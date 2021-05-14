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
	TPCamera.Init(27.f, 2.2f, eAlignObjDir, m_Car.GetMainPos(), &m_zc); // Changed
	m_zs.AddPlacement(&TPCamera);

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
}
