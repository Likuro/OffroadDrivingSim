#include "MainMenu.h"

void MainMenu::Init(CDeviceCursor* cursor, CDeviceKeyboard* keyboard)
{
	m_Cursor = cursor;
	m_Keyboard = keyboard;

	// Camera Init
	m_Camera.Init(QUARTERPI);
	m_PCamera.AddCamera(&m_Camera);
	this->AddPlacement(&m_PCamera);

	// Viewport Init
	m_Viewport.InitFull(&m_Camera);

	// Laden der Schriftart
	m_FontLucRed.LoadPreset("LucidaConsoleRed");
	m_FontLucRed.SetChromaKeyingOn();

	// Laden des Materials
	m_MatDark.MakeTextureSprite("textures\\PrototypeTextures\\Dark\\texture_06.png");
	m_MatGreen.MakeTextureSprite("textures\\PrototypeTextures\\Green\\texture_06.png");
	m_MatOrange.MakeTextureSprite("textures\\PrototypeTextures\\Orange\\texture_06.png");
	m_MatPurple.MakeTextureSprite("textures\\PrototypeTextures\\Purple\\texture_06.png");
	m_MatRed.MakeTextureSprite("textures\\PrototypeTextures\\Red\\texture_06.png");

	// Menu Aufbau
	m_Viewport.AddOverlay(&m_OvCover);
	m_OvCover.InitFull(&m_MatDark);
	m_OvCover.SetTransparency(0.5f);
	m_OvCover.SetLayer(0.9999f);

	m_OvCover.AddOverlay(&m_OvMenu);
	m_OvMenu.Init(&m_MatDark, CFloatRect(0.35f, 0.2f, 0.3f, 0.6f));
	m_OvMenu.SetLayer(1.f);

	float distanceButtons = 0.1f;
	float numberofButtons = 3.f;
	float sizeButtons = (1.f - ((numberofButtons - 1.f) * distanceButtons)) / numberofButtons;

	// Continue-Button
	m_OvMenu.AddOverlay(&m_BPlay);
	m_BPlay.Init(m_Cursor, &m_FontLucRed, CFloatRect(0.f, 0.f, 1.f, sizeButtons));
	m_BPlay.SetLabel("PLAY");
	m_BPlay.SetMaterialNormal(m_MatPurple);
	m_BPlay.SetMaterialHover(m_MatDark);
	m_BPlay.SetMaterialClick(m_MatOrange);
	m_BPlay.SetInnerOn();

	// Options-Button
	m_OvMenu.AddOverlay(&m_BOptions);
	m_BOptions.Init(m_Cursor, &m_FontLucRed, CFloatRect(0.f, sizeButtons + distanceButtons, 1.f, sizeButtons));
	m_BOptions.SetLabel("OPTIONS");
	m_BOptions.SetMaterialNormal(m_MatPurple);
	m_BOptions.SetMaterialHover(m_MatDark);
	m_BOptions.SetMaterialClick(m_MatOrange);
	m_BOptions.SetInnerOn();

	// Exit-Button
	m_OvMenu.AddOverlay(&m_BExit);
	m_BExit.Init(m_Cursor, &m_FontLucRed, CFloatRect(0.f, (sizeButtons + distanceButtons) * 2.f, 1.f, sizeButtons));
	m_BExit.SetLabel("EXIT");
	m_BExit.SetMaterialNormal(m_MatPurple);
	m_BExit.SetMaterialHover(m_MatDark);
	m_BExit.SetMaterialClick(m_MatOrange);
	m_BExit.SetInnerOn();
}

void MainMenu::update(float fTime, float fTimeDelta)
{
	if (PlayPressed())
	{
		m_changeScene = true;
		m_nextScene = game;
	}
}

bool MainMenu::IsOn()
{
	return m_OvCover.IsOn();
}

void MainMenu::SwitchOn()
{
	m_OvCover.SwitchOn();
}

void MainMenu::SwitchOff()
{
	m_OvCover.SwitchOff();
}

bool MainMenu::PlayPressed()
{
	return m_BPlay.IsClicked();
}

bool MainMenu::OptionsPressed()
{
	return m_BOptions.IsClicked();
}

bool MainMenu::ExitPressed()
{
	return m_BExit.IsClicked();
}