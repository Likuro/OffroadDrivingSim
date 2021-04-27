#include "GameScene.h"

void GameScene::Init(CDeviceCursor* cursor, CDeviceKeyboard* keyboard)
{
	m_Cursor = cursor;
	m_Keyboard = keyboard;

	// Camera Init
	m_Camera.Init(QUARTERPI);
	m_PCamera.AddCamera(&m_Camera);
	this->SetSkyOn(&m_PCamera, true);

	// Viewport Init
	m_Viewport.InitFull(&m_Camera);

	// Neues cooles Licht
	this->AddPlacement(&m_RadialLightPlace);
	m_RadialLight.Init(CColor(1.f, 1.f, 1.f), 0.1f);
	m_RadialLightPlace.AddLightRadial(&m_RadialLight);
	m_RadialLightPlace.TranslateY(100.f);

	// Prototype Textures für Camera Debugging
	m_Dark.MakeTextureDiffuse("textures\\PrototypeTextures\\Dark\\texture_06.png");
	m_Green.MakeTextureDiffuse("textures\\PrototypeTextures\\Green\\texture_06.png");
	m_Orange.MakeTextureDiffuse("textures\\PrototypeTextures\\Orange\\texture_06.png");
	m_Purple.MakeTextureDiffuse("textures\\PrototypeTextures\\Purple\\texture_06.png");
	m_Red.MakeTextureDiffuse("textures\\PrototypeTextures\\Red\\texture_06.png");

	// Dummy Kugel
	this->AddPlacement(&m_zpSphere);
	m_zgSphere.Init(1.f, &m_Red, 50, 50);
	m_zpSphere.SetTranslationSensitivity(50.f);				// Geschwindigkeit der Kugel
	m_zpSphere.SetRotationSensitivity(2.f);
	m_zpSphere.AddGeo(&m_zgSphere);
	m_zpSphere.EnableAABBs();

	// Third-Person-Camera
	m_TPCamera.Init(50.f, 10.f, eAlignObjDir, &m_zpSphere, &m_Camera);
	this->AddPlacement(&m_TPCamera);

	// Healthbar
	Health = new HealthBar(&m_Orange, &m_Viewport, 100, 100, 0.7f, 0.9f, 0.25f, 0.05f);
	// Speedometer
	Speedometer = new ProgressBar(&m_Green, &m_Viewport, 100, 0, 0.05f, 0.9f, 0.25f, 0.05f);
	// PauseMenu
	m_PauseMenu.Init(&m_Viewport, m_Cursor);
	// ItemManager
	Items = new ItemManager(25, &m_zpSphere);

	// RoadMaster erstellen
	this->AddPlacement(&drivingScenePlacement);
	this->RoadMaster = new RoadManager;
	RoadMaster->init(&drivingScenePlacement, Items);

	// Score
	m_scoreFont.LoadPreset("LucidaConsoleRed");
	m_scoreFont.SetChromaKeyingOn();
	m_scoreWriting.Init(CFloatRect(0.825f, 0.05f, 0.15f, 0.05f), 10, &m_scoreFont);
	m_Viewport.AddWriting(&m_scoreWriting);
	m_scoreWriting.PrintInt(m_score);
}

void GameScene::update(float fTime, float fTimeDelta)
{
	if (m_callOnceAfterTick && m_zpSphere.GetAABB() != nullptr)
	{
		// Funktionen die nach dem ersten Tick aufgerufen werden sollen, aber dann nicht mehr
		m_callOnceAfterTick = false;
		Items->InitRays(m_zpSphere.GetAABB());	// AABB des Players muss zu Beginn übergeben werden, um Strahlenbüschel zu nutzen
	}

	if (m_PauseMenu.IsOn())
	{
		if (m_PauseMenu.ContinuePressed())
		{
			m_PauseMenu.SwitchOff();
		}
		if (m_PauseMenu.ExitPressed())
		{
			m_nextScene = main;
			m_changeScene = true;
			m_PauseMenu.SwitchOff();
		}
	}
	if (m_Keyboard->KeyDown(DIK_P))
	{
		if (m_PauseMenu.IsOn())
		{
			m_PauseMenu.SwitchOff();
		}
		else
		{
			m_PauseMenu.SwitchOn();
		}
	}

	if (m_PauseMenu.IsOn())
	{
		return;
	}

	timetick++;

	// Score
	m_score = m_zpSphere.GetPos().Dist(CHVector(0.f, 0.f, 0.f, 0.f));
	m_scoreWriting.PrintInt(m_score);

	// Tastatur Steuerung
	if (m_Keyboard->KeyPressed(DIK_W))
	{
		if (m_Keyboard->KeyPressed(DIK_S))
			fSW = 0.f;
		else
			fSW = -1.f;
	}
	else if (m_Keyboard->KeyPressed(DIK_S))
		fSW = 1.f;
	else
		fSW = 0.f;
	// Hoch/Runter Verschiebung
	if (m_Keyboard->KeyPressed(DIK_LSHIFT))
	{
		if (m_Keyboard->KeyPressed(DIK_SPACE))
			fFR = 0.f;
		else
			fFR = -1.f;
	}
	else if (m_Keyboard->KeyPressed(DIK_SPACE))
		fFR = 1.f;
	else
		fFR = 0.f;
	// Links/Rechts Drehung
	if (m_Keyboard->KeyPressed(DIK_A))
	{
		if (m_Keyboard->KeyPressed(DIK_D))
			fLR = 0.f;
		else
			fLR = -1.f;
	}
	else if (m_Keyboard->KeyPressed(DIK_D))
		fLR = 1.f;
	else
		fLR = 0.f;
	// Zoom
	if (m_Keyboard->KeyPressed(DIK_UP))
	{
		if (m_Keyboard->KeyPressed(DIK_DOWN))
			m_TPCamera.zoom(0.4f * fTimeDelta);
		else
			m_TPCamera.zoom(-0.4f * fTimeDelta);
	}
	else if (m_Keyboard->KeyPressed(DIK_DOWN))
		m_TPCamera.zoom(0.4f * fTimeDelta);

	m_zpSphere.MoveTerrain(fTimeDelta, fAD, fSW, fFR, fLR, fUD, RoadMaster->getGeosFrontal(), RoadMaster->getGeosGround(), fHeightEye, fHeightRay, hitpointCollision, hitpointGround, true, eMoveFlightKind_Ballistic);
	m_TPCamera.update(fTimeDelta);

	// HealthBar Test
	if (m_Keyboard->KeyDown(DIK_Q))
	{
		Health->changeHealth(-10.f);
	}

	// Speedometer Test
	if (m_Keyboard->KeyPressed(DIK_E))
	{
		Speedometer->progressValue += 0.05f;
		Speedometer->update();
	}
	else
	{
		Speedometer->progressValue -= 0.005f;
		Speedometer->update();
	}

	// nur alle 5k Ticks -- RoadMaster
	if (timetick == 5000) {

		this->RoadMaster->updateRoad();

		timetick = 0;
	}

	// ItemManager
	Items->update(fTime, fTimeDelta);
}
