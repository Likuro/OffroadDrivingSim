#include "DriveController.h"

void DriveController::Init(CScene* scene, CViewport* viewport, Vehicle* car)
{
	knackDrive.Init("Drive", "car_flunder.ini", scene, viewport);
	myCar = car;
	knackDrive.Ignite(myCar->GetMat());
	bBrake = false;
	fBrake = 0.0f;
	fGas = 0.0f;
	fSteering = 0.0f;
	iClutch = 0;
}

void DriveController::Brake()
{
	fBrake = 1;
}

void DriveController::ReleaseBrakes()
{
	fBrake = 0;
}

void DriveController::Accelerate(float deltaTime)
{
	fGas += deltaTime * myCar->GetAccelerator();
	//UM_SETINRANGEFR(fGas);
}

void DriveController::Deaccelerate(float deltaTime)
{
	fGas -= deltaTime * myCar->GetDeaccelerator();
	UM_SETINRANGEFR(fGas);
}

void DriveController::RotateRight(float deltaTime)
{
	fSteering += deltaTime * 0.5f;
	UM_SETINRANGE(fSteering, -QUARTERPI, +QUARTERPI);
}

void DriveController::RotateLeft(float deltaTime)
{
	fSteering -= deltaTime * 0.5f;
	UM_SETINRANGE(fSteering, -QUARTERPI, +QUARTERPI);
}

void DriveController::ChangeClutch(int clutch)
{
	iClutch = clutch;
	UM_SETINRANGE(iClutch, -1, 5);
}

void DriveController::Update(float deltaTime, CGeoTerrains& terrain, CGeos& groundItems, CGeos& collisionItems)
{
	knackDrive.Input(fGas, fBrake, fSteering, iClutch, 0);
	knackDrive.Tick(deltaTime, terrain, groundItems, collisionItems);
#define CARITEM_DRIVER 12
	myCar->SetMat(knackDrive.GetPropMat(CARITEM_DRIVER, 0u()));
}
