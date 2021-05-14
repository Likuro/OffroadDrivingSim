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

	// Laden der Materiale
	m_MatDark.MakeTextureSprite("textures\\PrototypeTextures\\Dark\\texture_06.png");
	m_MatGreen.MakeTextureSprite("textures\\PrototypeTextures\\Green\\texture_06.png");
	m_MatOrange.MakeTextureSprite("textures\\PrototypeTextures\\Orange\\texture_06.png");
	m_MatPurple.MakeTextureSprite("textures\\PrototypeTextures\\Purple\\texture_06.png");
	m_MatRed.MakeTextureSprite("textures\\PrototypeTextures\\Red\\texture_06.png");
	m_MatRightArrow.MakeTextureSprite("textures\\Arrows\\Right_Arrow.png");
	m_MatRightArrowHovered.MakeTextureSprite("textures\\Arrows\\Right_Arrow_Hovered.png");
	m_MatLeftArrow.MakeTextureSprite("textures\\Arrows\\Left_Arrow.png");
	m_MatLeftArrowHovered.MakeTextureSprite("textures\\Arrows\\Left_Arrow_Hovered.png");

	// Dark für den Boden
	this->AddPlacement(&m_pDark);
	m_gDark.SetAxis(eAxisY);
	m_gDark.Init(100.f, &m_MatDark);
	m_pDark.AddGeo(&m_gDark);
	m_pDark.TranslateY(-100.f);
	// Green für Wand in positive Z-Richtung
	this->AddPlacement(&m_pGreen);
	m_gGreen.SetAxis(eAxisZ);
	m_gGreen.Init(100.f, &m_MatGreen);
	m_pGreen.AddGeo(&m_gGreen);
	m_pGreen.RotateY(PI);
	m_pGreen.TranslateZDelta(100.f);
	// Orange für Wand in negativer Z-Richtung
	this->AddPlacement(&m_pOrange);
	m_gOrange.SetAxis(eAxisZ);
	m_gOrange.Init(100.f, &m_MatOrange);
	m_pOrange.AddGeo(&m_gOrange);
	m_pOrange.TranslateZDelta(-100.f);
	// Purple für Wand in positiver X-Richtung
	this->AddPlacement(&m_pPurple);
	m_gPurple.SetAxis(eAxisX);
	m_gPurple.Init(100.f, &m_MatPurple);
	m_pPurple.AddGeo(&m_gPurple);
	m_pPurple.RotateY(PI);
	m_pPurple.TranslateXDelta(100.f);
	// Red für Wand in negativer X-Richtung
	//this->AddPlacement(&m_pRed);
	//m_gRed.SetAxis(eAxisX);
	//m_gRed.Init(100.f, &m_MatRed);
	//m_pRed.AddGeo(&m_gRed);
	//m_pRed.TranslateXDelta(-100.f);

	// Menu Aufbau
	m_Viewport.AddOverlay(&m_OvCover);
	m_OvCover.InitFull(&m_MatDark);
	m_OvCover.SetLayer(1.f);

	m_OvCover.AddOverlay(&m_OvMenu);
	m_OvMenu.Init(&m_MatDark, CFloatRect(0.35f, 0.2f, 0.3f, 0.6f));
	m_OvMenu.SetLayer(1.f);

	m_OvCover.AddOverlay(&m_OvSelectMenu);
	m_OvSelectMenu.InitFull(&m_MatDark);
	m_OvSelectMenu.SetLayer(1.f);
	m_OvSelectMenu.SwitchOff();

	float distanceButtons = 0.1f;
	float numberofButtons = 4.f;
	float sizeButtons = (1.f - ((numberofButtons - 1.f) * distanceButtons)) / numberofButtons;

	// Continue-Button
	m_OvMenu.AddOverlay(&m_BPlay);
	m_BPlay.Init(m_Cursor, &m_FontLucRed, CFloatRect(0.f, 0.f, 1.f, sizeButtons));
	m_BPlay.SetLabel("PLAY");
	m_BPlay.SetMaterialNormal(m_MatPurple);
	m_BPlay.SetMaterialHover(m_MatDark);
	m_BPlay.SetMaterialClick(m_MatOrange);
	m_BPlay.SetInnerOn();

	// Select Car-Button
	m_OvMenu.AddOverlay(&m_BSelectCar);
	m_BSelectCar.Init(m_Cursor, &m_FontLucRed, CFloatRect(0.f, sizeButtons + distanceButtons, 1.f, sizeButtons));
	m_BSelectCar.SetLabel("SELECT CAR");
	m_BSelectCar.SetMaterialNormal(m_MatPurple);
	m_BSelectCar.SetMaterialHover(m_MatDark);
	m_BSelectCar.SetMaterialClick(m_MatOrange);
	m_BSelectCar.SetInnerOn();

	// Options-Button
	m_OvMenu.AddOverlay(&m_BOptions);
	m_BOptions.Init(m_Cursor, &m_FontLucRed, CFloatRect(0.f, (sizeButtons + distanceButtons) * 2.f, 1.f, sizeButtons));
	m_BOptions.SetLabel("OPTIONS");
	m_BOptions.SetMaterialNormal(m_MatPurple);
	m_BOptions.SetMaterialHover(m_MatDark);
	m_BOptions.SetMaterialClick(m_MatOrange);
	m_BOptions.SetInnerOn();

	// Exit-Button
	m_OvMenu.AddOverlay(&m_BExit);
	m_BExit.Init(m_Cursor, &m_FontLucRed, CFloatRect(0.f, (sizeButtons + distanceButtons) * 3.f, 1.f, sizeButtons));
	m_BExit.SetLabel("EXIT");
	m_BExit.SetMaterialNormal(m_MatPurple);
	m_BExit.SetMaterialHover(m_MatDark);
	m_BExit.SetMaterialClick(m_MatOrange);
	m_BExit.SetInnerOn();

	// Confirm-Button
	m_OvSelectMenu.AddOverlay(&m_BConfirm);
	m_BConfirm.Init(m_Cursor, &m_FontLucRed, CFloatRect(0.3f, 0.7f, 0.4f, 0.2f));
	m_BConfirm.SetLabel("CONFIRM");
	m_BConfirm.SetMaterialNormal(m_MatPurple);
	m_BConfirm.SetMaterialHover(m_MatDark);
	m_BConfirm.SetMaterialClick(m_MatOrange);
	m_BConfirm.SetInnerOn();

	// Left-Button
	m_OvSelectMenu.AddOverlay(&m_BLeft);
	m_BLeft.Init(m_Cursor, &m_FontLucRed, CFloatRect(0.1f, 0.3f, 0.1f, 0.4f));
	m_BLeft.SetMaterialNormal(m_MatLeftArrow);
	m_BLeft.SetMaterialHover(m_MatLeftArrowHovered);
	m_BLeft.SetMaterialClick(m_MatLeftArrow);
	m_BLeft.SetInnerOn();

	// Right-Button
	m_OvSelectMenu.AddOverlay(&m_BRight);
	m_BRight.Init(m_Cursor, &m_FontLucRed, CFloatRect(0.8f, 0.3f, 0.1f, 0.4f));
	m_BRight.SetMaterialNormal(m_MatRightArrow);
	m_BRight.SetMaterialHover(m_MatRightArrowHovered);
	m_BRight.SetMaterialClick(m_MatRightArrow);
	m_BRight.SetInnerOn();

	// Cube-Wheel Init
	this->AddPlacement(&m_PSelectionAnchor);
	m_PSelectionAnchor.AddPlacement(&m_PSelectionWheel);
	m_PSelectionAnchor.Translate(-60.f, -10.f, 0.f);
	m_Cube1.Init(1.f, &m_MatDark);
	m_PCube1.AddGeo(&m_Cube1);
	m_PSelectionWheel.AddPlacement(&m_PCube1);
	m_Cube2.Init(1.f, &m_MatGreen);
	m_PCube2.AddGeo(&m_Cube2);
	m_PSelectionWheel.AddPlacement(&m_PCube2);
	m_Cube3.Init(1.f, &m_MatPurple);
	m_PCube3.AddGeo(&m_Cube3);
	m_PSelectionWheel.AddPlacement(&m_PCube3);
	m_Cube4.Init(1.f, &m_MatRed);
	m_PCube4.AddGeo(&m_Cube4);
	m_PSelectionWheel.AddPlacement(&m_PCube4);
	m_cubes.push_back(&m_PCube1);
	m_cubes.push_back(&m_PCube2);
	m_cubes.push_back(&m_PCube3);
	m_cubes.push_back(&m_PCube4);

	// Verteilen der Cubes auf dem Kreis
	CHVector vectorToCar(eAxisX);
	vectorToCar *= m_wheelradius;
	float angleDivided = TWOPI / m_cubes.size();
	CHMat matRotate;

	for (float i = 0; i < m_cubes.size(); i++)
	{
		matRotate.Rotate(eAxisY, angleDivided * i);
		vectorToCar = matRotate * vectorToCar;
		m_cubes.at(i)->Translate(vectorToCar);
	}

	// Setzen des DownAngles der Camera auf das Objekt im Fokus
	m_selectionDownAngle = tanh(abs(m_PSelectionAnchor.GetPos().y) / (abs(m_PSelectionAnchor.GetPos().x) - m_wheelradius));
}

