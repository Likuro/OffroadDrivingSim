#include "Vehicle.h"

void Vehicle::Init(CScene* scene, CPlacement* cam, CMaterial* mat, float accelerationValue, float deaccelerationValue, float maxSpeed) {

	scene->AddPlacement(&pos);
	model.Init(1, mat);
	pos.AddGeo(&model);

	pos.SetTranslationSensitivity(100.f);
	pos.SetRotationSensitivity(2.f);

	this->accelerator = accelerationValue;
	this->deaccelerator = deaccelerationValue;
	this->maxSpeed = maxSpeed;
}


CHMat Vehicle::GetMat()
{
	return pos.GetMat();
}
void Vehicle::SetMat(CHMat newMat)
{
	pos.SetMat(newMat);
}

float Vehicle::GetAccelerator()
{
	return accelerator;
}

float Vehicle::GetDeaccelerator()
{
	return deaccelerator;
}

