#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;
class Vehicle
{
public:
	void Init(CPlacement* scene, CPlacement* cam, int carID);
	void BuildSuperCar(int ID);
	void BuildMonsterTruck(int ID);
	void BuildBus(int ID);
	void BuildOldCar(int ID);

	CPlacement* GetMainPos();
	CHMat GetMat();
	void SetMat(CHMat newMat);

	float GetAccelerator();
	float GetDeaccelerator();

	float GetCurrentMaxSpeed();
	void SetCurrentMaxSpeed(int gear);

	void UpdateFrontWheels(float rotation, float gas, float speed);
	int GetCarID();

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
	int carID;

	// Super Car Materials
	CMaterial m_MSuperCar;
	CMaterial m_MSuperCarWheelsR;
	CMaterial m_MSuperCarWheelsL;

	// Truck Materials
	CMaterial m_MTruck;
	CMaterial m_MTruckWheelsR;
	CMaterial m_MTruckWheelsL;

	// Bus Materials
	CMaterial m_MBus;
	CMaterial m_MBusWheelsR;
	CMaterial m_MBusWheelsL;

	// Old Car Materials
	CMaterial m_MOldCar;
	CMaterial m_MOldCarWheelsR;
	CMaterial m_MOldCarWheelsL;
};