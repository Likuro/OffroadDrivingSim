#pragma once
#include "Vektoria\Root.h"
#include  "RoadTile.h"
#include "PrefabRoad.h"
#include "SpecialPrefabRoad.h"
#include "ItemManager.h"

//Settings fpr die PrefabRoads
#define  anzahlPrefabRoads 2
#define anzahlSpecialPrefabRoads 8

//Settings f�r die RoadTiles
#define anzahlRoadTiles 10
#define roadTilelength 144
#define roadTilewidth 100
#define roadTileheight 30

//Settings f�r den Spawn
#define spawnTime 10
//gibt an, wie viele RoadTiles zwischen dem Auto und dem "Ende" der Road sein sollen, wird dies unterschritten, wird ein Spawn erzwungen
#define tilesremaining 5
#define specialSpawnChanceSetting 4
#define specialSpawnForce 5
#define itemSpawnChance 5

//Settings f�r den Sandsturm aka Suzanne
#define wallofDEATHupdate 0.1
#define wallofDEATHspeed 0.05

using namespace Vektoria;

class RoadManager
{
public:

	void init(CPlacement *tmp_scene, ItemManager *tmp_myItemManager);
	void updateRoad();
	void tryupdate(float tmp_ftime, CHVector tmp_carPos);

	//damit die Hitboxen witergegeben werden k�nnen
	CGeos& getGeosGround();
	CGeos& getGeosFrontal();


private:

	//Zeit seit dem letzten update der Road
	float roadtime;
	float walltime;

	//das aktuell letzte RoadTile, das als n�chstes verschoben werden muss
	int activeSpawn;
	int lastSpawn;
	CHVector activeSpawnVector;
	int specialSpawnChance;

	//.
	int timesSpawned;
	int sinceLastSpecial;

	//gibt an in welcher lane sich die Road befindet, 0 ist der start, 1 entschpricht einer verschiebung
	//um die breite der Road nach links, negative Werte verschieben nach rechts
	int lane;

	//gibt an, in welcher H�he sich die Road befindet, 0 ist die start Ebene, 1 entspricht einer verschiebung
	//um die h�he der Road nach oben, negative Werte verschieben nach unten
	int lanehight;

	//f�r ein besseres Spawnen
	int lastTile;
	int nextTile;
	int nextspecialTile;
	int lastspecialTile;

	//zum Speichern der Pfade f�r den import
	char prefabModelLoadPath[_MAX_PATH];
	char prefabHitboxGroundLoadPath[_MAX_PATH];
	char prefabHitboxFrontalLoadPath[_MAX_PATH];

	//Placement das dem RoadManager beim init �bergeben wird und an dem alles angeh�ngt wird
	CPlacement *myPlacement;

	//Placement an den ein RoadTile angeh�ngt wird
	CPlacement placementRoad[anzahlRoadTiles];

	//Placement f�r die Plane des Sandsturms
	CPlacement wallofDEATH;
	CGeo *wallofMODEL;
	CFileWavefront wallofIMPORT;

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

