#pragma once
#include "gui/GuiButton.h"
#include "gui/GuiSelect.h"
#include "gui/GuiSlider.h"

using namespace Vektoria;

class PauseMenu
{
public:
	
	void Init(CViewport * viewport, CDeviceCursor *cursor);
private:
	// Übergebene Objekte
	CViewport* m_Viewport;
	CDeviceCursor* m_Cursor;

	// Fonts
	CWritingFont m_FontLucRed;

	// Materials Protype
	CMaterial m_MatDark;
	CMaterial m_MatGreen;
	CMaterial m_MatOrange;
	CMaterial m_MatPurple;
	CMaterial m_MatRed;

	// Overlays (Menüs)
	COverlay m_OvPauseMenu;

	// Buttons
	CGuiButton m_BContinue;
	CGuiButton m_BOptions;
	CGuiButton m_BExit;
};

