#include "ItemManager.h"

ItemManager::ItemManager(int count, CPlacement* player)
{
	srand(time(NULL));
	m_Player = player;
	m_itemCount = count;
	
	// Items werden gepoolt
	m_BoostArray = new BoostItem*[m_itemCount];
	for (size_t i = 0; i < m_itemCount; i++)
	{
		m_BoostArray[i] = new BoostItem;
		m_BoostArray[i]->loadGeo(m_boostModelPath);
		m_BoostArray[i]->Transform.SwitchOff();
	}

	m_HealthArray = new HealthItem*[m_itemCount];
	for (size_t i = 0; i < m_itemCount; i++)
	{
		m_HealthArray[i] = new HealthItem;
		m_HealthArray[i]->loadGeo(m_healthModelPath);
		m_HealthArray[i]->Transform.SwitchOff();
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
		for (size_t i = 0; i < m_itemCount; i++)
		{
			if (!m_BoostArray[i]->Transform.IsOn())
			{
				m_BoostArray[i]->Transform.SwitchOn();
				m_Geos.Add(m_BoostArray[i]->Geo);
				return &m_BoostArray[i]->Transform;
			}
		}
	}
	if (type == health)
	{
		for (size_t i = 0; i < m_itemCount; i++)
		{
			if (!m_HealthArray[i]->Transform.IsOn())
			{
				m_HealthArray[i]->Transform.SwitchOn();
				m_Geos.Add(m_HealthArray[i]->Geo);
				return &m_HealthArray[i]->Transform;
			}
		}
	}
	return nullptr;
}

void ItemManager::update(float fTime, float fTimeDelta)
{
	// rufe update für alle items auf und checkt Kollision mit dem Auto
	Item* it;
	CHVector playerPos = m_Player->GetPos();
	CHVector playerDir = m_Player->GetDirection();
	CRay ray(playerPos, playerDir, 0.f, 1.f);
	CHMat playerMat = m_Player->GetMat();
	CHitPoint hitpoint;
	bool hasHit = false;

	if (m_pathRays.size() > 0)
	{
		for (auto vector : m_pathRays)
		{
			ray.Init((playerMat * *vector), playerDir);
			ray.SetMax(m_RayLength);
			if (hasHit = m_Geos.Intersects(ray, hitpoint))
				break;
		}
	}
	else
	{
		hasHit = m_Geos.Intersects(ray, hitpoint);
	}

	for (size_t i = 0; i < m_itemCount; i++)
	{
		it = m_BoostArray[i];
		if (it->Transform.IsOn())
		{
			it->update(fTime, fTimeDelta);

			if (hasHit && hitpoint.m_pzg == it->Geo)
			{
				it->trigger();
				it->resetItem();
				m_Geos.Sub(it->Geo);
			}
			else if (it->lifeTime > it->maxLifeTime)
			{
				it->resetItem();
				m_Geos.Sub(it->Geo);
			}
		}

		it = m_HealthArray[i];
		if (it->Transform.IsOn())
		{
			it->update(fTime, fTimeDelta);

			if (hasHit && hitpoint.m_pzg == it->Geo)
			{
				it->trigger();
				it->resetItem();
				m_Geos.Sub(it->Geo);
			}
			else if (it->lifeTime > it->maxLifeTime)
			{
				it->resetItem();
				m_Geos.Sub(it->Geo);
			}
		}
	}
}

void ItemManager::InitRays(CAABB* boundingBox)
{
	// Berechnen des Strahlenbüschels
	CHVector minBox = boundingBox->GetMin();
	CHVector maxBox = boundingBox->GetMax();
	m_RayLength = boundingBox->GetSize().z / 2.f;

	float width = maxBox.x - minBox.x;
	float height = maxBox.y - minBox.y;
	float div = sqrtf(m_RayMaxDist / 2.f);
	int widthDivided = width / div;
	int heightDivided = height / div;
	float widthDivValue = width / (float)widthDivided;
	float heightDivValue = height / (float)heightDivided;
	CHVector* tmp;

	for (size_t i = 0; i < widthDivided; i++)
	{
		for (size_t j = 0; j < heightDivided; j++)
		{
			tmp = new CHVector(minBox.x + (i * widthDivValue), minBox.y + (j * heightDivValue), 0.f);
			m_pathRays.push_back(tmp);
		}
	}
}
