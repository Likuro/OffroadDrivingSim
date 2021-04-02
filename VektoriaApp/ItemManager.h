#pragma once
#include "Vektoria\Root.h"
#include "BoostItem.h"
#include "HealthItem.h"

using namespace Vektoria;

enum itemType { random, boost, health };

class ItemManager
{
public:
	ItemManager(int count);
	CPlacement* getItem(itemType type);
	void update(float fTime, float fTimeDelta);

private:
	int itemcount;
	BoostItem* BoostArray;
	HealthItem* HealthArray;
};

