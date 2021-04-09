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
	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Curve_L.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/RoadTile_Curve_L_Ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/specialroad/hitbox/frontal/RoadTile_Curve_L_Frontal.obj");
	SpecialPrefabRoads[0] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), -1, 0);
	
	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Curve_R.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/RoadTile_Curve_R_Ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/specialroad/hitbox/frontal/RoadTile_Curve_R_Frontal.obj");
	SpecialPrefabRoads[1] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), 1, 0);
	
	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Down.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/road/hitbox/ground/RoadTile_Basic_Ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/road/hitbox/frontal/RoadTile_Basic_Frontal.obj");
	SpecialPrefabRoads[2] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 0, -1);

	strcpy(prefabModelLoadPath, "models/specialroad/RoadTile_Up.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/road/hitbox/ground/RoadTile_Basic_Ground.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/road/hitbox/frontal/RoadTile_Basic_Frontal.obj");
	SpecialPrefabRoads[3] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), 0, 1);

	for (int i = 0; i < anzahlRoadTiles; i++) {
		RoadSector[i] = new RoadTile(PrefabRoads[0], &placementRoad[i]);
	}

	for (int i = 0; i < anzahlRoadTiles; i++) {

		//Placements in die Szene hängen
		myPlacement->AddPlacement(&placementRoad[i]);
		//Placements hintereinander in einer Reihe anordnen
		placementRoad[i].TranslateZ(-(i * roadTilelength));
		//RoadTile and die Scene hängen
		RoadSector[i]->addToScene(PrefabRoads[0]);
		
	}
}

void RoadManager::updateRoad()
{
	
	//Letztes RoadTile von der Scene abhängen
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
	if (sinceLastSpecial>specialSpawnChance) {
		sinceLastSpecial = 0;
		specialTile = std::rand() % anzahlSpecialPrefabRoads;
		RoadSector[activeSpawn]->addToScene(SpecialPrefabRoads[specialTile]);
		lane += SpecialPrefabRoads[specialTile]->getLaneShift();
		lanehight += SpecialPrefabRoads[specialTile]->getLaneSlope();
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
	if (activeSpawn == (anzahlRoadTiles-1)) {
		activeSpawn = 0;
	}
	else {
		activeSpawn++;
	}
	timesSpawned++;
	
}

CGeos& RoadManager::getGeosGround()
{
	return roadTilesHitboxGround;
}

CGeos& RoadManager::getGeosFrontal()
{
	return roadTilesHitboxFrontal;
}
