#include "ItemManager.h"

ItemManager::ItemManager(int count, CPlacement* player)
{
	srand(time(NULL));
	Player = player;
	itemCount = count;

	// Geometrien für Items werden einmal geladen
	CFileWavefront Obj;
	CGeo* Geometrie;
	
	// Items werden gepoolt
	BoostArray = new BoostItem[itemCount];
	Geometrie = Obj.LoadGeo(boostModelPath);
	for (size_t i = 0; i < itemCount; i++)
	{
		BoostArray[i].loadGeo(Geometrie);
		BoostArray[i].Transform.SwitchOff();
	}

	HealthArray = new HealthItem[itemCount];
	Geometrie = Obj.LoadGeo(healthModelPath);
	for (size_t i = 0; i < itemCount; i++)
	{
		HealthArray[i].loadGeo(Geometrie);
		HealthArray[i].Transform.SwitchOff();
	}
}

CPlacement* ItemManager::getItem(itemType type)
{
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
		for (size_t i = 0; i < itemCount; i++)
		{
			if (!BoostArray[i].Transform.IsOn())
			{
				BoostArray[i].Transform.SwitchOn();
				return &BoostArray[i].Transform;
			}
		}
	}
	if (type == health)
	{
		for (size_t i = 0; i < itemCount; i++)
		{
			if (!HealthArray[i].Transform.IsOn())
			{
				HealthArray[i].Transform.SwitchOn();
				return &HealthArray[i].Transform;
			}
		}
	}
	return nullptr;
}

void ItemManager::update(float fTime, float fTimeDelta)
{
	// update Geos und hänge alle aktiven Items an
	//CGeos Geos;
	//for (size_t i = 0; i < itemCount; i++)
	//{
	//	if (BoostArray[i].Transform.IsOn())
	//	{
	//		Geos.Add(&BoostArray[i].Geo);
	//	}
	//}
	//for (size_t i = 0; i < itemCount; i++)
	//{
	//	if (HealthArray[i].Transform.IsOn())
	//	{
	//		Geos.Add(&HealthArray[i].Geo);
	//	}
	//}
	CHVector vector;
	vector = CHVector(0.f, 0.f, 0.f);
	// rufe update für alle items auf und checkt Kollision mit dem Auto
	Item* it;
	CRay ray;
	ray.Init(Player->GetPos(), Player->GetDirection());
	CHitPoint hitpoint;
	bool hasHit = false; //Geos.Intersects(ray, hitpoint); //  Geos.Intersects(ray, hitpoint) wirft einen Stack Overflow noice

	for (size_t i = 0; i < itemCount; i++)
	{
		it = &BoostArray[i];
		if (it->Transform.IsOn())
		{
			it->update(fTime, fTimeDelta);

			if (hasHit)
			{
				//it->trigger();	// muss noch implementiert werden um etwas zu machen
				//it->resetItem();
			}
			if (hasHit && hitpoint.m_pzg->GetID() == it->Geo.GetID())
			{
				it->trigger();
				it->resetItem();
			}
			else if (it->lifeTime > it->maxLifeTime)
			{
				it->resetItem();
			}
		}

		it = &HealthArray[i];
		if (it->Transform.IsOn())
		{
			it->update(fTime, fTimeDelta);

			//if (it->Geo.Intersects(ray, hitpoint))
			//{
			//	it->trigger();	// muss noch implementiert werden um etwas zu machen
			//	it->deleteItem();
			//}
			if (hasHit && hitpoint.m_pzg->GetID() == it->Geo.GetID())
			{
				it->trigger();
				it->resetItem();
			}
			else if (it->lifeTime > it->maxLifeTime)
			{
				it->resetItem();
			}
		}
	}
}
