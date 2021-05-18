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
#define anzahlRoadTiles 10
#define roadTilelength 300
#define roadTilewidth 100
#define roadTileheight 30
#define RoadTileBoundingBox 6

//Settings für den Spawn
#define spawnTime 90
//gibt an, wie viele RoadTiles zwischen dem Auto und dem "Ende" der Road sein sollen, wird dies unterschritten, wird ein Spawn erzwungen
#define tilesremaining 5
#define specialSpawnChanceSetting 1
#define specialSpawnForce 5
#define itemSpawnChance 5

//Settings für den Sandsturm aka Suzanne
#define wallofDEATHupdate 0.1
#define wallofDEATHspeed 0.05

using namespace Vektoria;

class RoadManager
{
public:

	void init(CPlacement *tmp_scene, ItemManager *tmp_myItemManager);
	void updateRoad();
	void tryupdate(float tmp_ftime, CHVector tmp_carPos);
	void resetRoad();

	//damit die Hitboxen witergegeben werden können
	CGeos& getGeosGround();
	CGeos& getGeosFrontal();
	CGeoTerrains& getGravity();


private:

	//Zeit seit dem letzten update der Road
	float roadtime;
	float walltime;

	//das aktuell letzte RoadTile, das als nächstes verschoben werden muss
	int activeSpawn;
	int lastSpawn;
	int specialSpawnChance;

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
	int nextspecialTile;
	int lastspecialTile;

	//zum Speichern der Pfade für den import
	char prefabModelLoadPath[_MAX_PATH];
	char prefabHitboxGroundLoadPath[_MAX_PATH];
	char prefabHitboxFrontalLoadPath[_MAX_PATH];

	//Placement das dem RoadManager beim init übergeben wird und an dem alles angehängt wird
	CPlacement *myPlacement;

	//Placement an den ein RoadTile angehängt wird
	CPlacement placementGroundPlane[anzahlRoadTiles];
	CPlacement placementRoadBase[anzahlRoadTiles];
	CPlacement placementRoadTile[anzahlRoadTiles];

	//Groundplane unter der Road
	CGeoQuad groundplane;
	CMaterial groundplaneColor;

	//Placement für die Plane des Sandsturms
	CPlacement wallofDEATH;
	CGeo *wallofMODEL;
	CGeoQuad wallofSTORM;
	CMaterial wallofCOLOR;
	CEmitter wallofEMITTER;

	//Für die RoadTiles
	RoadTile* RoadSector[anzahlRoadTiles];

	//Für die PrefabRoads & SPecialPrefabRoads
	PrefabRoad* PrefabRoads[anzahlPrefabRoads];
	SpecialPrefabRoad* SpecialPrefabRoads[anzahlSpecialPrefabRoads];

	// Kollisionsobjektmenge der RoadTiles
	CGeos roadTilesHitboxGround;
	CGeos roadTilesHitboxFrontal;
	CGeoTerrains roadTilesGravityPlanes;

	//ItemManager
	ItemManager* myItemManager;
};

