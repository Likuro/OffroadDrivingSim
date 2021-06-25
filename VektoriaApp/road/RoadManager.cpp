
#include "RoadManager.h"

RoadManager::~RoadManager()
{
	delete myPerlinNoise;
}

void RoadManager::init(CPlacement* tmp_scene, ItemManager* tmp_myItemManager, CRoot* tmp_myRoot )
{
	myRoot = tmp_myRoot;
	srand(time(NULL));
	myPlacement = tmp_scene;
	myItemManager = tmp_myItemManager;
	specialSpawnChance = specialSpawnChanceSetting;

	activeSpawn = 0;
	timesSpawned = 1;
	lastTile = 0;
	nextTile = 0;
	lane = 0;
	lanehight = 0;
	sinceLastSpecial = 0;
	roadtime = 0;
	lastSpawn = anzahlRoadTiles;
	walltime = 0;
	lastspecialTile = 0;
	nextspecialTile = 0;
	terrainSpawnCounter = 0;
	count = 0;

	//Perlin Noise
	myPerlinNoise = new CPerlin * [6];
	for (size_t i = 0; i < 6; i++)
	{
		myPerlinNoise[i] = new CPerlin(rand() % 1000, 1.f, 10, 0.6f, 0.8f, 0.f, 0.f, ePerlinInterpol_Standard, true);
	}


	myTerrainMaterial.MakeTextureDiffuse("textures\\PrototypeTextures\\Green\\texture_06.png");

	//Sandsturm laden & anhängen
	wallofCOLOR.MakeTextureDiffuse("textures\\Sandstorm_cube.png");
	wallofCOLOR.SetTransparency(1.0f);
	wallofEMITTER.LoadPreset("Sandstorm_ver2");
	wallofSTORM.Init(roadTilewidth * RoadTileBoundingBox, roadTileheight * RoadTileBoundingBox, &wallofCOLOR);
	wallofDEATH.AddGeo(&wallofSTORM);
	wallofSTORM.AddEmitter(&wallofEMITTER);
	myPlacement->AddPlacement(&wallofDEATH);
	wallofDEATH.TranslateZ(400.0f);
	
	//Emitter Settings
	
	//wallofEMITTER.SetRate(3 * RoadTileBoundingBox * RoadTileBoundingBox);
	wallofEMITTER.SetTimeToWait(0.1f);
	wallofEMITTER.SetTimeToCome(2.0f);
	wallofEMITTER.SetTimeToStay(20.0f);
	wallofEMITTER.SetTimeToFade(0.5f);

	//Materials laden
	basicRoadTile.MakeTextureDiffuse("textures/RoadTiles/BasicTexture_Combined/BasicTexture_Base_Color.PNG");
	basicRoadTile.MakeTextureBump("textures/RoadTiles/BasicTexture_Combined/BasicTexture_Normal.PNG");
	basicRoadTile.MakeTextureSpecular("textures/RoadTiles/BasicTexture_Combined/BasicTexture_Roughness.PNG");
	myRoot->AddMaterial(&basicRoadTile);

	curveRoadTile.MakeTextureDiffuse("textures/RoadTiles/CurveTexture_Combined/CurveTexture_Base_Color.PNG");
	curveRoadTile.MakeTextureBump("textures/RoadTiles/CurveTexture_Combined/CurveTexture_Normal.PNG");
	curveRoadTile.MakeTextureSpecular("textures/RoadTiles/CurveTexture_Combined/CurveTexture_Roughness.PNG");
	myRoot->AddMaterial(&curveRoadTile);

	upDownRoadTile.MakeTextureDiffuse("textures/RoadTiles/UpDownTexture_Combined/UpDownTexture_Base_Color.PNG");
	upDownRoadTile.MakeTextureBump("textures/RoadTiles/UpDownTexture_Combined/UpDownTexture_Normal.PNG");
	upDownRoadTile.MakeTextureSpecular("textures/RoadTiles/UpDownTexture_Combined/UpDownTexture_Roughness.PNG");
	myRoot->AddMaterial(&upDownRoadTile);

	upDownCurveRoadTile.MakeTextureDiffuse("textures/RoadTiles/UpDownCurveTexture_Combined/UpDownCurveTexture_Base_Color.PNG");
	upDownCurveRoadTile.MakeTextureBump("textures/RoadTiles/UpDownCurveTexture_Combined/UpDownCurveTexture_Normal.PNG");
	upDownCurveRoadTile.MakeTextureSpecular("textures/RoadTiles/UpDownCurveTexture_Combined/UpDownCurveTexture_Roughness.PNG");
	myRoot->AddMaterial(&upDownCurveRoadTile);
	
	//PrefabRoads laden
	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Basic/RoadTile_Basic0.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Basic/ground/RoadTile_Basic_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Basic_FrontalHB/RoadTile_Basic0_FrontalHB.obj");
	PrefabRoads[count] = new PrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f));
	PrefabRoads[count]->addMaterial(&basicRoadTile);
	count++;
	
	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Basic/RoadTile_Basic1.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Basic/ground/RoadTile_Basic_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Basic_FrontalHB/RoadTile_Basic1_FrontalHB.obj");
	PrefabRoads[count] = new PrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f));
	PrefabRoads[count]->addMaterial(&basicRoadTile);
	count++;
	
	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Basic/RoadTile_Basic2.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Basic/ground/RoadTile_Basic_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Basic_FrontalHB/RoadTile_Basic2_FrontalHB.obj");
	PrefabRoads[count] = new PrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f));
	PrefabRoads[count]->addMaterial(&basicRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Basic/RoadTile_Basic3.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Basic/ground/RoadTile_Basic_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Basic_FrontalHB/RoadTile_Basic3_FrontalHB.obj");
	PrefabRoads[count] = new PrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f));
	PrefabRoads[count]->addMaterial(&basicRoadTile);
	count++;
	
	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Basic/RoadTile_Basic4.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Basic/ground/RoadTile_Basic_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Basic_FrontalHB/RoadTile_Basic4_FrontalHB.obj");
	PrefabRoads[count] = new PrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f));
	PrefabRoads[count]->addMaterial(&basicRoadTile);
	count++;
	
	//Special PrefabRoads laden
	count = 0;
	//Curves L
	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve/RaodTiles_CurveL/RoadTile_Curve_L0.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve/RaodTiles_CurveL/ground/RoadTile_Curve_L_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), -1, 0);
	PrefabRoads[count]->addMaterial(&curveRoadTile);
	count++;
	
	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve/RaodTiles_CurveL/RoadTile_Curve_L1.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve/RaodTiles_CurveL/ground/RoadTile_Curve_L_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), -1, 0);
	PrefabRoads[count]->addMaterial(&curveRoadTile);
	count++;
	
	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve/RaodTiles_CurveL/RoadTile_Curve_L2.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve/RaodTiles_CurveL/ground/RoadTile_Curve_L_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), -1, 0);
	PrefabRoads[count]->addMaterial(&curveRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve/RaodTiles_CurveL/RoadTile_Curve_L3.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve/RaodTiles_CurveL/ground/RoadTile_Curve_L_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), -1, 0);
	PrefabRoads[count]->addMaterial(&curveRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve/RaodTiles_CurveL/RoadTile_Curve_L4.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve/RaodTiles_CurveL/ground/RoadTile_Curve_L_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), -1, 0);
	PrefabRoads[count]->addMaterial(&curveRoadTile);
	count++;

	//Curves R
	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve/RoadTiles_CurveR/RoadTile_Curve_R0.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve/RoadTiles_CurveR/ground/RoadTile_Curve_R_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), 1, 0);
	PrefabRoads[count]->addMaterial(&curveRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve/RoadTiles_CurveR/RoadTile_Curve_R1.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve/RoadTiles_CurveR/ground/RoadTile_Curve_R_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), 1, 0);
	PrefabRoads[count]->addMaterial(&curveRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve/RoadTiles_CurveR/RoadTile_Curve_R2.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve/RoadTiles_CurveR/ground/RoadTile_Curve_R_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), 1, 0);
	PrefabRoads[count]->addMaterial(&curveRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve/RoadTiles_CurveR/RoadTile_Curve_R3.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve/RoadTiles_CurveR/ground/RoadTile_Curve_R_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), 1, 0);
	PrefabRoads[count]->addMaterial(&curveRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve/RoadTiles_CurveR/RoadTile_Curve_R4.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve/RoadTiles_CurveR/ground/RoadTile_Curve_R_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), 1, 0);
	PrefabRoads[count]->addMaterial(&curveRoadTile);
	count++;

	//Down
	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown/RoadTile_Basic_Down/RoadTile_Basic_Down0.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown/RoadTile_Basic_Down/ground/RoadTile_Basic_Down_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown_FrontalHB/RoadTile_Basic_Down_FrontalHB/RoadTile_Basic_Down0_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 0, -1);
	PrefabRoads[count]->addMaterial(&upDownRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown/RoadTile_Basic_Down/RoadTile_Basic_Down1.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown/RoadTile_Basic_Down/ground/RoadTile_Basic_Down_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown_FrontalHB/RoadTile_Basic_Down_FrontalHB/RoadTile_Basic_Down1_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 0, -1);
	PrefabRoads[count]->addMaterial(&upDownRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown/RoadTile_Basic_Down/RoadTile_Basic_Down2.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown/RoadTile_Basic_Down/ground/RoadTile_Basic_Down_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown_FrontalHB/RoadTile_Basic_Down_FrontalHB/RoadTile_Basic_Down2_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 0, -1);
	PrefabRoads[count]->addMaterial(&upDownRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown/RoadTile_Basic_Down/RoadTile_Basic_Down3.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown/RoadTile_Basic_Down/ground/RoadTile_Basic_Down_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown_FrontalHB/RoadTile_Basic_Down_FrontalHB/RoadTile_Basic_Down3_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 0, -1);
	PrefabRoads[count]->addMaterial(&upDownRoadTile);
	count++;

	//Up
	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown/RoadTile_Basic_Up/RoadTile_Basic_Up0.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown/RoadTile_Basic_Up/ground/RoadTile_Basic_Up_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown_FrontalHB/RoadTile_Basic_Up_FrontalHB/RoadTile_Basic_Up0_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 0, 1);
	PrefabRoads[count]->addMaterial(&upDownRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown/RoadTile_Basic_Up/RoadTile_Basic_Up1.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown/RoadTile_Basic_Up/ground/RoadTile_Basic_Up_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown_FrontalHB/RoadTile_Basic_Up_FrontalHB/RoadTile_Basic_Up1_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 0, 1);
	PrefabRoads[count]->addMaterial(&upDownRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown/RoadTile_Basic_Up/RoadTile_Basic_Up2.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown/RoadTile_Basic_Up/ground/RoadTile_Basic_Up_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown_FrontalHB/RoadTile_Basic_Up_FrontalHB/RoadTile_Basic_Up2_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 0, 1);
	PrefabRoads[count]->addMaterial(&upDownRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown/RoadTile_Basic_Up/RoadTile_Basic_Up3.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown/RoadTile_Basic_Up/ground/RoadTile_Basic_Up_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Basic_UpDown_FrontalHB/RoadTile_Basic_Up_FrontalHB/RoadTile_Basic_Up3_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 0, 1);
	PrefabRoads[count]->addMaterial(&upDownRoadTile);
	count++;
	
	// Combi L / R & Down / Up
	//L + Down
	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_L_Down/RoadTile_Curve_L_Down0.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_L_Down/ground/RoadTile_Curve_L_Down_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown_FrontalHB/RoadTiles_Curve_L_Down_FrontalHB/RoadTile_Curve_L_Down0_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), -1, -1);
	PrefabRoads[count]->addMaterial(&upDownCurveRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_L_Down/RoadTile_Curve_L_Down1.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_L_Down/ground/RoadTile_Curve_L_Down_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown_FrontalHB/RoadTiles_Curve_L_Down_FrontalHB/RoadTile_Curve_L_Down1_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), -1, -1);
	PrefabRoads[count]->addMaterial(&upDownCurveRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_L_Down/RoadTile_Curve_L_Down2.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_L_Down/ground/RoadTile_Curve_L_Down_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown_FrontalHB/RoadTiles_Curve_L_Down_FrontalHB/RoadTile_Curve_L_Down2_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), -1, -1);
	PrefabRoads[count]->addMaterial(&upDownCurveRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_L_Down/RoadTile_Curve_L_Down3.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_L_Down/ground/RoadTile_Curve_L_Down_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown_FrontalHB/RoadTiles_Curve_L_Down_FrontalHB/RoadTile_Curve_L_Down3_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), -1, -1);
	PrefabRoads[count]->addMaterial(&upDownCurveRoadTile);
	count++;

	//L + Up
	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_L_Up/RoadTile_Curve_L_Up0.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_L_Up/ground/RoadTile_Curve_L_up_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown_FrontalHB/RoadTiles_Curve_L_Up_FrontalHB/RoadTile_Curve_L_Up0_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), -1, 1);
	PrefabRoads[count]->addMaterial(&upDownCurveRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_L_Up/RoadTile_Curve_L_Up1.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_L_Up/ground/RoadTile_Curve_L_up_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown_FrontalHB/RoadTiles_Curve_L_Up_FrontalHB/RoadTile_Curve_L_Up1_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), -1, 1);
	PrefabRoads[count]->addMaterial(&upDownCurveRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_L_Up/RoadTile_Curve_L_Up2.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_L_Up/ground/RoadTile_Curve_L_up_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown_FrontalHB/RoadTiles_Curve_L_Up_FrontalHB/RoadTile_Curve_L_Up2_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), -1, 1);
	PrefabRoads[count]->addMaterial(&upDownCurveRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_L_Up/RoadTile_Curve_L_Up3.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_L_Up/ground/RoadTile_Curve_L_up_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown_FrontalHB/RoadTiles_Curve_L_Up_FrontalHB/RoadTile_Curve_L_Up3_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), -1, 1);
	PrefabRoads[count]->addMaterial(&upDownCurveRoadTile);
	count++;

	//R + Down
	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_R_Down/RoadTile_Curve_R_Down0.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_R_Down/ground/RoadTile_Curve_R_Down_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown_FrontalHB/RoadTiles_Curve_R_Down_FrontalHB/RoadTile_Curve_R_Down0_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 1, -1);
	PrefabRoads[count]->addMaterial(&upDownCurveRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_R_Down/RoadTile_Curve_R_Down1.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_R_Down/ground/RoadTile_Curve_R_Down_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown_FrontalHB/RoadTiles_Curve_R_Down_FrontalHB/RoadTile_Curve_R_Down1_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 1, -1);
	PrefabRoads[count]->addMaterial(&upDownCurveRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_R_Down/RoadTile_Curve_R_Down2.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_R_Down/ground/RoadTile_Curve_R_Down_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown_FrontalHB/RoadTiles_Curve_R_Down_FrontalHB/RoadTile_Curve_R_Down2_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 1, -1);
	PrefabRoads[count]->addMaterial(&upDownCurveRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_R_Down/RoadTile_Curve_R_Down3.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_R_Down/ground/RoadTile_Curve_R_Down_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown_FrontalHB/RoadTiles_Curve_R_Down_FrontalHB/RoadTile_Curve_R_Down3_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 1, -1);
	PrefabRoads[count]->addMaterial(&upDownCurveRoadTile);
	count++;

	
	//R + Up
	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_R_Up/RoadTile_Curve_R_Up0.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_R_Up/ground/RoadTile_Curve_R_Up_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown_FrontalHB/RoadTiles_Curve_R_Up_FrontalHB/RoadTile_Curve_R_Up0_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 1, 1);
	PrefabRoads[count]->addMaterial(&upDownCurveRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_R_Up/RoadTile_Curve_R_Up1.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_R_Up/ground/RoadTile_Curve_R_Up_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown_FrontalHB/RoadTiles_Curve_R_Up_FrontalHB/RoadTile_Curve_R_Up1_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 1, 1);
	PrefabRoads[count]->addMaterial(&upDownCurveRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_R_Up/RoadTile_Curve_R_Up2.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_R_Up/ground/RoadTile_Curve_R_Up_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown_FrontalHB/RoadTiles_Curve_R_Up_FrontalHB/RoadTile_Curve_R_Up2_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 1, 1);
	PrefabRoads[count]->addMaterial(&upDownCurveRoadTile);
	count++;

	strcpy(prefabModelLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_R_Up/RoadTile_Curve_R_Up3.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown/RoadTiles_Curve_R_Up/ground/RoadTile_Curve_R_Up_ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/RoadTiles/RoadTiles_Curve_UpDown_FrontalHB/RoadTiles_Curve_R_Up_FrontalHB/RoadTile_Curve_R_Up3_FrontalHB.obj");
	SpecialPrefabRoads[count] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 1, 1);
	PrefabRoads[count]->addMaterial(&upDownCurveRoadTile);
	count++;



	//Groundplane erstellen
	groundplaneColor.MakeTextureDiffuse("textures\\PrototypeTextures\\Orange\\texture_06.png");
	groundplane.Init((2 + roadTilewidth) + (roadTilewidth * RoadTileBoundingBox), roadTilelength, &groundplaneColor);

	for (int i = 0; i < anzahlPrefabTerrain; i++) {
		ambienteTerrain[i] = new PrefabTerrain(roadTilelength, roadTilewidth, roadTileheight, RoadTileBoundingBox);
	}

	count = 0;

	ambienteTerrain[count]->initTerrain(myPerlinNoise[0], &myTerrainMaterial);
	count++;

	ambienteTerrain[count]->initTerrain(myPerlinNoise[1], &myTerrainMaterial);
	count++;

	ambienteTerrain[count]->initTerrain(myPerlinNoise[2], &myTerrainMaterial);
	count++;

	ambienteTerrain[count]->initTerrain(myPerlinNoise[3], &myTerrainMaterial);
	count++;

	ambienteTerrain[count]->initTerrain(myPerlinNoise[4], &myTerrainMaterial);
	count++;

	ambienteTerrain[count]->initTerrain(myPerlinNoise[5], &myTerrainMaterial);
	count++;


	count = 3;
	
	for (int i = 0; i < anzahlRoadTiles; i++) {

		//Placements hintereinander in einer Reihe anordnen
		RoadSector[i] = new RoadTile(PrefabRoads[0], myPlacement, roadTilewidth, roadTilelength, roadTileheight, RoadTileBoundingBox, &roadTilesGravityPlanes, &groundplane);
		RoadSector[i]->move(0.0f, 0.0f, 0.0f);
		if (count >= 3) {
			RoadSector[i]->addTerrain(ambienteTerrain[std::rand() % anzahlPrefabTerrain]->getTerrain());
			count = 0;
		}
		count++;

		//RoadTile and die Scene hängen
		RoadSector[i]->addToScene(PrefabRoads[0]);

	}

	resetRoad();
}

