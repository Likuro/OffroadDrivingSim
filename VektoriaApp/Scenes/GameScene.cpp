#include "GameScene.h"

void GameScene::Init(CScene* scene, CViewport* viewport, CDeviceCursor* cursor, CDeviceKeyboard* keyboard)
{
	m_Cursor = cursor;
	m_Keyboard = keyboard;
	m_Scene = scene;
	m_Viewport = viewport;

	// Camera Init
	m_Camera.Init(QUARTERPI);
	m_PCamera.AddCamera(&m_Camera);
	m_Scene->AddPlacement(&m_PCamera);

	// Prototype Textures für Camera Debugging
	m_Dark.MakeTextureDiffuse("textures\\PrototypeTextures\\Dark\\texture_06.png");
	m_Green.MakeTextureDiffuse("textures\\PrototypeTextures\\Green\\texture_06.png");
	m_Orange.MakeTextureDiffuse("textures\\PrototypeTextures\\Orange\\texture_06.png");
	m_Purple.MakeTextureDiffuse("textures\\PrototypeTextures\\Purple\\texture_06.png");
	m_Red.MakeTextureDiffuse("textures\\PrototypeTextures\\Red\\texture_06.png");

	// Button Materials
	m_MatButtonHovered.MakeTextureSprite("textures\\Buttons\\Button_Pressed.png");
	m_MatButton.MakeTextureSprite("textures\\Buttons\\Button.png");

	// Laden der Schriftart
	m_FontLucRed.LoadPreset("LucidaConsoleRed");
	m_FontLucRed.SetChromaKeyingOn();

	m_Viewport->SetMistOn(true);
	m_Viewport->SetMistStartDistance(roadTilelength * (anzahlRoadTiles / 2));
	m_Viewport->SetMistStrength(0.01f); //1.0 / ((float)roadTilelength * (float)anzahlRoadTiles)
	m_Viewport->SetMistHeightMax(3750.f);
	m_Viewport->SetMistHeightMin(-5000.f);

	// OvRoot Init
	m_Viewport->AddOverlay(&m_OvRoot);
	m_OvRoot.InitFull(&m_Dark);
	m_OvRoot.SetLayer(1.f);

	// Drive
	m_SportsCar.Init(this, &m_PCamera, 0);
	m_SportsCar.GetMainPos()->SwitchOff();
	m_SportsController.Init(m_Scene, m_Viewport, &m_SportsCar);

	m_MonsterTruck.Init(this, &m_PCamera, 1);
	m_MonsterTruck.GetMainPos()->SwitchOff();
	m_MonsterController.Init(m_Scene, m_Viewport, &m_MonsterTruck);

	m_Bus.Init(this, &m_PCamera, 2);
	m_Bus.GetMainPos()->SwitchOff();
	m_BusController.Init(m_Scene, m_Viewport, &m_Bus);

	m_OldCar.Init(this, &m_PCamera, 3);
	m_OldCar.GetMainPos()->SwitchOff();
	m_OldController.Init(m_Scene, m_Viewport, &m_OldCar);

	selectCar(0);

	// PauseMenu
	m_PauseMenu.Init(&m_OvRoot, m_Cursor);

	// EndScreen
	m_MYouDied.MakeTextureSprite("textures\\EndScreenYouDied.png");
	m_OvRoot.AddOverlay(&m_EndScreen);
	m_EndScreen.InitFull(&m_MYouDied);
	m_EndScreen.SetLayer(0.99f);
	m_EndScreen.SwitchOff();
	m_EndScreen.AddOverlay(&m_BEndGame);
	m_BEndGame.Init(m_Cursor, &m_FontLucRed, CFloatRect(0.3f, 0.7f, 0.4f, 0.2f));
	m_BEndGame.SetLabel("CLOSE GAME");
	m_BEndGame.SetMaterialNormal(m_MatButton);
	m_BEndGame.SetMaterialHover(m_MatButtonHovered);
	m_BEndGame.SetMaterialClick(m_MatButton);

	// ItemManager
	Items = new ItemManager(25, m_currentCar->GetMainPos(), m_dController, m_Root);

	// RoadMaster erstellen
	this->AddPlacement(&drivingScenePlacement);
	this->RoadMaster = new RoadManager;
	RoadMaster->init(&drivingScenePlacement, Items, m_Root);

	//SkyMaster erstellen
	this->SkyMaster = new SkyManager;
	SkyMaster->init(m_Scene, &m_TPCamera, &m_Camera);

	//ScoreManager erstellen
	this->ScoreMaster = new ScoreManager;
	ScoreMaster->init(&m_OvRoot);

	//Stats
	m_scoreFont.LoadPreset("LucidaConsoleRed");
	m_scoreFont.SetChromaKeyingOn();
	m_SpeedValue.Init(CFloatRect(0.5f, 0.05f, 0.15f, 0.05f), 10, &m_scoreFont);
	m_OvRoot.AddWriting(&m_SpeedValue);
	m_GasValue.Init(CFloatRect(0.8f, 0.85f, 0.15f, 0.05f), 10, &m_scoreFont);
	m_OvRoot.AddWriting(&m_GasValue);
	m_ClutchValue.Init(CFloatRect(0.1f, 0.85f, 0.15f, 0.05f), 10, &m_scoreFont);
	m_OvRoot.AddWriting(&m_ClutchValue);

	// Third-Person-Camera
	m_TPCamera.Init(100.f, 15.f, eAlignZAxisNegative, m_currentCar->GetMainPos(), &m_Camera);
	m_TPCamera.SetTranslationSensitivity(200.f);
	m_TPCamera.SetRotationSensitivity(2.f);
	this->AddPlacement(&m_TPCamera);

	// Healthbar
	m_HealthBar = new ProgressBar(&m_Orange, &m_OvRoot, m_dController->getHealth()->getMaxHealth(), m_dController->getHealth()->getHealth(), 0.7f, 0.9f, 0.25f, 0.05f);
	// Boostbar
	m_BoostBar = new ProgressBar(&m_Green, &m_OvRoot, m_dController->getBoost()->getMaxBoost(), m_dController->getBoost()->getBoost(), 0.05f, 0.9f, 0.25f, 0.05f);

	//this->AddPlacement(&test);
	////testcube.Init(1.f, &m_Dark);
	////test.AddGeo(&testcube);
	//test.Translate(0.f, 0.f, -50.f);
	//test.AddPlacement(Items->getItem(health));
}

