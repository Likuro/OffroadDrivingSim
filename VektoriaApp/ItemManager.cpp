#include "ItemManager.h"

ItemManager::ItemManager(int count)
{
	// Pooling der Items für bessere Performance und einfache Steuerung
	srand(time(NULL));
	itemcount = count;
	BoostArray = new BoostItem[itemcount];
	HealthArray = new HealthItem[itemcount];

	for (size_t i = 0; i < itemcount; i++)
	{
		BoostArray[i].Transform.SwitchOff();
		HealthArray[i].Transform.SwitchOff();
	}
}

CPlacement* ItemManager::getItem(itemType type)
{
	// schaut nach dem ersten Item das verfügbar ist, aktiviert dieses und gibt dies zurück

	if (type == random)
	{
		if ((rand() % 2) == 0)
		{
			type = boost;
		}
		else
		{
			type = health;
		}
	}
	if (type == boost)
	{
		for (size_t i = 0; i < itemcount; i++)
		{
			if (!BoostArray[i].Transform.IsOn())
			{
				this->BoostArray[i].Transform.SwitchOn();
				return &BoostArray->Transform;
			}
		}
	}
	if (type == health)
	{
		for (size_t i = 0; i < itemcount; i++)
		{
			if (!HealthArray[i].Transform.IsOn())
			{
				this->HealthArray[i].Transform.SwitchOn();
				return &HealthArray->Transform;
			}
		}

	}
	else
	{
		return nullptr;
	}
}

void ItemManager::update(float fTime, float fTimeDelta)
{
	// rufe update für alle items auf und checke Kollision mit dem Auto

	for (size_t i = 0; i < itemcount; i++)
	{
		// Collision Check mit Auto Placement
		//if (BoostArray[i].Transform.IsColliding())
		//{

		//}

		BoostArray[i].update(fTime, fTimeDelta);
		BoostArray[i].lifeTime += fTimeDelta;

		if (BoostArray[i].lifeTime > BoostArray[i].maxLifeTime)
		{
			BoostArray[i].lifeTime = 0;
			BoostArray[i].Transform.SwitchOff();
		}

		HealthArray[i].update(fTime, fTimeDelta);
		HealthArray[i].lifeTime += fTimeDelta;

		if (HealthArray[i].lifeTime > HealthArray[i].maxLifeTime)
		{
			HealthArray[i].lifeTime = 0;
			HealthArray[i].Transform.SwitchOff();
		}
	}
}