void RoadManager::updateRoad()
{
	
	//Letztes RoadTile von der Scene abhängen
	RoadSector[activeSpawn]->removefromScene();

	//letztes Placement an den Anfang verschieben
	RoadSector[activeSpawn]->move((float)(lane * roadTilewidth), (float)(lanehight * roadTileheight), (float)-(roadTilelength * anzahlRoadTiles));

	//festlegen, ob eine SpecialRoad oder eine "normale" Road gespawnt werden soll
	if (sinceLastSpecial >= specialSpawnForce || 0 == std::rand() % specialSpawnChance) {
		sinceLastSpecial = 0;
		while ((nextspecialTile == lastspecialTile) || (lane >= RoadTileBoundingBox && SpecialPrefabRoads[nextspecialTile]->getLaneShift() >= 1) || (lane <= -(RoadTileBoundingBox) && SpecialPrefabRoads[nextspecialTile]->getLaneShift() <= -1) || (lanehight >= RoadTileBoundingBox && SpecialPrefabRoads[nextspecialTile]->getLaneSlope() >= 1) || (lanehight <= -(RoadTileBoundingBox) && SpecialPrefabRoads[nextspecialTile]->getLaneSlope() <= -1)) {
			nextspecialTile = std::rand() % anzahlSpecialPrefabRoads;
		}
		RoadSector[activeSpawn]->addToScene(SpecialPrefabRoads[nextspecialTile]);

		if (count >= 3) {
			RoadSector[activeSpawn]->addTerrain(ambienteTerrain[std::rand() % anzahlPrefabTerrain]->getTerrain());
			count = 0;
		}
		count++;

		lastspecialTile = nextspecialTile;
		lane += SpecialPrefabRoads[nextspecialTile]->getLaneShift();
		lanehight += SpecialPrefabRoads[nextspecialTile]->getLaneSlope();
	}else{

		sinceLastSpecial++;

		//Den nächsten Prefab bestimmen(ein Prefab kann nicht 2 mal hintereinander gespawned werden
		nextTile = std::rand() % anzahlPrefabRoads;
		while (nextTile == lastTile) {
			nextTile = std::rand() % anzahlPrefabRoads;
		}
		lastTile = nextTile;

		//RoadTile mit der neuen Geometrie and das verschobene Placement anhängen
		RoadSector[activeSpawn]->addToScene(PrefabRoads[nextTile]);
	}

	//Ein zufälliges Item an das RoadTile anhängen
	if (1 == std::rand() % itemSpawnChance) {
		RoadSector[activeSpawn]->addItem(myItemManager->getItem(random));
	}

	//durch die 10 Raodtiles iterieren, start beim ersten
	lastSpawn = activeSpawn;
	if (activeSpawn == (anzahlRoadTiles-1)) {
		activeSpawn = 0;
	}
	else {
		activeSpawn++;
	}
	timesSpawned++;
	
}

