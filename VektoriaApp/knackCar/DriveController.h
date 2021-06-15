#pragma once
#include "Vektoria\Root.h"
#include "Vehicle.h"
#include "Boost.h"
#include "Health.h"

#define CARITEM_DRIVER 12
#define MAX_HEALTH 100
#define MAX_BOOST 100
// Usage per second
#define BOOST_USAGE 10

using namespace Vektoria;
enum  State
{
	forward, backward, stop
};
class DriveController
{
public:

	void Init(CScene* scene, CViewport* viewport, Vehicle* car);
	void reignite();
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

	void useBoost(float fTimeDelta);
	void setUseBoost(bool use);

	Health* getHealth();
	Boost* getBoost();

	void resetCar(int carID);
	void Update(float deltaTime, CGeoTerrains& terrain, CGeos& groundItems, CGeos& collisionItems);
	void CheckCollisions(CGeos* obstacle_Geos);
	void DealDamage();

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

	CHMat mDriver;
	CHMat mChassis;

	// Health and Boost
	Boost* mBoost;
	bool mUseBoost = false;
	Health* mHealth;

	//Collision Stuff
	float m_RayLength;
	float m_RayMaxDist = 0.3f;
	std::vector<CHVector*> m_pathRays;
	CHVector m_oldPlayerPos;
	bool o_Collided = false;
	CGeo* currentColObject;
	CGeo* lastColObject;
	float collisionCooldown = 0.1f;
};
