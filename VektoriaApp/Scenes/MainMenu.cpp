#include "MainMenu.h"

void MainMenu::selectCar(int carID)
{
	m_PSelectSuperCar.SwitchOff();
	m_PSelectTruck.SwitchOff();
	m_PSelectBus.SwitchOff();
	m_PSelectOldCar.SwitchOff();
	switch (carID)
	{
	case 0:
		m_PSelectSuperCar.SwitchOn();
		m_PSelectedCar = &m_PSelectSuperCar;
		break;
	case 1:
		m_PSelectTruck.SwitchOn();
		m_PSelectedCar = &m_PSelectTruck;
		break;
	case 2:
		m_PSelectBus.SwitchOn();
		m_PSelectedCar = &m_PSelectBus;
		break;
	case 3:
		m_PSelectOldCar.SwitchOn();
		m_PSelectedCar = &m_PSelectOldCar;
		break;
	default:
		break;
	}
}

void MainMenu::setGameScene(GameScene* game)
{
	m_GameScene = game;
}

void MainMenu::Init(CScene* scene, CViewport* viewport, CDeviceCursor* cursor, CDeviceKeyboard* keyboard)
{
	m_Cursor = cursor;
	m_Keyboard = keyboard;
	m_Scene = scene;
	m_Viewport = viewport;

	// Camera Init
	m_Camera.Init(QUARTERPI);
	m_PCamera.AddCamera(&m_Camera);
	m_Scene->AddPlacement(&m_PCamera);

	// Skymanager Init
	//m_SkyManager.init(m_Scene, &m_PCamera, &m_Camera);
	m_Scene->SetSkyTimeOfDay(0.1f);

	// Laden der Schriftart
	m_FontLucRed.LoadPreset("LucidaConsoleRed");
	m_FontLucRed.SetChromaKeyingOn();

	// Laden der Materiale
	m_MatDark.MakeTextureSprite("textures\\PrototypeTextures\\Dark\\texture_06.png");
	m_MatGreen.MakeTextureSprite("textures\\PrototypeTextures\\Green\\texture_06.png");
	m_MatButtonHovered.MakeTextureSprite("textures\\Buttons\\Button_Pressed.png");
	m_MatButton.MakeTextureSprite("textures\\Buttons\\Button.png");
	m_MatRightArrow.MakeTextureSprite("textures\\Arrows\\Right_Arrow.png");
	m_MatRightArrowHovered.MakeTextureSprite("textures\\Arrows\\Right_Arrow_Hovered.png");
	m_MatLeftArrow.MakeTextureSprite("textures\\Arrows\\Left_Arrow.png");
	m_MatLeftArrowHovered.MakeTextureSprite("textures\\Arrows\\Left_Arrow_Hovered.png");
	m_MatGround.MakeTextureDiffuse("textures\\Menu_Ground\\Ground_BaseColor.png");
	m_MatGround.MakeTextureBump("textures\\Menu_Ground\\Ground_Normal.png");
	m_MatGround.MakeTextureSpecular("textures\\Ground_Menu\\Ground_Specular.png");

	// Dark für den Boden
	//this->AddPlacement(&m_pDark);
	//m_gDark.SetAxis(eAxisY);
	//m_gDark.Init(100.f, &m_MatDark);
	//m_pDark.AddGeo(&m_gDark);
	//m_pDark.TranslateY(-100.f);
	// Green für Wand in positive Z-Richtung
	//this->AddPlacement(&m_pGreen);
	//m_gGreen.SetAxis(eAxisZ);
	//m_gGreen.Init(100.f, &m_MatGreen);
	//m_pGreen.AddGeo(&m_gGreen);
	//m_pGreen.RotateY(PI);
	//m_pGreen.TranslateZDelta(100.f);
	// Orange für Wand in negativer Z-Richtung
	//this->AddPlacement(&m_pOrange);
	//m_gOrange.SetAxis(eAxisZ);
	//m_gOrange.Init(100.f, &m_MatOrange);
	//m_pOrange.AddGeo(&m_gOrange);
	//m_pOrange.TranslateZDelta(-100.f);
	// Purple für Wand in positiver X-Richtung
	//this->AddPlacement(&m_pPurple);
	//m_gPurple.SetAxis(eAxisX);
	//m_gPurple.Init(100.f, &m_MatPurple);
	//m_pPurple.AddGeo(&m_gPurple);
	//m_pPurple.RotateY(PI);
	//m_pPurple.TranslateXDelta(100.f);
	// Red für Wand in negativer X-Richtung
	//this->AddPlacement(&m_pRed);
	//m_gRed.SetAxis(eAxisX);
	//m_gRed.Init(100.f, &m_MatRed);
	//m_pRed.AddGeo(&m_gRed);
	//m_pRed.TranslateXDelta(-100.f);

	// Menu Aufbau
	m_Viewport->AddOverlay(&m_OvRoot);
	m_OvRoot.InitFull(&m_MatDark);
	m_OvRoot.SetLayer(1.f);

	m_OvRoot.AddOverlay(&m_OvCover);
	m_OvCover.InitFull(&m_MatDark);
	m_OvCover.SetLayer(1.f);

	m_OvCover.AddOverlay(&m_OvMenu);
	m_OvMenu.Init(&m_MatDark, CFloatRect(0.1f, 0.2f, 0.3f, 0.6f));
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
	m_BPlay.SetMaterialNormal(m_MatButton);
	m_BPlay.SetMaterialHover(m_MatButtonHovered);
	m_BPlay.SetMaterialClick(m_MatButton);
	m_BPlay.SetInnerOn();

	// Select Car-Button
	m_OvMenu.AddOverlay(&m_BSelectCar);
	m_BSelectCar.Init(m_Cursor, &m_FontLucRed, CFloatRect(0.f, sizeButtons + distanceButtons, 1.f, sizeButtons));
	m_BSelectCar.SetLabel("SELECT CAR");
	m_BSelectCar.SetMaterialNormal(m_MatButton);
	m_BSelectCar.SetMaterialHover(m_MatButtonHovered);
	m_BSelectCar.SetMaterialClick(m_MatButton);
	m_BSelectCar.SetInnerOn();

	// Options-Button
	m_OvMenu.AddOverlay(&m_BOptions);
	m_BOptions.Init(m_Cursor, &m_FontLucRed, CFloatRect(0.f, (sizeButtons + distanceButtons) * 2.f, 1.f, sizeButtons));
	m_BOptions.SetLabel("OPTIONS");
	m_BOptions.SetMaterialNormal(m_MatButton);
	m_BOptions.SetMaterialHover(m_MatButtonHovered);
	m_BOptions.SetMaterialClick(m_MatButton);
	m_BOptions.SetInnerOn();

	// Exit-Button
	m_OvMenu.AddOverlay(&m_BExit);
	m_BExit.Init(m_Cursor, &m_FontLucRed, CFloatRect(0.f, (sizeButtons + distanceButtons) * 3.f, 1.f, sizeButtons));
	m_BExit.SetLabel("EXIT");
	m_BExit.SetMaterialNormal(m_MatButton);
	m_BExit.SetMaterialHover(m_MatButtonHovered);
	m_BExit.SetMaterialClick(m_MatButton);
	m_BExit.SetInnerOn();

	// Confirm-Button
	m_OvSelectMenu.AddOverlay(&m_BConfirm);
	m_BConfirm.Init(m_Cursor, &m_FontLucRed, CFloatRect(0.3f, 0.7f, 0.4f, 0.2f));
	m_BConfirm.SetLabel("CONFIRM");
	m_BConfirm.SetMaterialNormal(m_MatButton);
	m_BConfirm.SetMaterialHover(m_MatButtonHovered);
	m_BConfirm.SetMaterialClick(m_MatButton);
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
	m_PSelectionAnchor.Translate(-100.f, -10.f, 0.f);

	CFileWavefront file;
	m_GRoad = file.LoadGeo("models\\road\\RoadTile_Basic.obj");
	m_PSelectionAnchor.AddPlacement(&m_PRoad);
	m_PRoad.AddGeo(m_GRoad);
	m_PRoad.TranslateZ(-20.f);
	m_PRoad.RotateY(HALFPI);

	// Cars Init
	m_SportsCar.Init(&m_PSportsCar, &m_PCamera, 0);
	m_MonsterTruck.Init(&m_PMonsterTruck, &m_PCamera, 1);
	m_Bus.Init(&m_PBus, &m_PCamera, 2);
	m_OldCar.Init(&m_POldCar, &m_PCamera, 3);

	// SuperCar (ID = 0)
	m_PSelectionWheel.AddPlacement(&m_PSportsCar);
	m_cars.push_back(&m_PSportsCar);

	// MonsterTruck (ID = 1)
	m_PSelectionWheel.AddPlacement(&m_PMonsterTruck);
	m_cars.push_back(&m_PMonsterTruck);

	// Bus (ID = 2)
	m_PSelectionWheel.AddPlacement(&m_PBus);

	// OldCar (ID = 3)
	m_PSelectionWheel.AddPlacement(&m_POldCar);
	m_cars.push_back(&m_POldCar);
	m_cars.push_back(&m_PBus);

	// Selected Car
	m_GDisplayQuad.Init(25.f, &m_MatGround);
	m_PDisplayQuad.AddGeo(&m_GDisplayQuad);
	m_PDisplayQuad.RotateX(-HALFPI);
	m_PDisplayQuad.TranslateYDelta(-1.6f);
	m_PMainCar.AddPlacement(&m_PDisplayQuad);
	this->AddPlacement(&m_PMainCar);
	m_PMainCar.Translate(5.f, -1.f, -30.f);
	m_PSelectSuperCar.Copy(m_PSportsCar);
	m_PSelectTruck.Copy(m_PMonsterTruck);
	m_PSelectBus.Copy(m_PBus);
	m_PSelectOldCar.Copy(m_POldCar);
	selectCar(m_carindex);
	m_PMainCar.AddPlacement(&m_PSelectSuperCar);
	m_PMainCar.AddPlacement(&m_PSelectTruck);
	m_PMainCar.AddPlacement(&m_PSelectBus);
	m_PMainCar.AddPlacement(&m_PSelectOldCar);

	// Verteilen der Autos auf dem Auswahlkreis
	CHVector vectorToCar(eAxisX);
	vectorToCar *= m_wheelradius;
	float angleDivided = TWOPI / m_cars.size();
	CHMat matRotate;

	for (float i = 0; i < m_cars.size(); i++)
	{
		matRotate.Rotate(eAxisY, -angleDivided * i);
		vectorToCar = matRotate * vectorToCar;
		m_cars.at(i)->Translate(vectorToCar);
		m_cars.at(i)->TranslateYDelta(1.6f);
	}

	// Setzen des DownAngles der Camera auf das Objekt im Fokus
	m_selectionDownAngle = tanh(abs(m_PSelectionAnchor.GetPos().y) / (abs(m_PSelectionAnchor.GetPos().x) - m_wheelradius));
}

