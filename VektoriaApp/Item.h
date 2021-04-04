#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;

class Item
{
public:
	// lädt die Geometrie
	void loadGeo(CGeo* g)
	{
		Geo = *g;
		Transform.AddGeo(g);
	}

	// hängt das Item von dem darüberliegendem Placement ab und schaltet sich aus; gibt true aus wenn erfolgreich
	bool resetItem()
	{
		if (this->Transform.GetParent() != nullptr)
		{
			this->lifeTime = 0;
			this->Transform.Rotate(0.f, 0.f, 0.f, 0.f);
			this->Transform.Translate(0.f, 0.f, 0.f);
			this->Transform.GetParent()->m_nodesChildren.Sub(&Transform);
			this->Transform.SwitchOff();
			return true;
		}
		else
		{
			this->lifeTime = 0;
			this->Transform.Rotate(0.f, 0.f, 0.f, 0.f);
			this->Transform.Translate(0.f, 0.f, 0.f);
			this->Transform.SwitchOff();
			return true;
		}
		return false;
	}
	// stellt die Funktion des Items dar
	virtual void trigger() = 0;

	// behandelt Animation oder ähnliches
	virtual void update(float fTime, float ftimeDelta) = 0;

	CMaterial Material;
	CFileWavefront IconObject;
	CGeo Geo;
	CPlacement Transform;
	float lifeTime = 0.f;
	float maxLifeTime = 10.f;
	float amplitude = 0.25;
	float periode = 2;
};

