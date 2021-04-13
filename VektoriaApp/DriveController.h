#pragma once
#include "Vektoria\Root.h"
#include "Vehicle.h"

using namespace Vektoria;
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
	void ChangeClutch(int clutch);

	void Update(float deltaTime, CGeoTerrains& terrain, CGeos& groundItems, CGeos& collisionItems);

private:
	bool bBrake;
	float fBrake;
	float fGas;
	float fSteering;
	int iClutch;
	CKnack knackDrive;
	Vehicle* myCar;

	CGeoTerrains m_zgsColTerrain;
};
