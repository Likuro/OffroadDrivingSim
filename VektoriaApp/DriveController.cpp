#include "DriveController.h"

void DriveController::Init(CScene* scene, CViewport* viewport, Vehicle* car)
{
	myCar = car;
	knackDrive.Init("Drive", "car_test.ini", scene, viewport);
	knackDrive.Ignite(myCar->GetMat());
	bBrake = false;
	fBrake = 0.0f;
	fGas = 0.0f;
	fSteering = 0.0f;
	iClutch = 0;

	time = 0;
	oldPos = myCar->pos.GetPos();
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
	UM_SETINRANGE(fGas, 0, 1);
}

void DriveController::Deaccelerate(float deltaTime)
{
	fGas -= deltaTime * myCar->GetDeaccelerator();
	UM_SETINRANGE(fGas, 0, 1);
}

void DriveController::RotateRight(float deltaTime)
{
	fSteering += deltaTime * 0.05f;
	UM_SETINRANGE(fSteering, -0.15, 0.15);
	//UM_SETINRANGE(fSteering, -QUARTERPI, +QUARTERPI);
}

void DriveController::RotateLeft(float deltaTime)
{
	fSteering -= deltaTime * 0.05f;
	UM_SETINRANGE(fSteering, -0.15, 0.15);
	//UM_SETINRANGE(fSteering, -QUARTERPI, +QUARTERPI);
}

void DriveController::ChangeClutch(int clutch)
{
	iClutch = clutch;
	UM_SETINRANGE(iClutch, -1, 5);
	myCar->SetCurrentMaxSpeed(clutch);
}

void DriveController::ResetRotation(float deltaTime)
{
	if (fSteering == 0)
		return;
	else {
		if (fSteering > 0)
			fSteering -= deltaTime * 0.008f;
		else if (fSteering < 0)
			fSteering += deltaTime * 0.008f;
	}
}

float DriveController::GetGas()
{
	return fGas;
}

float DriveController::GetSpeed()
{
	return speed;
}

int DriveController::GetGear()
{
	return iClutch;
}

void DriveController::CalculateSpeed(float deltaTime)
{
	if (time >= 1) {
		speed = myCar->pos.GetPos().Dist(oldPos) / time; //returns Speed as in how much distance has been crossed in 1 second.
		oldPos = myCar->pos.GetPos();
		time = 0;
	}
	time += deltaTime;
}

void DriveController::Update(float deltaTime, CGeoTerrains& terrain, CGeos& groundItems, CGeos& collisionItems)
{
	if (myCar->GetCurrentMaxSpeed() - 2 <= speed)
		fGas = 0;

	knackDrive.Input(fGas, fBrake, fSteering, iClutch, 0);
	knackDrive.Tick(deltaTime, terrain, groundItems, collisionItems);
#define CARITEM_DRIVER 12
	myCar->SetMat(knackDrive.GetPropMat(CARITEM_DRIVER, 0u()));

	myCar->UpdateFrontWheels(fSteering, iClutch, speed);
	CalculateSpeed(deltaTime);
}
