#pragma once
#include "TemplateScene.h"
#include "../HealthBar.h"
#include "../Kinematics.h"
#include "../ItemManager.h"
#include "../RoadManager.h"
#include "../ThirdPersonCamera.h"
#include "../gui/PauseMenu.h"
#include "../SkyManager.h"
#include "../ScoreManager.h"
#include "../Vehicle.h"
#include "../DriveController.h"

using namespace Vektoria;

class GameScene : public TemplateScene
{
public:
	void Init(CDeviceCursor* cursor, CDeviceKeyboard* keyboard);
	void update(float fTime, float fTimeDelta);
	void reset();

private:
	// Input
	CDeviceCursor* m_Cursor;
	CDeviceKeyboard* m_Keyboard;

	// Camera
	CCamera m_Camera;
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

	// Scorebar
	CWriting m_scoreWriting;
	CWritingFont m_scoreFont;
	unsigned int m_score = 0;

	// PauseMenu
	PauseMenu m_PauseMenu;

	// Einmal nach dem ersten Tick aufzurufen
	bool m_callOnceAfterTick = true;

	HealthBar* Health;
	ProgressBar* Speedometer;

	//f�r den SkyManager
	SkyManager* SkyMaster;

	//f�r den ScoreManager
	ScoreManager* ScoreMaster;

	//Driving stuff
	Vehicle m_Car;
	DriveController m_dController;

	CWriting m_SpeedValue;
	CWriting m_GasValue;
	CWriting m_ClutchValue;

	//Debug-Kamera Steuerung
	bool m_switchDebugCam = false;
};

