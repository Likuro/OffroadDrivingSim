#pragma once
#include "GuiButton.h"
#include "GuiSelect.h"
#include "GuiSlider.h"

using namespace Vektoria;

class PauseMenu
{
public:
	
	void Init(CViewport * viewport, CDeviceCursor *cursor);
	bool IsOn();
	void SwitchOn();
	void SwitchOff();
	bool ContinuePressed();
	bool OptionsPressed();
	bool ExitPressed();
private:
	// Übergebene Objekte
	CViewport* m_Viewport;
	CDeviceCursor* m_Cursor;

	// Fonts
	CWritingFont m_FontLucRed;

	// Materials Protype
	CMaterial m_MatDark;
	CMaterial m_MatGreen;
	CMaterial m_MatButtonHovered;
	CMaterial m_MatButton;
	CMaterial m_MatRed;

	// Overlays (Menüs)
	COverlay m_OvPauseMenu;
	COverlay m_OvCover;

	// Buttons
	CGuiButton m_BContinue;
	CGuiButton m_BOptions;
	CGuiButton m_BExit;
};

