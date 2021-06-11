#include "PauseMenu.h"

void PauseMenu::Init(COverlay* overlay, CDeviceCursor* cursor)
{
	m_Cursor = cursor;

	// Laden der Schriftart
	m_FontLucRed.LoadPreset("LucidaConsoleRed");
	m_FontLucRed.SetChromaKeyingOn();

	// Laden des Materials
	m_MatDark.MakeTextureSprite("textures\\PrototypeTextures\\Dark\\texture_14.png");
	m_MatGreen.MakeTextureSprite("textures\\PrototypeTextures\\Green\\texture_06.png");
	m_MatButtonHovered.MakeTextureSprite("textures\\Buttons\\Button_Pressed.png");
	m_MatButton.MakeTextureSprite("textures\\Buttons\\Button.png");
	m_MatRed.MakeTextureSprite("textures\\PrototypeTextures\\Red\\texture_06.png");

	// Menu Aufbau
	overlay->AddOverlay(&m_OvCover);
	m_OvCover.InitFull(&m_MatDark);
	m_OvCover.SetTransparency(0.3f);
	m_OvCover.SetLayer(0.9999f);

	m_OvCover.AddOverlay(&m_OvPauseMenu);
	m_OvPauseMenu.Init(&m_MatDark, CFloatRect(0.35f, 0.2f, 0.3f, 0.6f));
	m_OvPauseMenu.SetLayer(1.f);

	float distanceButtons = 0.1f;
	float numberofButtons = 3.f;
	float sizeButtons = (1.f - ((numberofButtons - 1.f) * distanceButtons)) / numberofButtons;

	// Continue-Button
	m_OvPauseMenu.AddOverlay(&m_BContinue);
	m_BContinue.Init(m_Cursor, &m_FontLucRed, CFloatRect(0.f, 0.f, 1.f, sizeButtons));
	m_BContinue.SetLabel("CONTINUE");
	m_BContinue.SetMaterialNormal(m_MatButton);
	m_BContinue.SetMaterialHover(m_MatButtonHovered);
	m_BContinue.SetMaterialClick(m_MatButton);
	m_BContinue.SetInnerOn();

	// Options-Button
	m_OvPauseMenu.AddOverlay(&m_BOptions);
	m_BOptions.Init(m_Cursor, &m_FontLucRed, CFloatRect(0.f, sizeButtons + distanceButtons, 1.f, sizeButtons));
	m_BOptions.SetLabel("OPTIONS");
	m_BOptions.SetMaterialNormal(m_MatButton);
	m_BOptions.SetMaterialHover(m_MatButtonHovered);
	m_BOptions.SetMaterialClick(m_MatButton);
	m_BOptions.SetInnerOn();

	// Exit-Button
	m_OvPauseMenu.AddOverlay(&m_BExit);
	m_BExit.Init(m_Cursor, &m_FontLucRed, CFloatRect(0.f, (sizeButtons + distanceButtons) * 2.f, 1.f, sizeButtons));
	m_BExit.SetLabel("EXIT");
	m_BExit.SetMaterialNormal(m_MatButton);
	m_BExit.SetMaterialHover(m_MatButtonHovered);
	m_BExit.SetMaterialClick(m_MatButton);
	m_BExit.SetInnerOn();

	m_OvCover.SwitchOff();
}

bool PauseMenu::IsOn()
{
	return m_OvCover.IsOn();
}

void PauseMenu::SwitchOn()
{
	m_OvCover.SwitchOn();
}

void PauseMenu::SwitchOff()
{
	m_OvCover.SwitchOff();
}

bool PauseMenu::ContinuePressed()
{
	return m_BContinue.IsClicked();
}

bool PauseMenu::OptionsPressed()
{
	return m_BOptions.IsClicked();
}

bool PauseMenu::ExitPressed()
{
	return m_BExit.IsClicked();
}
