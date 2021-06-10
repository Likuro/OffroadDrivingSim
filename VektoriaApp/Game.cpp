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
	m_Root.AddScene(&m_Scene);
	m_Frame.Init(hwnd, procOS);
	m_Frame.AddViewport(&m_Viewport);

	// Eingabegeräte (Keyboard/Controller/Maus)
	m_Frame.AddDeviceKeyboard(&m_Keyboard);
	m_Frame.AddDeviceGameController(&m_Controller);
	m_Frame.AddDeviceCursor(&m_Cursor);

	// Scenes Init
	m_SGame.Init(&m_Scene, &m_Viewport, &m_Cursor, &m_Keyboard);
	m_SMain.setGameScene(&m_SGame);
	m_SMain.Init(&m_Scene, &m_Viewport, &m_Cursor, &m_Keyboard);
	initScene(&m_SGame);
	initScene(&m_SMain);

	m_currentScene = &m_SMain;
	m_currentScene->SwitchOn();
	m_currentScene->getOverlay()->SwitchOn();
	m_Viewport.InitFull(m_currentScene->getCamera());
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
	m_Scene.AddPlacement(scene);
	scene->getOverlay()->SwitchOff();
	scene->SwitchOff();
}

void CGame::changeScene(eSceneType scene)
{
	m_doSetup = m_currentScene->getSetup();
	m_currentScene->setSetup(false);
	m_currentScene->reset();
	switch (scene)
	{
	case main:
		m_currentScene->SwitchOff();
		m_currentScene->getOverlay()->SwitchOff();
		m_currentScene = &m_SMain;
		m_currentScene->SwitchOn();
		m_currentScene->getOverlay()->SwitchOn();
		m_Viewport.InitFull(m_currentScene->getCamera());
		break;
	case game:
		m_currentScene->SwitchOff();
		m_currentScene->getOverlay()->SwitchOff();
		m_currentScene = &m_SGame;
		m_currentScene->SwitchOn();
		m_currentScene->getOverlay()->SwitchOn();
		m_Viewport.InitFull(m_currentScene->getCamera());
		break;
	default:
		break;
	}
	if (m_doSetup)
	{
		m_currentScene->setup();
	}
}
