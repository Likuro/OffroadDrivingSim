#include "Game.h"

CGame::CGame(void)
{
	//Mandy war hier hihi
	//Denis war hier
	//lulz
}

CGame::~CGame(void)
{
}

void CGame::Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash)
{
	srand(time(NULL));

	// Hier die Initialisierung Deiner Vektoria-Objekte einfügen:
	m_Root.Init(psplash);
	m_Root.AddFrame(&m_Frame);
	m_Frame.Init(hwnd, procOS);
	m_zr.Init(psplash);
	m_zc.Init(QUARTERPI, 0.5f);
	// m_zf.SetApiRender(eApiRender_DirectX11_Shadermodel50_Monolight);
	m_zf.Init(hwnd, procOS); 
	m_zv.InitFull(&m_zc);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f), CColor(1.0f, 1.0f, 1.0f));

	// Eingabegeräte (Keyboard/Controller/Maus)
	m_Frame.AddDeviceKeyboard(&m_Keyboard);
	m_Frame.AddDeviceGameController(&m_Controller);
	m_Frame.AddDeviceCursor(&m_Cursor);

	// Scenes Init
	m_SGame.Init(&m_Cursor, &m_Keyboard);
	initScene(&m_SGame);
	m_SMain.Init(&m_Cursor, &m_Keyboard);
	initScene(&m_SMain);

	// Prototype Textures für Camera Debugging
	m_Dark.MakeTextureDiffuse("textures\\PrototypeTextures\\Dark\\texture_06.png");
	m_Green.MakeTextureDiffuse("textures\\PrototypeTextures\\Green\\texture_06.png");
	m_Orange.MakeTextureDiffuse("textures\\PrototypeTextures\\Orange\\texture_06.png");
	m_Purple.MakeTextureDiffuse("textures\\PrototypeTextures\\Purple\\texture_06.png");
	m_Red.MakeTextureDiffuse("textures\\PrototypeTextures\\Red\\texture_06.png");

	// Dummy Kugel
	m_zs.AddPlacement(&m_zpSphere);
	m_zgSphere.Init(1.f, &m_Red, 50, 50);
	m_zpSphere.SetTranslationSensitivity(400.f);
	m_zpSphere.SetRotationSensitivity(2.f);
	m_zpSphere.AddGeo(&m_zgSphere);
	m_zpSphere.EnableAABBs();

	//Terrain
	m_zs.AddPlacement(&m_zpTerrain);
	m_zpTerrain.AddGeo(&m_terrain);
	m_terrain.InitQuick(100000, 100000, 10, false, &m_Green, 300, 300, 0, 0, 10, 10);
	m_zgsColTerrain.Add(&m_terrain);
	m_zpTerrain.TranslateY(-1000);

	//Drive
	m_Car.Init(&m_zs, &m_zpCamera, &m_Green, 0.8, 0.2, 200);
	m_dController.Init(&m_zs, &m_zv, &m_Car);

	// Camera
	TPCamera.Init(25.f, 4.f, eAlignObjDir, m_Car.GetMainPos(), &m_zc); // Changed
	m_zs.AddPlacement(&TPCamera);
	m_zv.SetMistOn(true);
	//m_zv.SetMistStartDistance(roadTilelength*(anzahlRoadTiles/2));
	m_zv.SetMistStrength(1.0/((float)roadTilelength*(float)anzahlRoadTiles));

	m_zf.AddDeviceKeyboard(&m_Keyboard);
	m_zf.AddDeviceGameController(&m_Controller);
	//Kugel Speed
	m_zpSphere.SetTranslationSensitivity(100.0f);

	// Healthbar
	Health = new HealthBar(&m_Orange, &m_zv, 100, 100, 0.7f, 0.9f, 0.25f, 0.05f);
	// Speedometer
	Speedometer = new ProgressBar(&m_Green, &m_zv, 100, 0, 0.05f, 0.9f, 0.25f, 0.05f);

	// ItemManager
	Items = new ItemManager(25, &m_zpSphere);

	//RoadMaster erstellen
	m_zs.AddPlacement(&drivingScenePlacement);
	this->RoadMaster = new RoadManager;
	RoadMaster->init(&drivingScenePlacement, Items);

	//SkyMaster erstellen
	this->SkyMaster = new SkyManager;
	SkyMaster->init(&m_zs, &m_zpSphere);

	//ScoreManager erstellen
	this->ScoreMaster = new ScoreManager;
	ScoreMaster->init(&m_zv);

	//Stats
	m_scoreFont.LoadPreset("LucidaConsoleRed");
	m_scoreFont.SetChromaKeyingOn();
	m_SpeedValue.Init(CFloatRect(0.5f, 0.05f, 0.15f, 0.05f), 10, &m_scoreFont);
	m_zv.AddWriting(&m_SpeedValue);
	m_GasValue.Init(CFloatRect(0.8f, 0.85f, 0.15f, 0.05f), 10, &m_scoreFont);
	m_zv.AddWriting(&m_GasValue);
	m_ClutchValue.Init(CFloatRect(0.1f, 0.85f, 0.15f, 0.05f), 10, &m_scoreFont);
	m_zv.AddWriting(&m_ClutchValue);

	// Setzen der Current Scene
	m_currentScene = &m_SMain;
	m_currentScene->SwitchOn();
	m_currentScene->getViewport()->SwitchOn();
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	m_Root.Tick(fTimeDelta);
	m_currentScene->update(fTime, fTimeDelta);
	if (m_currentScene->getChange())
	{
		changeScene(m_currentScene->getNextScene());
	}
}

	timetick++;

	// Tastatur Steuerung
	// Links/Rechts Verschiebung
	//if (m_Keyboard.KeyPressed(DIK_A))
	//{
	//	if (m_Keyboard.KeyPressed(DIK_D))
	//		fAD = 0.f;
	//	else
	//		fAD = -1.f;
	//}
	//else if (m_Keyboard.KeyPressed(DIK_D))
	//	fAD = 1.f;
	//else
	//	fAD = 0.f;
	// Vor/Zurück Verschiebung
	if (m_Keyboard.KeyPressed(DIK_W))
	{
		if (m_Keyboard.KeyPressed(DIK_S))
			fSW = 0.f;
		else
			fSW = -1.f;
	}
	else if (m_Keyboard.KeyPressed(DIK_S))
		fSW = 1.f;
	else
		fSW = 0.f;
	// Hoch/Runter Verschiebung
	if (m_Keyboard.KeyPressed(DIK_LSHIFT))
	{
		if (m_Keyboard.KeyPressed(DIK_SPACE))
			fFR = 0.f;
		else
			fFR = -1.f;
	}
	else if (m_Keyboard.KeyPressed(DIK_SPACE))
		fFR = 1.f;
	else
		fFR = 0.f;
	// Links/Rechts Drehung
	if (m_Keyboard.KeyPressed(DIK_A))
	{
		if (m_Keyboard.KeyPressed(DIK_D))
			fLR = 0.f;
		else
			fLR = -1.f;
	}
	else if (m_Keyboard.KeyPressed(DIK_D))
		fLR = 1.f;
	else
		fLR = 0.f;
	// Hoch/Runter Drehung 
	//!Vorsicht funktioniert bei Third - Person - Camera nicht so gut... (überhaupt nicht!)!//
	//if (m_Keyboard.KeyPressed(DIK_UP))
	//{
	//	if (m_Keyboard.KeyPressed(DIK_DOWN))
	//		fUD = 0.f;
	//	else
	//		fUD = -1.f;
	//}
	//else if (m_Keyboard.KeyPressed(DIK_DOWN))
	//	fUD = 1.f;
	//else
	//	fUD = 0.f;

	//m_zpSphere.MoveTerrain(fTimeDelta, fAD, fSW, fFR, fLR, fUD, RoadMaster->getGeosFrontal(), RoadMaster->getGeosGround(), fHeightEye, fHeightRay, hitpointCollision, hitpointGround, true, eMoveFlightKind_Ballistic);
	
	if (m_Keyboard.KeyDown(DIK_Q))
		m_dController.GearUp();
	if (m_Keyboard.KeyDown(DIK_F))
		m_dController.GearDown();



	if (m_Keyboard.KeyPressed(DIK_W))
		m_dController.Accelerate(fTimeDelta);
	else
		m_dController.Deaccelerate(fTimeDelta);
	//Rotations
	if (m_Keyboard.KeyPressed(DIK_D))
		m_dController.RotateRight(fTimeDelta);

	else if (m_Keyboard.KeyPressed(DIK_A))
		m_dController.RotateLeft(fTimeDelta);
	else
		m_dController.ResetRotation(fTimeDelta);
	//End Rotations
	if (m_Keyboard.KeyPressed(DIK_SPACE)|| m_Keyboard.KeyPressed(DIK_S))
		m_dController.Brake();

	if (m_Keyboard.KeyUp(DIK_SPACE))
		m_dController.ReleaseBrakes();
