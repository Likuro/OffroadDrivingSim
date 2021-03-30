#include "RoadManager.h"

void RoadManager::init(CPlacement *tmp_scene)
{

	myPlacement = tmp_scene;
	activeSpawn = 0;
	timesSpawned = 1;

	//Prefabs laden
	strcpy(prefabLoadPath, "models/road/startRoad.obj");
	PrefabRoads[0] = new PrefabRoad(prefabLoadPath);
	strcpy(prefabLoadPath, "models/road/prefabRoad0.obj");
	PrefabRoads[1] = new PrefabRoad(prefabLoadPath);
	strcpy(prefabLoadPath, "models/road/prefabRoad1.obj");
	PrefabRoads[2] = new PrefabRoad(prefabLoadPath);
	strcpy(prefabLoadPath, "models/road/prefabRoad1.obj");
	PrefabRoads[3] = new PrefabRoad(prefabLoadPath);
	strcpy(prefabLoadPath, "models/road/prefabRoad3.obj");
	PrefabRoads[4] = new PrefabRoad(prefabLoadPath);

	for (int i = 0; i < 10; i++) {
		RoadSector[i] = new RoadTile(PrefabRoads[0], &placementRoad[i]);
	}

	//die ersten 10 Roadtiels mit der startRoad initialisieren
	for (int i = 0; i < 10; i++) {
		modelRoad[i] = prefabRoad[0];
	}

	for (int i = 0; i < 10; i++) {

		//Placements in die Szene h�ngen
		myPlacement->AddPlacement(&placementRoad[i]);
		//Placements hintereinander in einer Reihe anordnen
		placementRoad[i].TranslateZ(5 + i * 5);
		//RoadTile and die Scene h�ngen
		RoadSector[i]->addToScene(PrefabRoads[0]);
		
	}
}

void RoadManager::updateRoad()
{
	
	//Letztes RoadTile von der Scene abh�ngen
	RoadSector[activeSpawn]->removefromScene();
	//letztes Placement an den Anfang verschieben
	placementRoad[activeSpawn].TranslateZ(50 + timesSpawned * 5);
	//RoadTile mit der neuen Geometrie and das verschobene Placement anh�ngen
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
