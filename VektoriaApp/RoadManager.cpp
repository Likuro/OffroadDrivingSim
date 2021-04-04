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
	sinceLastSpecial = 0;

	//PrefabRoads laden
	strcpy(prefabModelLoadPath, "models/road/startRoad.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/road/hitbox/ground/startRoadbox.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/road/hitbox/frontal/startRoadbox.obj");
	PrefabRoads[0] = new PrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f));
	
	strcpy(prefabModelLoadPath, "models/road/prefabRoad0.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/road/hitbox/ground/prefabRoad0box.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/road/hitbox/frontal/prefabRoad0box.obj");
	PrefabRoads[1] = new PrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f));
	
	strcpy(prefabModelLoadPath, "models/road/prefabRoad1.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/road/hitbox/ground/prefabRoad1box.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/road/hitbox/frontal/prefabRoad1box.obj");
	PrefabRoads[2] = new PrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f));
	
	strcpy(prefabModelLoadPath, "models/road/prefabRoad2.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/road/hitbox/ground/prefabRoad2box.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/road/hitbox/frontal/prefabRoad2box.obj");
	PrefabRoads[3] = new PrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f), CHVector(0.0f, 2.0f, 0.0f));
	
	strcpy(prefabModelLoadPath, "models/road/prefabRoad3.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/road/hitbox/ground/prefabRoad3box.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/road/hitbox/frontal/prefabRoad3box.obj");
	PrefabRoads[4] = new PrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 2.0f, 2.0f), CHVector(0.0f, 2.0f, 2.0f), CHVector(0.0f, 2.0f, 2.0f));

	//Special PrefabRoads laden
	strcpy(prefabModelLoadPath, "models/specialroad/SpecialRoad0.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/SpecialRoad0box.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/specialroad/hitbox/frontal/SpecialRoad0box.obj");
	SpecialPrefabRoads[0] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), -1);
	
	strcpy(prefabModelLoadPath, "models/specialroad/SpecialRoad1.obj");
	strcpy(prefabHitboxGroundLoadPath, "models/specialroad/hitbox/ground/SpecialRoad1box.obj");
	strcpy(prefabHitboxFrontalLoadPath, "models/specialroad/hitbox/frontal/SpecialRoad1box.obj");
	SpecialPrefabRoads[1] = new SpecialPrefabRoad(prefabModelLoadPath, prefabHitboxGroundLoadPath, prefabHitboxFrontalLoadPath, &roadTilesHitboxGround, &roadTilesHitboxFrontal, CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), CHVector(0.0f, 0.0f, 2.0f), 1);


	for (int i = 0; i < anzahlRoadTiles; i++) {
		RoadSector[i] = new RoadTile(PrefabRoads[0], &placementRoad[i]);
	}

	for (int i = 0; i < anzahlRoadTiles; i++) {

		//Placements in die Szene hängen
		myPlacement->AddPlacement(&placementRoad[i]);
		//Placements hintereinander in einer Reihe anordnen
		placementRoad[i].TranslateZ(roadTilelength + i * roadTilelength);
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
	placementRoad[activeSpawn].TranslateX(lane * roadTilewidth);
	placementRoad[activeSpawn].TranslateDelta(activeSpawnVector);
	placementRoad[activeSpawn].TranslateZDelta((roadTilelength*anzahlRoadTiles));

	//festlegen, ob eine SpecialRoad oder eine "normale" Road gespawnt werden soll
	if (sinceLastSpecial>specialSpawnChance) {
		sinceLastSpecial = 0;
		specialTile = std::rand() % anzahlSpecialPrefabRoads;
		RoadSector[activeSpawn]->addToScene(SpecialPrefabRoads[specialTile]);
		lane += SpecialPrefabRoads[specialTile]->getLaneShift();
		//Ein zufälliges Item an das RoadTile anhängen
		//RoadSector[activeSpawn]->addItem(myItemManager->getItem(random));
	}else{
		sinceLastSpecial++;
		//RoadTile mit der neuen Geometrie and das verschobene Placement anhängen
		nextTile = std::rand() % anzahlPrefabRoads;
		while (nextTile == lastTile) {
			nextTile = std::rand() % anzahlPrefabRoads;
		}
		lastTile = nextTile;
		RoadSector[activeSpawn]->addToScene(PrefabRoads[nextTile]);
		//Ein zufälliges Item an das RoadTile anhängen
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