void GameScene::selectCar(int carID)
{
	if (m_currentCar != nullptr)
	{
		m_currentCar->GetMainPos()->SwitchOff();
	}
	switch (carID)
	{
	case 0:
		m_currentCar = &m_SportsCar;
		m_dController = &m_SportsController;
		break;
	case 1:
		m_currentCar = &m_MonsterTruck;
		m_dController = &m_MonsterController;
		break;
	case 2:
		m_currentCar = &m_Bus;
		m_dController = &m_BusController;
		break;
	case 3:
		m_currentCar = &m_OldCar;
		m_dController = &m_OldController;
		break;
	default:
		break;
	}
	m_currentCar->GetMainPos()->SwitchOn();
}

void GameScene::update(float fTime, float fTimeDelta)
{
	if (m_callOnceAfterTick && m_currentCar->GetMainPos()->GetAABB())
	{
		// Funktionen die nach dem ersten Tick aufgerufen werden sollen, aber dann nicht mehr
		m_callOnceAfterTick = false;
		Items->InitRays(m_currentCar->GetMainPos()->GetAABB());	// AABB des Players muss zu Beginn übergeben werden, um Strahlenbüschel zu nutzen
	}

	if (m_dController->getHealth()->isDead())
	{
		m_EndScreen.SwitchOn();
	}

	if (m_EndScreen.IsOn())
	{
		if (m_BEndGame.IsClicked())
		{
			exitGame();
		}
		return;
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
			m_doSetup = true;
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
	m_score = m_currentCar->GetMainPos()->GetPos().Dist(CHVector(0.f, 0.f, 0.f, 0.f));
	m_scoreWriting.PrintInt(m_score);

	// Zoom
	if (m_Keyboard->KeyPressed(DIK_UP))
	{
		if (m_Keyboard->KeyPressed(DIK_DOWN))
			m_TPCamera.zoom(fTimeDelta);
		else
			m_TPCamera.zoom(-fTimeDelta);
	}
	else if (m_Keyboard->KeyPressed(DIK_DOWN))
		m_TPCamera.zoom(fTimeDelta);

	// Car Input

	if (m_Keyboard->KeyDown(DIK_Q))
		m_dController->GearUp();
	if (m_Keyboard->KeyDown(DIK_F))
		m_dController->GearDown();

	if (m_Keyboard->KeyPressed(DIK_W))
		m_dController->Accelerate(fTimeDelta);
	else
		m_dController->Deaccelerate(fTimeDelta);
	//Rotations
	if (m_Keyboard->KeyPressed(DIK_D))
		m_dController->RotateRight(fTimeDelta);

	else if (m_Keyboard->KeyPressed(DIK_A))
		m_dController->RotateLeft(fTimeDelta);
	else
		m_dController->ResetRotation(fTimeDelta);
	//End Rotations
	if (m_Keyboard->KeyPressed(DIK_SPACE) || m_Keyboard->KeyPressed(DIK_S))
		m_dController->Brake();

	if (m_Keyboard->KeyUp(DIK_SPACE))
		m_dController->ReleaseBrakes();
	m_dController->ResetRotation(fTimeDelta);

	// Boosting
	if (m_Keyboard->KeyPressed(DIK_LSHIFT))
		m_dController->useBoost(fTimeDelta);
	else
		m_dController->setUseBoost(false);

	m_dController->Update(fTimeDelta, RoadMaster->getGravity(), RoadMaster->getGeosGround(), RoadMaster->getGeosFrontal());

	if (m_Keyboard->KeyDown(DIK_0))
		m_switchDebugCam = !m_switchDebugCam;
	if (!m_switchDebugCam)
		m_TPCamera.update(fTimeDelta);
	else
		m_Keyboard->PlaceWASD(m_TPCamera, fTimeDelta, true);

	m_SpeedValue.PrintFloat(m_dController->GetSpeed());
	m_GasValue.PrintFloat(m_dController->GetGas());
	m_ClutchValue.PrintInt(m_dController->GetGear());

	//RoadManager
	RoadMaster->tryupdate(fTimeDelta, m_currentCar->GetMainPos()->GetPos());

	// ItemManager
	Items->update(fTime, fTimeDelta);

	//ScoreManager
	ScoreMaster->update(m_currentCar->GetMainPos()->GetPos(), fTimeDelta);

	//SkyManager
	SkyMaster->update(ScoreMaster->getScore());

	//BoostBar
	m_BoostBar->update(m_dController->getBoost()->getBoost());

	m_dController->CheckCollisions(&RoadMaster->getGeosFrontal());
	//HealthBar
	m_HealthBar->update(m_dController->getHealth()->getHealth());
}

void GameScene::reset()
{
	m_changeScene = false;
}

void GameScene::setup()
{
	// Hier Methoden einfügen, die beim Szenenwechsel aufgerufen werden sollen
	//SkyMaster->update(ScoreMaster->getScore());
	selectCar(m_carID);
	m_dController->reignite();
	m_currentCar->GetMainPos()->Translate(CHVector(0.f, 0.f, 0.f));
	m_TPCamera.updateFollowObject(m_currentCar->GetMainPos());
	Items->updatePlayer(m_currentCar->GetMainPos(), m_dController);
	RoadMaster->resetRoad();
	ScoreMaster->resetScore();
	m_callOnceAfterTick = true;
	m_doSetup = false;
}

void GameScene::setcarID(int ID)
{
	m_carID = ID;
}

int GameScene::getcarID()
{
	return m_carID;
}
