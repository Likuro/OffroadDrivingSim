#include "GameScene.h"

void GameScene::Init(CDeviceCursor* cursor, CDeviceKeyboard* keyboard)
{
	m_Cursor = cursor;
	m_Keyboard = keyboard;

	// Camera Init
	m_Camera.Init(QUARTERPI);
	m_PCamera.AddCamera(&m_Camera);

	// Viewport Init
	m_Viewport.InitFull(&m_Camera);

	// Prototype Textures für Camera Debugging
	m_Dark.MakeTextureDiffuse("textures\\PrototypeTextures\\Dark\\texture_06.png");
	m_Green.MakeTextureDiffuse("textures\\PrototypeTextures\\Green\\texture_06.png");
	m_Orange.MakeTextureDiffuse("textures\\PrototypeTextures\\Orange\\texture_06.png");
	m_Purple.MakeTextureDiffuse("textures\\PrototypeTextures\\Purple\\texture_06.png");
	m_Red.MakeTextureDiffuse("textures\\PrototypeTextures\\Red\\texture_06.png");

	// Third-Person-Camera
	m_TPCamera.Init(25.f, 4.f, eAlignObjDir, m_Car.GetMainPos(), &m_Camera);
	this->AddPlacement(&m_TPCamera);

	m_Viewport.SetMistOn(true);
	//m_zv.SetMistStartDistance(roadTilelength*(anzahlRoadTiles/2));
	m_Viewport.SetMistStrength(1.0 / ((float)roadTilelength * (float)anzahlRoadTiles));

	// Healthbar
	Health = new HealthBar(&m_Orange, &m_Viewport, 100, 100, 0.7f, 0.9f, 0.25f, 0.05f);
	// Speedometer
	Speedometer = new ProgressBar(&m_Green, &m_Viewport, 100, 0, 0.05f, 0.9f, 0.25f, 0.05f);

	// PauseMenu
	m_PauseMenu.Init(&m_Viewport, m_Cursor);

	// ItemManager
	Items = new ItemManager(25, m_Car.GetMainPos());

	// RoadMaster erstellen
	this->AddPlacement(&drivingScenePlacement);
	this->RoadMaster = new RoadManager;
	RoadMaster->init(&drivingScenePlacement, Items);

	//SkyMaster erstellen
	this->SkyMaster = new SkyManager;
	SkyMaster->init(this, &m_PCamera);

	//ScoreManager erstellen
	this->ScoreMaster = new ScoreManager;
	ScoreMaster->init(&m_Viewport);

	//Stats
	m_scoreFont.LoadPreset("LucidaConsoleRed");
	m_scoreFont.SetChromaKeyingOn();
	m_SpeedValue.Init(CFloatRect(0.5f, 0.05f, 0.15f, 0.05f), 10, &m_scoreFont);
	m_Viewport.AddWriting(&m_SpeedValue);
	m_GasValue.Init(CFloatRect(0.8f, 0.85f, 0.15f, 0.05f), 10, &m_scoreFont);
	m_Viewport.AddWriting(&m_GasValue);
	m_ClutchValue.Init(CFloatRect(0.1f, 0.85f, 0.15f, 0.05f), 10, &m_scoreFont);
	m_Viewport.AddWriting(&m_ClutchValue);

	//Terrain
	this->AddPlacement(&m_zpTerrain);
	m_zpTerrain.AddGeo(&m_terrain);
	m_terrain.InitQuick(100000, 100000, 10, false, &m_Green, 300, 300, 0, 0, 10, 10);
	m_zgsColTerrain.Add(&m_terrain);
	m_zpTerrain.TranslateY(-1000);

	//Drive
	m_Car.Init(this, &m_PCamera, &m_Green, 0.8, 0.2, 200);
	m_dController.Init(this, &m_Viewport, &m_Car);
}

void GameScene::update(float fTime, float fTimeDelta)
{
	//if (m_callOnceAfterTick && m_zpSphere.GetAABB() != nullptr)
	//{
	//	// Funktionen die nach dem ersten Tick aufgerufen werden sollen, aber dann nicht mehr
	//	m_callOnceAfterTick = false;
	//	Items->InitRays(m_zpSphere.GetAABB());	// AABB des Players muss zu Beginn übergeben werden, um Strahlenbüschel zu nutzen
	//}

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
			// m_PauseMenu.SwitchOff();
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
	m_score = m_Car.GetMainPos()->GetPos().Dist(CHVector(0.f, 0.f, 0.f, 0.f));
	m_scoreWriting.PrintInt(m_score);

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


	if (m_Keyboard->KeyDown(DIK_Q))
		m_dController.GearUp();
	if (m_Keyboard->KeyDown(DIK_F))
		m_dController.GearDown();



	if (m_Keyboard->KeyPressed(DIK_W))
		m_dController.Accelerate(fTimeDelta);
	else
		m_dController.Deaccelerate(fTimeDelta);
	//Rotations
	if (m_Keyboard->KeyPressed(DIK_D))
		m_dController.RotateRight(fTimeDelta);

	else if (m_Keyboard->KeyPressed(DIK_A))
		m_dController.RotateLeft(fTimeDelta);
	else
		m_dController.ResetRotation(fTimeDelta);
	//End Rotations
	if (m_Keyboard->KeyPressed(DIK_SPACE) || m_Keyboard->KeyPressed(DIK_S))
		m_dController.Brake();

	if (m_Keyboard->KeyUp(DIK_SPACE))
		m_dController.ReleaseBrakes();
	m_dController.ResetRotation(fTimeDelta);

	m_dController.Update(fTimeDelta, m_zgsColTerrain, RoadMaster->getGeosGround(), RoadMaster->getGeosFrontal());
	m_TPCamera.update(fTimeDelta);

	m_SpeedValue.PrintFloat(m_dController.GetSpeed());
	m_GasValue.PrintFloat(m_dController.GetGas());
	m_ClutchValue.PrintInt(m_dController.GetGear());

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

	//RoadManager
	RoadMaster->tryupdate(fTimeDelta, m_Car.GetMainPos()->GetPos());

	// ItemManager
	Items->update(fTime, fTimeDelta);

	//ScoreManager
	ScoreMaster->update(m_Car.GetMainPos()->GetPos(), fTimeDelta);

	//SkyManager
	SkyMaster->update(ScoreMaster->getScore());
}

void GameScene::reset()
{
	RoadMaster->resetRoad();
	m_changeScene = false;
}
