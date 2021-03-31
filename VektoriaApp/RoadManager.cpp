#include "RoadManager.h"

void RoadManager::init(CPlacement *tmp_scene)
{

	myPlacement = tmp_scene;
	activeSpawn = 0;
	timesSpawned = 1;

	//Prefabs laden
	strcpy(prefabModelLoadPath, "models/road/startRoad.obj");
	strcpy(prefabHitboxLoadPath, "models/road/hitbox/startRoadbox.obj");
	PrefabRoads[0] = new PrefabRoad(prefabModelLoadPath, prefabHitboxLoadPath, &roadTilesHitbox);
	strcpy(prefabModelLoadPath, "models/road/prefabRoad0.obj");
	strcpy(prefabHitboxLoadPath, "models/road/hitbox/prefabRoad0box.obj");
	PrefabRoads[1] = new PrefabRoad(prefabModelLoadPath, prefabHitboxLoadPath, &roadTilesHitbox);
	strcpy(prefabModelLoadPath, "models/road/prefabRoad1.obj");
	strcpy(prefabHitboxLoadPath, "models/road/hitbox/prefabRoad1box.obj");
	PrefabRoads[2] = new PrefabRoad(prefabModelLoadPath, prefabHitboxLoadPath, &roadTilesHitbox);
	strcpy(prefabModelLoadPath, "models/road/prefabRoad2.obj");
	strcpy(prefabHitboxLoadPath, "models/road/hitbox/prefabRoad2box.obj");
	PrefabRoads[3] = new PrefabRoad(prefabModelLoadPath, prefabHitboxLoadPath, &roadTilesHitbox);
	strcpy(prefabModelLoadPath, "models/road/prefabRoad3.obj");
	strcpy(prefabHitboxLoadPath, "models/road/hitbox/prefabRoad3box.obj");
	PrefabRoads[4] = new PrefabRoad(prefabModelLoadPath, prefabHitboxLoadPath, &roadTilesHitbox);

	for (int i = 0; i < 10; i++) {
		RoadSector[i] = new RoadTile(PrefabRoads[0], &placementRoad[i]);
	}

	//die ersten 10 Roadtiels mit der startRoad initialisieren
	for (int i = 0; i < 10; i++) {
		modelRoad[i] = prefabRoad[0];
	}

	for (int i = 0; i < 10; i++) {

		//Placements in die Szene hängen
		myPlacement->AddPlacement(&placementRoad[i]);
		//Placements hintereinander in einer Reihe anordnen
		placementRoad[i].TranslateZ(5 + i * 5);
		//RoadTile and die Scene hängen
		RoadSector[i]->addToScene(PrefabRoads[0]);
		
	}
}

void RoadManager::updateRoad()
{
	
	//Letztes RoadTile von der Scene abhängen
	RoadSector[activeSpawn]->removefromScene();
	//letztes Placement an den Anfang verschieben
	placementRoad[activeSpawn].TranslateZ(50 + timesSpawned * 5);
	//RoadTile mit der neuen Geometrie and das verschobene Placement anhängen
	RoadSector[activeSpawn]->addToScene(PrefabRoads[std::rand() % 5]);

	//durch die 10 Raodtiles iterieren, start beim ersten
	if (activeSpawn >= 9) {
		activeSpawn = 0;
	}
	else {
		activeSpawn++;
	}
	timesSpawned++;
	
}
