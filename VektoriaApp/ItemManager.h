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

private:
	int itemCount;
	CPlacement* Player;
	BoostItem* BoostArray;
	char* boostModelPath = "models\\items\\BoostItem.obj";
	HealthItem* HealthArray;
	char* healthModelPath = "models\\items\\HealthItem.obj";
};

