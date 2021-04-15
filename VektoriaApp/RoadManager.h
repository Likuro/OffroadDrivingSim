#pragma once
#include "Vektoria\Root.h"
#include  "RoadTile.h"
#include "PrefabRoad.h"
#include "SpecialPrefabRoad.h"
#include "ItemManager.h"

//Settings fpr die PrefabRoads
#define  anzahlPrefabRoads 2
#define anzahlSpecialPrefabRoads 8

//Settings für die RoadTiles
#define anzahlRoadTiles 5
#define roadTilelength 144
#define roadTilewidth 100
#define roadTileheight 30

//Settings für den Spawn
#define specialSpawnChance 2
#define itemSpawnChance 5

using namespace Vektoria;

class RoadManager
{
public:

	void init(CPlacement *tmp_scene, ItemManager *tmp_myItemManager);
	void updateRoad();

	//damit die Hitboxen witergegeben werden können
	CGeos& getGeosGround();
	CGeos& getGeosFrontal();


private:

	//das aktuell letzte RoadTile, das als nächstes verschoben werden muss
	int activeSpawn;
	CHVector activeSpawnVector;

	//.
	int timesSpawned;
	int sinceLastSpecial;

	//gibt an in welcher lane sich die Road befindet, 0 ist der start, 1 entschpricht einer verschiebung
	//um die breite der Road nach links, negative Werte verschieben nach rechts
	int lane;

	//gibt an, in welcher Höhe sich die Road befindet, 0 ist die start Ebene, 1 entspricht einer verschiebung
	//um die höhe der Road nach oben, negative Werte verschieben nach unten
	int lanehight;

	//für ein besseres Spawnen
	int lastTile;
	int nextTile;
	int specialTile;

	//zum Speichern der Pfade für den import
	char prefabModelLoadPath[_MAX_PATH];
	char prefabHitboxGroundLoadPath[_MAX_PATH];
	char prefabHitboxFrontalLoadPath[_MAX_PATH];

	//Placement das dem RoadManager beim init übergeben wird und an dem alles angehängt wird
	CPlacement *myPlacement;

	//Placement an den ein RoadTile angehängt wird
	CPlacement placementRoad[anzahlRoadTiles];

	//Für die RoadTiles
	RoadTile* RoadSector[anzahlRoadTiles];

	//Für die PrefabRoads & SPecialPrefabRoads
	PrefabRoad* PrefabRoads[anzahlPrefabRoads];
	SpecialPrefabRoad* SpecialPrefabRoads[anzahlSpecialPrefabRoads];

	// Kollisionsobjektmenge der RoadTiles
	CGeos roadTilesHitboxGround;
	CGeos roadTilesHitboxFrontal;

	//ItemManager
	ItemManager* myItemManager;
};

