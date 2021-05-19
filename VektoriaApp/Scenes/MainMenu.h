#pragma once
#include "TemplateScene.h"
#include "../SkyManager.h"
#include "../gui/GuiButton.h"
#include "../gui/GuiSelect.h"
#include "../gui/GuiSlider.h"

using namespace Vektoria;

class MainMenu : public TemplateScene
{
public:

	void Init(CDeviceCursor* cursor, CDeviceKeyboard* keyboard);
	void update(float fTime, float fTimeDelta);

	bool IsOn();
	void SwitchOn();
	void SwitchOff();
	bool PlayPressed();
	bool SelectPressed();
	bool OptionsPressed();
	bool ExitPressed();

private:
	// Camera
	CCamera m_Camera;
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
	CMaterial m_MatOrange;
	CMaterial m_MatPurple;
	CMaterial m_MatRed;
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
	CGeoCube m_Cube1;
	CPlacement m_PCube1;
	CGeoCube m_Cube2;
	CPlacement m_PCube2;
	CGeoCube m_Cube3;
	CPlacement m_PCube3;
	CGeoCube m_Cube4;
	CPlacement m_PCube4;
	std::vector<CPlacement*> m_cubes;
		
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
};

