#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;
class Vehicle
{
public:
	void Init(CScene* scene, CPlacement* cam, CMaterial* mat, float accelerationValue,float deaccelerationValue, float maxSpeed);

	CHMat GetMat();
	void SetMat(CHMat newMat);
	CPlacement pos;
	float GetAccelerator();
	float GetDeaccelerator();
private:

	CGeoCube model;
	float accelerator;
	float deaccelerator;
	float maxSpeed;
};
