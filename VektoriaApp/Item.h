#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;

class Item
{
public:

	// wird von dem anderen kollidierenden Objekt aufgerufen
	// stellt die Funktion des Items dar
	virtual void trigger() = 0;

	// behandelt Animation oder ähnliches
	virtual void update(float fTime, float ftimeDelta) = 0;

	CPlacement Transform;
	CMaterial Material;
	CFileWavefront IconObject;
	CGeo* Icon;
	float lifeTime = 0.f;
	float maxLifeTime = 10.f;
	float amplitude = 0.25;
	float periode = 2;
};

