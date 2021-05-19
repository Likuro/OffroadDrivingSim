#include "RoadManager.h"

void RoadManager::init(CPlacement *tmp_scene, ItemManager *tmp_myItemManager)
{

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

	//Sandsturm laden & anhängen
	wallofCOLOR.MakeTextureDiffuse("textures\\Sandstorm_cube.png");
	wallofCOLOR.SetTransparency(1.0f);
	wallofEMITTER.LoadPreset("Sandstorm_ver2");
	wallofSTORM.Init(roadTilewidth* RoadTileBoundingBox, roadTileheight* RoadTileBoundingBox, &wallofCOLOR);
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
	

	//PrefabRoads laden
	strcpy(prefabModelLoadPath, "models/road/RoadTile_Basic_dummy.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/road/hitbox/ground/RoadTile_Basic_Ground_dummy.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	PrefabRoads[0] = new PrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f));
	

	strcpy(prefabModelLoadPath, "models/road/RoadTile_Basic_dummy.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/road/hitbox/ground/RoadTile_Basic_Ground_dummy.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	PrefabRoads[1] = new PrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f));
	

	//Special PrefabRoads laden

	//Curves L / R
	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Curve_L_dummy.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/RoadTile_Curve_L_Ground_dummy.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	SpecialPrefabRoads[0] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), -1, 0);
	
	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Curve_R_dummy.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/RoadTile_Curve_R_Ground_dummy.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	SpecialPrefabRoads[1] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), 1, 0);
	
	//Down / Up
	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Down_dummy.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/RoadTile_Down_Ground_dummy.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	SpecialPrefabRoads[2] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 0, -1);

	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Up_dummy.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/RoadTile_Up_Ground_dummy.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	SpecialPrefabRoads[3] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 0, 1);

	// Combi L / R & Down / Up

	
	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Curve_L_Down_dummy.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/RoadTile_Curve_L_Down_Ground_dummy.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	SpecialPrefabRoads[4] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), -1, -1);

	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Curve_L_Up_dummy.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/RoadTile_Curve_L_Up_Ground_dummy.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	SpecialPrefabRoads[5] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), -1, 1);
	
	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Curve_R_Down_dummy.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/RoadTile_Curve_R_Down_Ground_dummy.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	SpecialPrefabRoads[6] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 1, -1);
	
	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Curve_R_Up_dummy.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/RoadTile_Curve_R_Up_Ground_dummy.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/dummy/void.obj");
	SpecialPrefabRoads[7] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 1, 1);
	
	//Groundplane erstellen
	groundplaneColor.MakeTextureDiffuse("textures\\PrototypeTextures\\Orange\\texture_06.png");
	groundplane.Init(roadTilewidth* RoadTileBoundingBox, roadTilelength, &groundplaneColor);

	for (int i = 0; i < anzahlRoadTiles; i++) {
		placementGroundPlane[i].AddGeo(&groundplane);
		placementRoadBase[i].AddPlacement(&placementGroundPlane[i]);
		placementGroundPlane[i].TranslateZ(-((float)roadTileheight+((float)roadTileheight*((float)RoadTileBoundingBox/2))));
		//placementGroundPlane[i].TranslateZDelta(200.0f);
		placementGroundPlane[i].RotateXDelta(-HALFPI);
		placementRoadBase[i].AddPlacement(&placementRoadTile[i]);
		RoadSector[i] = new RoadTile(PrefabRoads[0], &placementRoadTile[i], roadTilewidth, roadTilelength, &roadTilesGravityPlanes);
	}

	for (int i = 0; i < anzahlRoadTiles; i++) {

		//Placements in die Szene hängen
		myPlacement->AddPlacement(&placementRoadBase[i]);
		//Placements hintereinander in einer Reihe anordnen
		placementRoadBase[i].TranslateZ((roadTilelength * 2) - (i * roadTilelength));
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
	placementRoadBase[activeSpawn].TranslateZDelta(-(roadTilelength * anzahlRoadTiles));
	placementRoadTile[activeSpawn].TranslateX(lane * roadTilewidth);
	placementRoadTile[activeSpawn].TranslateYDelta((lanehight * roadTileheight));


	//festlegen, ob eine SpecialRoad oder eine "normale" Road gespawnt werden soll
	if (sinceLastSpecial>=specialSpawnForce || 0 == std::rand()% specialSpawnChance) {
		sinceLastSpecial = 0;
		while ((nextspecialTile == lastspecialTile) || (lane >= RoadTileBoundingBox && SpecialPrefabRoads[nextspecialTile]->getLaneShift() >=1) || (lane <= -(RoadTileBoundingBox) && SpecialPrefabRoads[nextspecialTile]->getLaneShift() <= -1) || (lanehight >= RoadTileBoundingBox && SpecialPrefabRoads[nextspecialTile]->getLaneSlope() >= 1) || (lanehight <= -(RoadTileBoundingBox) && SpecialPrefabRoads[nextspecialTile]->getLaneSlope() <= -1)) {
			nextspecialTile = std::rand() % anzahlSpecialPrefabRoads;
		}
		RoadSector[activeSpawn]->addToScene(SpecialPrefabRoads[nextspecialTile]);
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
		//Ein zufälliges Item an das RoadTile anhängen
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

	
	if (placementRoadBase[lastSpawn].GetPos().GetZ()+(tilesremaining*roadTilelength)> tmp_carPos.GetZ()) {
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

	for (int i = 0; i < anzahlRoadTiles; i++) {
		//RoadTiles von der Scene abhängen
		RoadSector[i]->removefromScene();
		//Placements hintereinander in einer Reihe anordnen
		placementRoadBase[i].TranslateZ((roadTilelength * 2) - (i * roadTilelength));
		//RoadTiles an die Scene anhängen
		RoadSector[i]->addToScene(PrefabRoads[0]);
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
