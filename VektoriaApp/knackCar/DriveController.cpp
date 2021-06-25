#include "DriveController.h"

void DriveController::Init(CScene* scene, CViewport* viewport, Vehicle* car)
{
	myCar = car;
	
	switch (myCar->GetCarID())
	{
	case 0:
		knackDrive.Init("Drive", "SuperCar.ini", scene, viewport);
		break;
	case 1:
		knackDrive.Init("Drive", "MonsterTruck.ini", scene, viewport);
		break;
	case 2:
		knackDrive.Init("Drive", "Bus.ini", scene, viewport);
		break;
	case 3:
		knackDrive.Init("Drive", "OldCar.ini", scene, viewport);
		break;
	default:
		break;
	}

	knackDrive.Ignite(myCar->GetMat());
	bBrake = false;
	fBrake = 0.0f;
	fGas = 0.0f;
	fSteering = 0.0f;
	iClutch = 0;

	time = 0;
	oldPos = myCar->GetMainPos()->GetPos();
	mBoost = new Boost(MAX_BOOST, MAX_BOOST);
	mHealth = new Health(MAX_HEALTH, MAX_HEALTH);

	m_oldPlayerPos.Null();
}

void DriveController::reignite()
{
	knackDrive.Reset();
	knackDrive.Ignite(myCar->GetMat());
	mBoost->setBoost(MAX_BOOST);
	mHealth->setHealth(MAX_HEALTH);
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
	fSteering += deltaTime * 0.08f;
	UM_SETINRANGE(fSteering, -0.15, 0.15);
	//UM_SETINRANGE(fSteering, -QUARTERPI, +QUARTERPI);
}

void DriveController::RotateLeft(float deltaTime)
{
	fSteering -= deltaTime * 0.08f;
	UM_SETINRANGE(fSteering, -0.15, 0.15);
	//UM_SETINRANGE(fSteering, -QUARTERPI, +QUARTERPI);
}

void DriveController::GearUp()
{
	iClutch += 1;
	UM_SETINRANGE(iClutch, -1, 6);
	myCar->SetCurrentMaxSpeed(iClutch);
}

void DriveController::GearDown()
{
	float newClutch = iClutch - 1;
	if (myCarState == forward && newClutch < 0 && speed > 5) {
		return;
	}
	else
		iClutch -= 1;
	UM_SETINRANGE(iClutch, -1, 5);
	myCar->SetCurrentMaxSpeed(iClutch);
}

void DriveController::ResetRotation(float deltaTime)
{
	if (fSteering == 0)
		return;
	else {
		if (fSteering > 0)
			fSteering -= deltaTime * 0.02f;
		else if (fSteering < 0)
			fSteering += deltaTime * 0.02f;
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
	if (time >= 0.1F) {
		speed = myCar->GetMainPos()->GetPos().Dist(oldPos) / time; //returns Speed as in how much distance has been crossed in 1 second.
		oldPos = myCar->GetMainPos()->GetPos();
		time = 0;
	}
	time += deltaTime;
}

void DriveController::DrivingState()
{
	CHVector difference = myCar->GetMainPos()->GetPos() - oldPos;
	if (myCar->GetMainPos()->GetPos().z < oldPos.z)
		myCarState = forward;
	else if (myCar->GetMainPos()->GetPos().z > oldPos.z)
		myCarState = backward;
	else 
		myCarState = stop;
}

State DriveController::GetDrivingState()
{
	return myCarState;
}

void DriveController::useBoost(float fTimeDelta)
{
	if (!mBoost->isEmpty())
	{
		mBoost->substractBoost(float(BOOST_USAGE) * fTimeDelta);
		mUseBoost = true;
	}
	else
	{
		mUseBoost = false;
	}
}

void DriveController::setUseBoost(bool use)
{
	mUseBoost = use;
}

Health* DriveController::getHealth()
{
	return mHealth;
}

Boost* DriveController::getBoost()
{
	return mBoost;
}

void DriveController::Update(float deltaTime, CGeoTerrains& terrain, CGeos& groundItems, CGeos& collisionItems)
{
	if (myCar->GetCurrentMaxSpeed() <= speed)
		fGas = 0;
	if (iClutch == -1 && myCarState == forward) {
		if (speed >= 10) {
			Brake();
			fGas = 0;
		}
		else
			ReleaseBrakes();
	}	

	knackDrive.Input(fGas, fBrake, fSteering, iClutch, mUseBoost);
	knackDrive.Tick(deltaTime, terrain, groundItems, collisionItems);

#define CARITEM_DRIVER 12
	mDriver = knackDrive.GetPropMat(CARITEM_DRIVER, 0u());

#define CARITEM_CHASSIS 0
	mChassis = knackDrive.GetPropMat(CARITEM_CHASSIS, 0u());
	mChassis.CopyRotation(mDriver);
	myCar->SetMat(mChassis);

	myCar->UpdateFrontWheels(fSteering, iClutch, speed);
	CalculateSpeed(deltaTime);
	DrivingState();
	collisionCooldown -= deltaTime;
}

void DriveController::CheckCollisions(CGeos* obstacle_Geos)
{
	bool currentCollided = false;
	if (m_pathRays.size() == 0) {
		m_pathRays.clear();
		// Berechnen des Strahlenbüschels
		CHVector minBox = myCar->GetMainPos()->GetAABB()->GetMin();
		CHVector maxBox = myCar->GetMainPos()->GetAABB()->GetMax();
		m_RayLength = myCar->GetMainPos()->GetAABB()->GetSize().z / 2.f;

		float width = maxBox.x - minBox.x;
		float height = maxBox.y - minBox.y;
		float div = sqrtf(m_RayMaxDist / 2.f);
		int widthDivided = width / div;
		int heightDivided = height / div;
		float widthDivValue = width / (float)widthDivided;
		float heightDivValue = height / (float)heightDivided;
		CHVector* tmp;

		for (size_t i = 0; i < widthDivided; i++)
		{
			for (size_t j = 0; j < heightDivided; j++)
			{
				tmp = new CHVector(minBox.x + (i * widthDivValue), minBox.y + (j * heightDivValue), 0.f);
				m_pathRays.push_back(tmp);
			}
		}
	}

	////////////////////////////////////////////////
	CHVector playerPos = myCar->GetMainPos()->GetPos();
	CHVector playerDir = myCar->GetMainPos()->GetPos() - m_oldPlayerPos;
	m_oldPlayerPos = myCar->GetMainPos()->GetPos();
	playerDir.Norm();
	CRay ray(playerPos, playerDir, 0.f, 1.f);
	CHMat playerMat = myCar->GetMainPos()->GetMat();
	CHitPoint hitpoint;
	bool hasHit = false;

	if (m_pathRays.size() > 0 && collisionCooldown <= 0)
	{
		for (auto vector : m_pathRays)
		{
			ray.Init((playerMat * *vector), playerDir);
			ray.SetMax(m_RayLength);
			if (hasHit = obstacle_Geos->Intersects(ray, hitpoint)) {
				ULDebug("Hit Cube");
				currentCollided = true;
				currentColObject = hitpoint.m_pzg;
				collisionCooldown = 0.15f;
				break;
			}
			else {
				currentCollided = false;
			}
		}
		if (currentCollided)
			o_Collided = true;
		else {
			o_Collided = false;
			lastColObject = NULL;			
		}
	}
	DealDamage();
}
void DriveController::DealDamage() {
	if (lastColObject != currentColObject && o_Collided) {
		mHealth->dealDamage(10);		
		lastColObject = currentColObject;
	}
	ULDebug("%i" , mHealth->getHealth());
}
