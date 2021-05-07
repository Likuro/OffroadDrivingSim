#pragma once
#include "TemplateScene.h"
#include "../HealthBar.h"
#include "../Kinematics.h"
#include "../ItemManager.h"
#include "../RoadManager.h"
#include "../ThirdPersonCamera.h"
#include "../gui/PauseMenu.h"

using namespace Vektoria;

class GameScene : public TemplateScene
{
public:
	void Init(CDeviceCursor* cursor, CDeviceKeyboard* keyboard);
	void update(float fTime, float fTimeDelta);

private:
	CPlacement m_RadialLightPlace;
	CLightRadial m_RadialLight;
	CPlacement m_zpSphere;
	CGeoSphere m_zgSphere;
	HealthBar* Health;
	ProgressBar* Speedometer;

	// Input
	CDeviceCursor* m_Cursor;
	CDeviceKeyboard* m_Keyboard;

	// Camera
	CCamera m_Camera;
	CPlacement m_PCamera;
	ThirdPersonCamera m_TPCamera;

	// ItemManager
	ItemManager* Items;

	//für den RoadManager
	RoadManager* RoadMaster;
	CPlacement drivingScenePlacement;
	float timetick;

	// rudimentäre Steuerung
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
	unsigned int m_score = 0;

	// PauseMenu
	PauseMenu m_PauseMenu;

	// Einmal nach dem ersten Tick aufzurufen
	bool m_callOnceAfterTick = true;
};

