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
#include "HealthBar.h"
#include "Kinematics.h"
#include "ItemManager.h"
#include "RoadManager.h"
#include "ThirdPersonCamera.h"
#include "SkyManager.h"
#include "ScoreManager.h"
#include "Vehicle.h"
#include "DriveController.h"

using namespace Vektoria;


class CGame
{
public:
	CGame(void);																				// Wird vor Begin einmal aufgerufen (Konstruktor)
	~CGame(void);																				// Wird nach Ende einmal aufgerufen (Destruktor)

	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash);	// Wird zu Begin einmal aufgerufen
	void Tick(float fTime, float fTimeDelta);													// Wird w�hrend der Laufzeit bei jedem Bildaufbau aufgerufen
	void Fini();																				// Wird am Ende einmal aufgerufen

	void WindowReSize(int iNewWidth, int iNewHeight);											// Wird immer dann aufgerufen, wenn der Benutzer die Fenstergr��e ver�ndert hat

	void initScene(TemplateScene* scene);
	void changeScene(eSceneType scene);
private:
	// Grundlegende Vektoria-Objekte
	CRoot m_Root;
	CFrame m_Frame;

	// Eingabeger�te
	CDeviceKeyboard m_Keyboard;
	CDeviceCursor m_Cursor;
	CDeviceGameController m_Controller;

	HealthBar* Health;
	ProgressBar* Speedometer;
	ThirdPersonCamera TPCamera;

	// ItemManager
	ItemManager* Items;

	//f�r den RoadManager
	RoadManager* RoadMaster;
	CPlacement drivingScenePlacement;
	float timetick;

	//f�r den SkyManager
	SkyManager* SkyMaster;

	//f�r den ScoreManager
	ScoreManager* ScoreMaster;

	// rudiment�re Steuerung
	float fAD = 0;
	float fSW = 0;
	float fFR = 0;
	float fLR = 0;
	float fUD = 0;
	float fHeightEye = 1;
	float fHeightRay = 1;
	CHitPoint hitpointCollision;
	CHitPoint hitpointGround;

	// Prototyp Textures
	CMaterial m_Dark;
	CMaterial m_Green;
	CMaterial m_Orange;
	CMaterial m_Purple;
	CMaterial m_Red;

	// Scorebar
	CWriting m_scoreWriting;
	CWritingFont m_scoreFont;

	// Variable f�r Funktionen die nach dem ersten Tick der Engine aufgerufen werden sollen (z.B.H�llk�rper)
	bool m_callOnceAfterTick = true;

	//Driving stuff
	Vehicle m_Car;
	DriveController m_dController;
	CMaterial m_zmTerrain;
	CPlacement m_zpTerrain;
	CGeoTerrain m_terrain;
	CGeoTerrains m_zgsColTerrain;

	CWriting m_SpeedValue;
	CWriting m_GasValue;
	CWriting m_ClutchValue;
	// Szenen
	TemplateScene* m_currentScene;
	GameScene m_SGame;
	MainMenu m_SMain;
};