m_dController.ResetRotation(fTimeDelta);

	m_dController.Update(fTimeDelta, m_zgsColTerrain, RoadMaster->getGeosGround(), RoadMaster->getGeosFrontal());
	TPCamera.update();

	m_SpeedValue.PrintFloat(m_dController.GetSpeed());
	m_GasValue.PrintFloat(m_dController.GetGas());
	m_ClutchValue.PrintInt(m_dController.GetGear());

	//m_zpCamera.RotateY(PI);
	//m_zpCamera.RotateXDelta(atanf(20.f/100.f));
	//m_zpCamera.TranslateZDelta(m_zpSphere.GetPos().GetZ() - 100.f);
	//m_zpCamera.TranslateYDelta(m_zpSphere.GetPos().GetY() + 20.f);
	//m_zpCamera.TranslateXDelta(m_zpSphere.GetPos().GetX());
void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:
	m_Frame.ReSize(iNewWidth, iNewHeight);
}

void CGame::initScene(TemplateScene* scene)
{
	m_Root.AddScene(scene);
	scene->SwitchOff();
	m_Frame.AddViewport(scene->getViewport());
	scene->getViewport()->SwitchOff();
}

void CGame::changeScene(eSceneType scene)
{
	m_currentScene->reset();
	switch (scene)
	{
	case main:
		m_currentScene->SwitchOff();
		m_currentScene->getViewport()->SwitchOff();
		m_currentScene = &m_SMain;
		m_currentScene->SwitchOn();
		m_currentScene->getViewport()->SwitchOn();
		break;
	case game:
		m_currentScene->SwitchOff();
		m_currentScene->getViewport()->SwitchOff();
		m_currentScene = &m_SGame;
		m_currentScene->SwitchOn();
		m_currentScene->getViewport()->SwitchOn();
		break;
	default:
		break;
	}
		Speedometer->progressValue -= 0.005f;
		Speedometer->update();
	}

	//RoadManager
	RoadMaster->tryupdate(fTimeDelta, m_Car.GetMainPos()->GetPos());

	// ItemManager
	Items->update(fTime, fTimeDelta);

	//ScoreManager
	ScoreMaster->update(m_Car.GetMainPos()->GetPos(), fTimeDelta);

	//SkyManager
	SkyMaster->update(ScoreMaster->getScore());

}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:
	m_zf.ReSize(iNewWidth, iNewHeight);
}

