#pragma once
#include "GameScene.h"
#include "../gui/GuiButton.h"
#include "../gui/GuiSelect.h"
#include "../gui/GuiSlider.h"

using namespace Vektoria;

class MainMenu : public TemplateScene
{
public:
	void setGameScene(GameScene* game);
	void Init(CScene* scene, CViewport* viewport, CDeviceCursor* cursor, CDeviceKeyboard* keyboard);

	void selectCar(int carID);
	void update(float fTime, float fTimeDelta);
	void reset();
	void setup();

	bool IsOn();
	void SwitchOn();
	void SwitchOff();
	bool PlayPressed();
	bool SelectPressed();
	bool OptionsPressed();
	bool ExitPressed();

private:
	// Game Scene
	GameScene* m_GameScene;

	// Camera
	CPlacement m_PCamera;

	// Sky
	SkyManager m_SkyManager;

	// Input
	CDeviceCursor* m_Cursor;
	CDeviceKeyboard* m_Keyboard;

	// Fonts
	CWritingFont m_FontLucRed;

	// Materials
	CMaterial m_MatDark;
	CMaterial m_MatGreen;
	CMaterial m_MatButtonHovered;
	CMaterial m_MatButton;
	CMaterial m_MatGround;
	CMaterial m_MatRightArrow;
	CMaterial m_MatRightArrowHovered;
	CMaterial m_MatLeftArrow;
	CMaterial m_MatLeftArrowHovered;

	// Overlays (Menüs)
	COverlay m_OvCover;
	COverlay m_OvMenu;
	COverlay m_OvSelectMenu;

	// Buttons
	CGuiButton m_BPlay;
	CGuiButton m_BSelectCar;
	CGuiButton m_BOptions;
	CGuiButton m_BExit;
	CGuiButton m_BConfirm;
	
	// Select Buttons
	CGuiButton m_BLeft;
	CGuiButton m_BRight;

	// Transition Main-Selection
	float m_selectionDownAngle;
	float m_transitionTime = 0.8f;
	float m_transTimer = 0.f;
	bool m_selectTransition = false;
	bool m_mainTransition = false;

	// Prototyp Placements + Geos
	CPlacement m_pDark;
	CPlacement m_pGreen;
	CPlacement m_pOrange;
	CPlacement m_pPurple;
	CPlacement m_pRed;
	CGeoQuad m_gDark;
	CGeoQuad m_gGreen;
	CGeoQuad m_gOrange;
	CGeoQuad m_gPurple;
	CGeoQuad m_gRed;

	// Car Placeholders
	Vehicle m_SportsCar;
	Vehicle m_MonsterTruck;
	Vehicle m_Bus;
	Vehicle m_OldCar;
	CPlacement m_PSportsCar;
	CPlacement m_PMonsterTruck;
	CPlacement m_PBus;
	CPlacement m_POldCar;
	CPlacement m_PSuperCarWheel;
	CPlacement m_PBusWheel;
	CPlacement m_PTruckWheel;
	CPlacement m_POldCarWheel;
	std::vector<CPlacement*> m_cars;
		
	// Car-Wheel Variables
	CPlacement m_PSelectionAnchor;
	CPlacement m_PSelectionWheel;
	CPlacement m_PRoad;
	CGeo* m_GRoad;
	float m_wheelradius = 20.f;
	float m_rotationduration = 0.5f;
	float m_rotationstart = 0.f;
	int m_carindex = 0;
	bool m_rotateright = false;
	bool m_rotateleft = false;

	// Main-Car Display
	CPlacement m_PMainCar;
	CPlacement m_PDisplayQuad;
	CGeoQuad m_GDisplayQuad;
	CPlacement* m_PSelectedCar;
	CPlacement m_PSelectSuperCar;
	CPlacement m_PSelectTruck;
	CPlacement m_PSelectBus;
	CPlacement m_PSelectOldCar;
};

