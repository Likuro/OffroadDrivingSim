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
	m_zr.Init(psplash);
	m_zc.Init(QUARTERPI);
	// m_zf.SetApiRender(eApiRender_DirectX11_Shadermodel50_Monolight);
	m_zf.Init(hwnd, procOS); 
	m_zv.InitFull(&m_zc);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f), CColor(1.0f, 1.0f, 1.0f));

	m_zr.AddFrame(&m_zf);
	m_zf.AddViewport(&m_zv);
	m_zr.AddScene(&m_zs);
	m_zs.AddLightParallel(&m_zl);
	m_zs.SetSkyOn(&m_zpCamera, true);

	// Neues cooles Licht
	m_zs.AddPlacement(&m_RadialLightPlace);
	m_RadialLight.Init(CColor(1.f, 1.f, 1.f), 0.1f);
	m_RadialLightPlace.AddLightRadial(&m_RadialLight);
	m_RadialLightPlace.TranslateY(100.f);

	// Prototyp Cube Init
	initPrototypCube();

	// Dummy Kugel
	m_zs.AddPlacement(&m_zpSphere);
	m_zgSphere.Init(1.f, &m_Red, 50, 50);
	m_zpSphere.SetTranslationSensitivity(50.f);				// Geschwindigkeit der Kugel
	m_zpSphere.SetRotationSensitivity(2.f);
	m_zpSphere.AddGeo(&m_zgSphere);
	m_zpSphere.EnableAABBs();

	// Camera
	TPCamera.Init(50.f, 10.f, eAlignObjDir, &m_zpSphere, &m_zc);
	m_zs.AddPlacement(&TPCamera);

	// Eingabegeräte (Keyboard/Controller)
	m_zf.AddDeviceKeyboard(&m_Keyboard);
	m_zf.AddDeviceGameController(&m_Controller);
	m_zf.AddDeviceCursor(&m_Cursor);

	// Healthbar
	Health = new HealthBar(&m_Orange, &m_zv, 100, 100, 0.7f, 0.9f, 0.25f, 0.05f);
	// Speedometer
	Speedometer = new ProgressBar(&m_Green, &m_zv, 100, 0, 0.05f, 0.9f, 0.25f, 0.05f);
	// PauseMenu
	m_PauseMenu.Init(&m_zv, &m_Cursor);
	// ItemManager
	Items = new ItemManager(25, &m_zpSphere);

	// RoadMaster erstellen
	m_zs.AddPlacement(&drivingScenePlacement);
	this->RoadMaster = new RoadManager;
	RoadMaster->init(&drivingScenePlacement, Items);

	// Score
	m_scoreFont.LoadPreset("LucidaConsoleRed");
	m_scoreFont.SetChromaKeyingOn();
	m_scoreWriting.Init(CFloatRect(0.825f, 0.05f, 0.15f, 0.05f), 10, &m_scoreFont);
	m_zv.AddWriting(&m_scoreWriting);
	m_scoreWriting.PrintInt(m_score);
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	m_zr.Tick(fTimeDelta);
	if (m_callOnceAfterTick)
	{
		// Funktionen die nach dem ersten Tick aufgerufen werden sollen, aber dann nicht mehr
		Items->InitRays(m_zpSphere.GetAABB());	// AABB des Players muss zu Beginn übergeben werden, um Strahlenbüschel zu nutzen
		m_callOnceAfterTick = false;
	}

	timetick++;

	// Score
	m_score = m_zpSphere.GetPos().Dist(CHVector(0.f, 0.f, 0.f, 0.f));
	m_scoreWriting.PrintInt(m_score);
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
	// Zoom
	if (m_Keyboard.KeyPressed(DIK_UP))
	{
		if (m_Keyboard.KeyPressed(DIK_DOWN))
			TPCamera.zoom(0.4f * fTimeDelta);
		else
			TPCamera.zoom(-0.4f * fTimeDelta);
	}
	else if (m_Keyboard.KeyPressed(DIK_DOWN))
		TPCamera.zoom(0.4f * fTimeDelta);

	m_zpSphere.MoveTerrain(fTimeDelta, fAD, fSW, fFR, fLR, fUD, RoadMaster->getGeosFrontal(), RoadMaster->getGeosGround(), fHeightEye, fHeightRay, hitpointCollision, hitpointGround, true, eMoveFlightKind_Ballistic);
	TPCamera.update(fTimeDelta);

	//m_zpCamera.RotateY(PI);
	//m_zpCamera.RotateXDelta(atanf(20.f/100.f));
	//m_zpCamera.TranslateZDelta(m_zpSphere.GetPos().GetZ() - 100.f);
	//m_zpCamera.TranslateYDelta(m_zpSphere.GetPos().GetY() + 20.f);
	//m_zpCamera.TranslateXDelta(m_zpSphere.GetPos().GetX());

	// Controller Steuerung
	if (abs(m_Controller.GetRelativeX()) > 0.1)		// Deadzone
	{
		m_zpSphere.TranslateXDelta(-0.2f*(m_Controller.GetRelativeX()*controllerSpeed));
	}
	if (abs(m_Controller.GetRelativeY()) > 0.1)		// Deadzone
	{
		m_zpSphere.TranslateZDelta(0.2f*(-m_Controller.GetRelativeY()*controllerSpeed));
	}
	if (abs(m_Controller.GetRelativeRX()) > 0.1)
	{
		m_zpCamera.RotateYDelta(0.025f * (-m_Controller.GetRelativeRX() * controllerSpeed));
	}
	//if (abs(m_Controller.GetRelativeRY()) > 0.1)
	//{
	//	m_zpCamera.RotateXDelta(0.025f * (m_Controller.GetRelativeRY() * controllerSpeed));
	//}
	//if (abs(m_Controller.GetRelativeRZ()) > 0.1)
	//{
	//	m_zpSphere.TranslateYDelta(0.05f * (m_Controller.GetRelativeRZ() * controllerSpeed));
	//}

	// HealthBar Test
	if (m_Keyboard.KeyDown(DIK_Q))
	{
		Health->changeHealth(-10.f);
	}

	// Speedometer Test
	if (m_Keyboard.KeyPressed(DIK_E))
	{
		Speedometer->progressValue += 0.05f;
		Speedometer->update();
	}
	else
	{
		Speedometer->progressValue -= 0.005f;
		Speedometer->update();
	}

	// nur alle 5k Ticks -- RoadMaster
	if (timetick == 5000) {

		this->RoadMaster->updateRoad();

		timetick = 0;
	}

	// ItemManager
	Items->update(fTime, fTimeDelta);

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