void MainMenu::update(float fTime, float fTimeDelta)
{
	if (PlayPressed())
	{
		m_changeScene = true;
		m_doSetup = true;
		m_nextScene = game;
		m_GameScene->setcarID(m_carindex);
	}

	if (SelectPressed() && m_OvMenu.IsOn())
	{
		m_OvMenu.SwitchOff();
		m_selectTransition = true;
	}

	if (m_OvMenu.IsOn())
	{
		m_PSelectedCar->RotateYDelta(0.25f * fTimeDelta);
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
			if (m_carindex == m_cars.size())
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
				m_carindex += m_cars.size();
			}
		}
	}

	if (m_rotateleft)
	{
		m_rotationstart += fTimeDelta;
		float transitionamount = fTimeDelta / m_rotationduration;
		m_PSelectionWheel.RotateYDelta(transitionamount * -(TWOPI / m_cars.size()));
		if (m_rotationstart >= m_rotationduration)
		{
			m_rotateleft = false;
			m_PSelectionWheel.RotateY((float)m_carindex * (TWOPI / m_cars.size()));
			m_rotationstart = 0.f;
		}
	}
	else if (m_rotateright)
	{
		m_rotationstart += fTimeDelta;
		float transitionamount = fTimeDelta / m_rotationduration;
		m_PSelectionWheel.RotateYDelta(transitionamount * (TWOPI / m_cars.size()));
		if (m_rotationstart >= m_rotationduration)
		{
			m_rotateright = false;
			m_PSelectionWheel.RotateY((float)m_carindex * (TWOPI / m_cars.size()));
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
			selectCar(m_carindex);
		}
	}
}

void MainMenu::setup()
{
	m_Scene->SetSkyTimeOfDay(0.1f);
	m_doSetup = false;
}

void MainMenu::reset()
{
	m_changeScene = false;
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