void RoadManager::tryupdate(float tmp_ftime, CHVector tmp_carPos)
{
	roadtime += tmp_ftime;
	walltime += tmp_ftime;
	if (walltime >= wallofDEATHupdate) {
		wallofDEATH.TranslateZDelta(-wallofDEATHspeed);
	}

	
	if (RoadSector[lastSpawn]->getZPos()+(tilesremaining*roadTilelength)> tmp_carPos.GetZ()) {
		updateRoad();
		roadtime = 0;
	}
	
}

void RoadManager::resetRoad()
{
	activeSpawn = 0;
	timesSpawned = 1;
	lastTile = 0;
	nextTile = 0;
	lane = 0;
	lanehight = 0;
	sinceLastSpecial = 0;
	roadtime = 0;
	lastSpawn = anzahlRoadTiles;
	walltime = 0;
	lastspecialTile = 0;
	nextspecialTile = 0;
	terrainSpawnCounter = 0;
	count = 3;

	for (int i = 0; i < anzahlRoadTiles; i++) {
		//RoadTiles von der Scene abhängen
		RoadSector[i]->removefromScene();
		//Placements hintereinander in einer Reihe anordnen
		RoadSector[i]->move(0.0f, 0.0f, ((float)((roadTilelength*2) - (i * roadTilelength)))/2);
		//RoadTiles an die Scene anhängen
		RoadSector[i]->addToScene(PrefabRoads[0]);

		if (count >= 3) {
			RoadSector[i]->addTerrain(ambienteTerrain[std::rand()% anzahlPrefabTerrain]->getTerrain());
			count = 0;
		}
		count++;

	}


}

CGeos& RoadManager::getGeosGround()
{
	return roadTilesHitboxGround;
}

CGeos& RoadManager::getGeosFrontal()
{
	return roadTilesHitboxFrontal;
}

CGeoTerrains& RoadManager::getGravity()
{
	return roadTilesGravityPlanes;
}