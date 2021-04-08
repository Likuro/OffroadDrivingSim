#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;

class Item
{
public:
	// l�dt die Geometrie
	void loadGeo(char* path)
	{
		CFileWavefront file;
		Geo = file.LoadGeo(path);
		Transform.AddGeo(Geo);
	}

	// h�ngt das Item von dem dar�berliegendem Placement ab und schaltet sich aus; gibt true aus wenn erfolgreich
	bool resetItem()
	{
		if (this->Transform.GetParent() != nullptr)
		{
			this->lifeTime = 0;
			this->Transform.Rotate(0.f, 0.f, 0.f, 0.f);
			this->Transform.Translate(0.f, 0.f, 0.f);
			static_cast<CPlacement*>(this->Transform.GetParent())->SubPlacement(&this->Transform);
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

	// behandelt Animation oder �hnliches
	virtual void update(float fTime, float ftimeDelta) = 0;

	CMaterial Material;
	CFileWavefront IconObject;
	CGeo* Geo;
	CPlacement Transform;
	float lifeTime = 0.f;
	float maxLifeTime = 10.f;
	float amplitude = 0.25;
	float periode = 2;
};

