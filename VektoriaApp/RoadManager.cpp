#include "RoadManager.h"

void RoadManager::init(CPlacement *tmp_scene, ItemManager *tmp_myItemManager)
{

	myPlacement = tmp_scene;
	activeSpawn = 0;
	timesSpawned = 1;
	myItemManager = tmp_myItemManager;
	lastTile = 0;
	nextTile = 0;
	lane = 0;
	lanehight = 0;
	sinceLastSpecial = 0;
	roadtime = 0;
	lastSpawn = 0;
	walltime = 0;
	lastspecialTile = 0;
	nextspecialTile = 0;
	specialSpawnChance = specialSpawnChanceSetting;

	//Sandsturm laden & anh�ngen
	wallofMODEL = wallofIMPORT.LoadGeo("models/wallofdeath/wallofdeath.obj", true);
	wallofDEATH.AddGeo(wallofMODEL);
	myPlacement->AddPlacement(&wallofDEATH);
	wallofDEATH.TranslateZ(400.0f);

	//PrefabRoads laden
	strcpy(prefabModelLoadPath, "models/road/RoadTile_Basic.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/road/hitbox/ground/RoadTile_Basic_Ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/road/hitbox/frontal/RoadTile_Basic_Frontal.obj");
	PrefabRoads[0] = new PrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f));
	
	strcpy(prefabModelLoadPath, "models/road/RoadTile_Basic.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/road/hitbox/ground/RoadTile_Basic_Ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/road/hitbox/frontal/RoadTile_Basic_Frontal.obj");
	PrefabRoads[1] = new PrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f));
	

	//Special PrefabRoads laden

	//Curves L / R
	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Curve_L.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/RoadTile_Curve_L_Ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/specialroad/hitbox/frontal/RoadTile_Curve_L_Frontal.obj");
	SpecialPrefabRoads[0] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), -1, 0);
	
	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Curve_R.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/RoadTile_Curve_R_Ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/specialroad/hitbox/frontal/RoadTile_Curve_R_Frontal.obj");
	SpecialPrefabRoads[1] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), 1, 0);
	
	//Down / Up
	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Down.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/RoadTile_Down_Ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/specialroad/hitbox/frontal/RoadTile_Down_Frontal.obj");
	SpecialPrefabRoads[2] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 0, -1);

	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Up.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/RoadTile_Up_Ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/specialroad/hitbox/frontal/RoadTile_Up_Frontal.obj");
	SpecialPrefabRoads[3] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 0, 1);

	// Combi L / R & Down / Up

	
	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Curve_L_Down.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/RoadTile_Curve_L_Down_Ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/specialroad/hitbox/frontal/RoadTile_Curve_L_Down_Frontal.obj");
	SpecialPrefabRoads[4] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), -1, -1);

	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Curve_L_Up.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/RoadTile_Curve_L_Up_Ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/specialroad/hitbox/frontal/RoadTile_Curve_L_Up_Frontal.obj");
	SpecialPrefabRoads[5] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), -1, 1);
	
	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Curve_R_Down.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/RoadTile_Curve_R_Down_Ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/specialroad/hitbox/frontal/RoadTile_Curve_R_Down_Frontal.obj");
	SpecialPrefabRoads[6] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 1, -1);
	
	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Curve_R_Up.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/RoadTile_Curve_R_Up_Ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/specialroad/hitbox/frontal/RoadTile_Curve_R_Up_Frontal.obj");
	SpecialPrefabRoads[7] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 1, 1);
	

	for (int i = 0; i < anzahlRoadTiles; i++) {
		RoadSector[i] = new RoadTile(PrefabRoads[0], &placementRoad[i]);
	}

	for (int i = 0; i < anzahlRoadTiles; i++) {

		//Placements in die Szene h�ngen
		myPlacement->AddPlacement(&placementRoad[i]);
		//Placements hintereinander in einer Reihe anordnen
		placementRoad[i].TranslateZ((roadTilelength*2)-(i *roadTilelength));
		//RoadTile and die Scene h�ngen
		RoadSector[i]->addToScene(PrefabRoads[0]);
		
	}
}

void RoadManager::updateRoad()
{
	
	//Letztes RoadTile von der Scene abh�ngen
	RoadSector[activeSpawn]->removefromScene();
	//letztes Placement an den Anfang verschieben
	activeSpawnVector = placementRoad[activeSpawn].GetPos();
	activeSpawnVector.SetX(0);
	activeSpawnVector.SetY(0);
	placementRoad[activeSpawn].TranslateX(lane * roadTilewidth);
	placementRoad[activeSpawn].TranslateYDelta(lanehight * roadTileheight);
	placementRoad[activeSpawn].TranslateDelta(activeSpawnVector);
	placementRoad[activeSpawn].TranslateZDelta(-(roadTilelength*anzahlRoadTiles));

	//festlegen, ob eine SpecialRoad oder eine "normale" Road gespawnt werden soll
	if (sinceLastSpecial>=specialSpawnForce || 1 == std::rand()%specialSpawnChance) {
		sinceLastSpecial = 0;
		while ((nextspecialTile == lastspecialTile) || (lane >= 6 && SpecialPrefabRoads[nextspecialTile]->getLaneShift() >=1) || (lane <= -6 && SpecialPrefabRoads[nextspecialTile]->getLaneShift() <= -1) || (lanehight >= 6 && SpecialPrefabRoads[nextspecialTile]->getLaneSlope() >= 1) || (lanehight <= -6 && SpecialPrefabRoads[nextspecialTile]->getLaneSlope() <= -1)) {
			nextspecialTile = std::rand() % anzahlSpecialPrefabRoads;
		}
		RoadSector[activeSpawn]->addToScene(SpecialPrefabRoads[nextspecialTile]);
		lastspecialTile = nextspecialTile;
		lane += SpecialPrefabRoads[nextspecialTile]->getLaneShift();
		lanehight += SpecialPrefabRoads[nextspecialTile]->getLaneSlope();
	}else{

		sinceLastSpecial++;

		//Den n�chsten Prefab bestimmen(ein Prefab kann nicht 2 mal hintereinander gespawned werden
		nextTile = std::rand() % anzahlPrefabRoads;
		while (nextTile == lastTile) {
			nextTile = std::rand() % anzahlPrefabRoads;
		}
		lastTile = nextTile;

		//RoadTile mit der neuen Geometrie and das verschobene Placement anh�ngen
		RoadSector[activeSpawn]->addToScene(PrefabRoads[nextTile]);
		//Ein zuf�lliges Item an das RoadTile anh�ngen
	}

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

	if (roadtime >= spawnTime || placementRoad[lastSpawn].GetPos().GetZ()+(tilesremaining*roadTilelength)> tmp_carPos.GetZ()) {
		updateRoad();
		roadtime = 0;
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
