#pragma once


#ifdef _WIN64
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug64.lib")
#pragma comment (lib, "VektoriaMath_Debug64.lib")
#else
#pragma comment (lib, "Vektoria_Release64.lib")
#pragma comment (lib, "VektoriaMath_Release64.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug.lib")
#pragma comment (lib, "VektoriaMath_Debug.lib")
#else
#pragma comment (lib, "Vektoria_Release.lib")
#pragma comment (lib, "VektoriaMath_Release.lib")
#endif
#endif


#include "Vektoria\Root.h"
#include "Scenes/GameScene.h"
#include "Scenes/MainMenu.h"

using namespace Vektoria;


class CGame
{
public:
	CGame(void);																				// Wird vor Begin einmal aufgerufen (Konstruktor)
	~CGame(void);																				// Wird nach Ende einmal aufgerufen (Destruktor)

	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash);	// Wird zu Begin einmal aufgerufen
	void Tick(float fTime, float fTimeDelta);													// Wird während der Laufzeit bei jedem Bildaufbau aufgerufen
	void Fini();																				// Wird am Ende einmal aufgerufen

	void WindowReSize(int iNewWidth, int iNewHeight);											// Wird immer dann aufgerufen, wenn der Benutzer die Fenstergröße verändert hat

	void initScene(TemplateScene* scene);
	void changeScene(eSceneType scene);

	bool getExit();
private:
	// Grundlegende Vektoria-Objekte
	CRoot m_Root;
	CScene m_Scene;
	CViewport m_Viewport;
	CFrame m_Frame;

	// Eingabegeräte
	CDeviceKeyboard m_Keyboard;
	CDeviceCursor m_Cursor;
	CDeviceGameController m_Controller;

	// Szenen
	TemplateScene* m_currentScene;
	GameScene m_SGame;
	MainMenu m_SMain;

	// Setup Bool
	bool m_doSetup = false;
	bool m_exit = false;
};


