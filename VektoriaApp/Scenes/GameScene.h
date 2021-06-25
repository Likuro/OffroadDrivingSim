#pragma once
#include "TemplateScene.h"
#include "../gui/ProgressBar.h"
#include "../items/ItemManager.h"
#include "../road/RoadManager.h"
#include "../ThirdPersonCamera.h"
#include "../gui/PauseMenu.h"
#include "../SkyManager.h"
#include "../ScoreManager.h"
#include "../knackCar/Vehicle.h"
#include "../knackCar/DriveController.h"

using namespace Vektoria;

class GameScene : public TemplateScene
{
public:
	void Init(CScene* scene, CViewport* viewport, CDeviceCursor* cursor, CDeviceKeyboard* keyboard);

	void selectCar(int carID);
	void update(float fTime, float fTimeDelta);
	void reset();
	void setup();

	void setcarID(int ID);
	int getcarID();

private:
	// Input
	CDeviceCursor* m_Cursor;
	CDeviceKeyboard* m_Keyboard;

	// Camera
	CPlacement m_PCamera;
	ThirdPersonCamera m_TPCamera;

	// ItemManager
	ItemManager* Items;

	//f�r den RoadManager
	RoadManager* RoadMaster;
	CPlacement drivingScenePlacement;
	float timetick;

	// Prototyp Textures
	CMaterial m_Dark;
	CMaterial m_Green;
	CMaterial m_Orange;
	CMaterial m_Purple;
	CMaterial m_Red;

	// Materials
	CMaterial m_MatButton;
	CMaterial m_MatButtonHovered;

	// Fonts
	CWritingFont m_FontLucRed;

	// Scorebar
	CWriting m_scoreWriting;
	CWritingFont m_scoreFont;
	unsigned int m_score = 0;

	// PauseMenu
	PauseMenu m_PauseMenu;

	// Endscreen
	COverlay m_EndScreen;
	COverlay m_EndTextBox;
	CMaterial m_MYouDied;
	CGuiButton m_BEndGame;

	// Einmal nach dem ersten Tick aufzurufen
	bool m_callOnceAfterTick = true;

	ProgressBar* m_HealthBar;
	ProgressBar* m_BoostBar;

	//f�r den SkyManager
	SkyManager* SkyMaster;

	//f�r den ScoreManager
	ScoreManager* ScoreMaster;

	//Driving stuff
	Vehicle* m_currentCar;
	Vehicle m_SportsCar;
	Vehicle m_MonsterTruck;
	Vehicle m_Bus;
	Vehicle m_OldCar;

	DriveController* m_dController;
	DriveController m_SportsController;
	DriveController m_MonsterController;
	DriveController m_BusController;
	DriveController m_OldController;

	CWriting m_SpeedValue;
	CWriting m_GasValue;
	CWriting m_ClutchValue;
	int m_carID = 0;

	//Debug-Kamera Steuerung
	bool m_switchDebugCam = false;

	CPlacement test;
	CGeoCube testcube;
};