void MainMenu::update(float fTime, float fTimeDelta)
{
	if (PlayPressed())
	{
		m_changeScene = true;
		m_nextScene = game;
	}

	if (SelectPressed() && m_OvMenu.IsOn())
	{
		m_OvMenu.SwitchOff();
		m_selectTransition = true;
	}

	if (m_OvSelectMenu.IsOn() && !m_rotateleft && !m_rotateright)
	{
		if (m_BConfirm.IsClicked())
		{
			m_OvSelectMenu.SwitchOff();
			m_mainTransition = true;
		}
		if (m_BRight.IsClicked())
		{
			m_rotateright = true;
			m_carindex++;
			if (m_carindex == m_cubes.size())
			{
				m_carindex = 0;
			}
		}
		else if (m_BLeft.IsClicked())
		{
			m_rotateleft = true;
			m_carindex--;
			if (m_carindex < 0)
			{
				m_carindex += m_cubes.size();
			}
		}
	}

	if (m_rotateleft)
	{
		m_rotationstart += fTimeDelta;
		float transitionamount = fTimeDelta / m_rotationduration;
		m_PSelectionWheel.RotateYDelta(transitionamount * -(TWOPI / m_cubes.size()));
		if (m_rotationstart >= m_rotationduration)
		{
			m_rotateleft = false;
			m_PSelectionWheel.RotateY((float)m_carindex * (TWOPI / m_cubes.size()));
			m_rotationstart = 0.f;
		}
	}
	else if (m_rotateright)
	{
		m_rotationstart += fTimeDelta;
		float transitionamount = fTimeDelta / m_rotationduration;
		m_PSelectionWheel.RotateYDelta(transitionamount * (TWOPI / m_cubes.size()));
		if (m_rotationstart >= m_rotationduration)
		{
			m_rotateright = false;
			m_PSelectionWheel.RotateY((float)m_carindex * (TWOPI / m_cubes.size()));
			m_rotationstart = 0.f;
		}
	}

	if (m_selectTransition)
	{
		m_transTimer += fTimeDelta;
		float transitionamount = m_transTimer / m_transitionTime;
		m_PCamera.RotateY(transitionamount * HALFPI);
		m_PCamera.RotateZDelta(transitionamount * m_selectionDownAngle);
		if (transitionamount >= 1.f)
		{
			m_selectTransition = false;
			m_PCamera.RotateY(HALFPI);
			m_PCamera.RotateZDelta(m_selectionDownAngle);
			m_OvSelectMenu.SwitchOn();
			m_transTimer = 0.f;
		}
	}
	if (m_mainTransition)
	{
		m_transTimer += fTimeDelta;
		float transitionamount = 1.f - (m_transTimer / m_transitionTime);
		m_PCamera.RotateY(transitionamount * HALFPI);
		m_PCamera.RotateZDelta(transitionamount * m_selectionDownAngle);
		if (transitionamount <= 0.f)
		{
			m_mainTransition = false;
			m_PCamera.RotateY(0.f);
			m_OvMenu.SwitchOn();
			m_transTimer = 0.f;
		}
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

bool MainMenu::SelectPressed()
{
	return m_BSelectCar.IsClicked();
}

bool MainMenu::OptionsPressed()
{
	return m_BOptions.IsClicked();
}

bool MainMenu::ExitPressed()
{
	return m_BExit.IsClicked();
}
