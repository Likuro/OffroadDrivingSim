#pragma once
#include "TemplateScene.h"
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
	bool OptionsPressed();
	bool ExitPressed();

private:
	// Camera
	CCamera m_Camera;
	CPlacement m_PCamera;

	// Input
	CDeviceCursor* m_Cursor;
	CDeviceKeyboard* m_Keyboard;

	// Fonts
	CWritingFont m_FontLucRed;

	// Materials Protype
	CMaterial m_MatDark;
	CMaterial m_MatGreen;
	CMaterial m_MatOrange;
	CMaterial m_MatPurple;
	CMaterial m_MatRed;

	// Overlays (Menüs)
	COverlay m_OvMenu;
	COverlay m_OvCover;

	// Buttons
	CGuiButton m_BPlay;
	CGuiButton m_BOptions;
	CGuiButton m_BExit;
};

