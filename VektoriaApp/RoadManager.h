#pragma once
#include "Vektoria\Root.h"
#include  "RoadTile.h"
#include "PrefabRoad.h"
#include "SpecialPrefabRoad.h"
#include "ItemManager.h"

//Settings fpr die PrefabRoads
#define  anzahlPrefabRoads 5
#define anzahlSpecialPrefabRoads 2

//Settings f�r die RoadTiles
#define anzahlRoadTiles 10
#define roadTilelength 5
#define roadTilewidth 8

//Settings f�r den Spawn
#define specialSpawnChance 5

using namespace Vektoria;

class RoadManager
{
public:

	void init(CPlacement *tmp_scene, ItemManager *tmp_myItemManager);
	void updateRoad();
	CGeos getGeosGround()
	{
		return roadTilesHitboxGround;
	}
	CGeos getGeosFrontal()
	{
		return roadTilesHitboxFrontal;
	}

private:

	//das aktuell letzte RoadTile, das als n�chstes verschoben werden muss
	int activeSpawn;
	CHVector activeSpawnVector;

	//.
	int timesSpawned;
	int sinceLastSpecial;

	//gibt an in welcher lane sich die Road befindet, 0 ist der start, 1 entschpricht einer verschiebung
	//um die breite der Road nach links, negative Werte verschieben nach rechts
	int lane;

	//f�r ein besseres Spawnen
	int lastTile;
	int nextTile;
	int specialTile;

	//zum Speichern der Pfade f�r den import
	char prefabModelLoadPath[_MAX_PATH];
	char prefabHitboxGroundLoadPath[_MAX_PATH];
	char prefabHitboxFrontalLoadPath[_MAX_PATH];

	//Placement das dem RoadManager beim init �bergeben wird und an dem alles angeh�ngt wird
	CPlacement *myPlacement;

	//Placement an den ein RoadTile angeh�ngt wird
	CPlacement placementRoad[anzahlRoadTiles];

	//F�r die RoadTiles
	RoadTile* RoadSector[anzahlRoadTiles];

	//F�r die PrefabRoads & SPecialPrefabRoads
	PrefabRoad* PrefabRoads[anzahlPrefabRoads];
	SpecialPrefabRoad* SpecialPrefabRoads[anzahlSpecialPrefabRoads];

	// Kollisionsobjektmenge der RoadTiles
	CGeos roadTilesHitboxGround;
	CGeos roadTilesHitboxFrontal;

	//ItemManager
	ItemManager* myItemManager;
};

