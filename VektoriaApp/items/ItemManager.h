#pragma once
#include "Vektoria\Root.h"
#include "BoostItem.h"
#include "HealthItem.h"

using namespace Vektoria;

enum itemType { random, boost, health };

class ItemManager
{
public:
	ItemManager(int count, CPlacement* player, DriveController* car, CRoot* root);

	CPlacement* getItem(itemType type);
	void update(float fTime, float fTimeDelta);
	void updatePlayer(CPlacement* player, DriveController* car);
	// muss gecallt werden, damit Kollisionen mit Strahlenb�schel gecheckt wird
	void InitRays(CAABB* boundingBox);

private:
	// Player f�r Kollisionsabfragen
	CPlacement* m_Player;
	DriveController* m_Car;
	CHVector m_oldPlayerPos;
	// maximaler Abstand der Rays zueinander (sollte kleiner sein als das kleinste Kollisionsobjekt)
	float m_RayMaxDist = 0.15f;
	// L�nge des Rays
	float m_RayLength;
	// Container f�r Pfadb�schel
	std::vector<CHVector*> m_pathRays;

	CRoot* m_Root;

	// ItemArrays
	int m_itemCount;
	BoostItem** m_BoostArray;
	char* m_boostModelPath = "models\\items\\BoostItem.obj";
	char* m_boostMatPath = "textures\\BoostItemTexture\\Material.001_Emissive.png";
	HealthItem** m_HealthArray;
	char* m_healthModelPath = "models\\items\\HealthItem.obj";
	char* m_healthMatPath = "textures\\HealthItemTexture\\Material.002_Emissive.png";

	// Container f�r alle aktiven Geos, die mit dem Auto kollidieren k�nnen
	CGeos m_Geos;
};