void CGame::initPrototypCube()
{
	// Prototype Textures für Camera Debugging
	m_Dark.MakeTextureDiffuse("textures\\PrototypeTextures\\Dark\\texture_06.png");
	m_Green.MakeTextureDiffuse("textures\\PrototypeTextures\\Green\\texture_06.png");
	m_Orange.MakeTextureDiffuse("textures\\PrototypeTextures\\Orange\\texture_06.png");
	m_Purple.MakeTextureDiffuse("textures\\PrototypeTextures\\Purple\\texture_06.png");
	m_Red.MakeTextureDiffuse("textures\\PrototypeTextures\\Red\\texture_06.png");
	// Dark für den Boden
	m_zs.AddPlacement(&m_pDark);
	m_gDark.SetAxis(eAxisY);
	m_gDark.Init(100.f, &m_Dark);
	m_pDark.AddGeo(&m_gDark);
	m_pDark.TranslateY(-100.f);
	// Green für Wand in positive Z-Richtung
	m_zs.AddPlacement(&m_pGreen);
	m_gGreen.SetAxis(eAxisZ);
	m_gGreen.Init(100.f, &m_Green);
	m_pGreen.AddGeo(&m_gGreen);
	m_pGreen.RotateY(PI);
	m_pGreen.TranslateZDelta(100.f);
	// Orange für Wand in negativer Z-Richtung
	m_zs.AddPlacement(&m_pOrange);
	m_gOrange.SetAxis(eAxisZ);
	m_gOrange.Init(100.f, &m_Orange);
	m_pOrange.AddGeo(&m_gOrange);
	m_pOrange.TranslateZDelta(-100.f);
	// Purple für Wand in positiver X-Richtung
	m_zs.AddPlacement(&m_pPurple);
	m_gPurple.SetAxis(eAxisX);
	m_gPurple.Init(100.f, &m_Purple);
	m_pPurple.AddGeo(&m_gPurple);
	m_pPurple.RotateY(PI);
	m_pPurple.TranslateXDelta(100.f);
	// Red für Wand in negativer X-Richtung
	m_zs.AddPlacement(&m_pRed);
	m_gRed.SetAxis(eAxisX);
	m_gRed.Init(100.f, &m_Red);
	m_pRed.AddGeo(&m_gRed);
	m_pRed.TranslateXDelta(-100.f);
}