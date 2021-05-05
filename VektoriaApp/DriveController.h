#pragma once
#include "Vektoria\Root.h"
#include "Vehicle.h"

using namespace Vektoria;
enum  State
{
	forward, backward, stop
};
class DriveController
{	
public:
	void Init(CScene* scene, CViewport* viewport, Vehicle* car);
	void Brake();
	void ReleaseBrakes();
	void Accelerate(float deltaTime);
	void Deaccelerate(float deltaTime);
	void RotateRight(float deltaTime);
	void RotateLeft(float deltaTime);
	void GearUp();
	void GearDown();
	void ResetRotation(float deltaTime);
	float GetGas();
	float GetSpeed();
	int GetGear();
	void CalculateSpeed(float deltaTime);
	void DrivingState();
	State GetDrivingState();

	void Update(float deltaTime, CGeoTerrains& terrain, CGeos& groundItems, CGeos& collisionItems);

private:
	
	State myCarState;
	bool bBrake;
	float fBrake;
	float fGas;
	float fSteering;
	int iClutch;
	CKnack knackDrive;
	Vehicle* myCar;

	CGeoTerrains m_zgsColTerrain;

	CHVector oldPos;
	float time;
	float speed;
};
