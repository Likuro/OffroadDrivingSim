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
