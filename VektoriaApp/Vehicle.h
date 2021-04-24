#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;
class Vehicle
{
public:
	void Init(CScene* scene, CPlacement* cam, CMaterial* mat, float accelerationValue,float deaccelerationValue, float maxSpeed);

	CPlacement* GetMainPos();
	CHMat GetMat();
	void SetMat(CHMat newMat);

	float GetAccelerator();
	float GetDeaccelerator();

	float GetCurrentMaxSpeed();
	void SetCurrentMaxSpeed(int gear);

	void UpdateFrontWheels(float rotation, float gas, float speed);

private:

	CPlacement pos;

	CPlacement carFramePos;
	CGeo* modelGeo;
	CPlacement model_Pos;
	
	//Front Wheels
	CPlacement frontWheels_Pos;
	CGeo* wheel_FR_Geo;
	CPlacement wheel_FR_Pos;
	CPlacement wheel_FR;
	CPlacement wheel_FR_zR;
	CGeo* wheel_FL_Geo;
	CPlacement wheel_FL_Pos;
	CPlacement wheel_FL;
	CPlacement wheel_FL_zR;
	//Back Wheels
	CPlacement backWheels_Pos;
	CGeo* wheel_BR_Geo;
	CPlacement wheel_BR_Pos;
	CPlacement wheel_BR;
	CGeo* wheel_BL_Geo;
	CPlacement wheel_BL_Pos;
	CPlacement wheel_BL;
	//Emitter
	CPlacement emitterPos;

	CMaterial Material;

	float accelerator;
	float deaccelerator;
	float maxSpeed;
	float currentMaxSpeed;

	float lastSpeed, currentSpeed;
};

