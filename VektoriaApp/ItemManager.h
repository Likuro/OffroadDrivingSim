#pragma once
#include "Vektoria\Root.h"
#include "BoostItem.h"
#include "HealthItem.h"

using namespace Vektoria;

enum itemType { random, boost, health };

class ItemManager
{
public:
	ItemManager(int count, CPlacement* player);

	CPlacement* getItem(itemType type);
	void update(float fTime, float fTimeDelta);
	// muss gecallt werden, damit Kollisionen mit Strahlenbüschel gecheckt wird
	void InitRays(CAABB* boundingBox);

private:
	// Player für Kollisionsabfragen
	CPlacement* m_Player;
	CHVector m_oldPlayerPos;
	// maximaler Abstand der Rays zueinander (sollte kleiner sein als das kleinste Kollisionsobjekt)
	float m_RayMaxDist = 0.15f;
	// Länge des Rays
	float m_RayLength;
	// Container für Pfadbüschel
	std::vector<CHVector*> m_pathRays;

	// ItemArrays
	int m_itemCount;
	BoostItem** m_BoostArray;
	char* m_boostModelPath = "models\\items\\BoostItem.obj";
	HealthItem** m_HealthArray;
	char* m_healthModelPath = "models\\items\\HealthItem.obj";

	// Container für alle aktiven Geos, die mit dem Auto kollidieren können
	CGeos m_Geos;
};

