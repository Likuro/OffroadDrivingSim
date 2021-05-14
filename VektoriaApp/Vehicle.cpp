#include "Vehicle.h"

void Vehicle::Init(CScene* scene, CPlacement* cam, CMaterial* mat, float accelerationValue, float deaccelerationValue, float maxSpeed) {

	scene->AddPlacement(&pos);
	//pos.GetMat().TranslateZ(10);
	char* modelPath = "models\\car\\Offroadcar_Toon.obj";
	char* FR_Path = "models\\car\\FrontRight_Toon.obj";
	char* FL_Path = "models\\car\\FrontLeft_Toon.obj";

	CHMat m;
	m.TranslateY(-1);

	pos.AddPlacement(&carFramePos);

	//carFramePos.Translate(CHVector(0,-3.f,0));
	
	//model
	CFileWavefront file;
	carFramePos.AddPlacement(&model_Pos);
	modelGeo = file.LoadGeo(modelPath);	
	modelGeo->Transform(m);
	model_Pos.AddGeo(modelGeo);	
	model_Pos.RotateYDelta(3.14);
	model_Pos.TranslateDelta(0,0.2,0);

	//modelGeo->m_anodeinstance[0].m_aabb.IsInside();

	//front wheels
	carFramePos.AddPlacement(&frontWheels_Pos);
	frontWheels_Pos.Translate(0,-1.28f,-1.15f);

	frontWheels_Pos.AddPlacement(&wheel_FR);
	wheel_FR_Geo = file.LoadGeo(FR_Path);
	//wheel_FR_Geo->Transform(m);
	wheel_FR_zR.AddGeo(wheel_FR_Geo);
	wheel_FR.Translate(0.92f, 0, 0);
	wheel_FR.AddPlacement(&wheel_FR_Pos);
	wheel_FR_Pos.AddPlacement(&wheel_FR_zR);

	frontWheels_Pos.AddPlacement(&wheel_FL);
	wheel_FL_Geo = file.LoadGeo(FL_Path);
	//wheel_FL_Geo->Transform(m);
	wheel_FL_zR.AddGeo(wheel_FL_Geo);
	wheel_FL.Translate(-0.92f, 0, 0);
	wheel_FL.AddPlacement(&wheel_FL_Pos);
	wheel_FL_Pos.AddPlacement(&wheel_FL_zR);

	//back wheels
	carFramePos.AddPlacement(&backWheels_Pos);
	backWheels_Pos.Translate(0,-1.28,1.85f);

	backWheels_Pos.AddPlacement(&wheel_BR);
	wheel_BR.Translate(0.9f, 0, 0);
	wheel_BR_Geo = file.LoadGeo(FR_Path);
	//wheel_BR_Geo->Transform(m);
	wheel_BR_Pos.AddGeo(wheel_BR_Geo);
	wheel_BR.AddPlacement(&wheel_BR_Pos);

	backWheels_Pos.AddPlacement(&wheel_BL);
	wheel_BL_Geo = file.LoadGeo(FL_Path);
	//wheel_BL_Geo->Transform(m);
	wheel_BL_Pos.AddGeo(wheel_BL_Geo);
	wheel_BL.Translate(-0.9f, 0, 0);
	wheel_BL.AddPlacement(&wheel_BL_Pos);

	backWheels_Pos.AddPlacement(&emitterPos);
	//Add emiiter effect to placement

	//carFramePos.RotateY(1.74);

	pos.SetTranslationSensitivity(100.f);
	pos.SetRotationSensitivity(2.f);

	this->accelerator = accelerationValue;
	this->deaccelerator = deaccelerationValue;
	this->maxSpeed = maxSpeed;
	this->currentMaxSpeed = 0;
}


CHMat Vehicle::GetMat()
{
	return pos.GetMat();
}
void Vehicle::SetMat(CHMat newMat)
{
	pos.SetMat(newMat);
}

CPlacement* Vehicle::GetMainPos()
{
	return &pos;
}

float Vehicle::GetAccelerator()
{
	return accelerator;
}

float Vehicle::GetDeaccelerator()
{
	return deaccelerator;
}

float Vehicle::GetCurrentMaxSpeed()
{
	return abs(currentMaxSpeed);
}

void Vehicle::SetCurrentMaxSpeed(int gear)
{
	if (gear >= 0)
		currentMaxSpeed = (maxSpeed / 6) * gear;
	else
		currentMaxSpeed = (maxSpeed / 6);

}

void Vehicle::UpdateFrontWheels(float steeringRotation, float clutch, float speed)
{
	float rotationSpeed;
	if(clutch > 0)
		rotationSpeed = -speed * 0.00125;
	else
		rotationSpeed = speed * 0.00125;

	wheel_FR_Pos.RotateY(-steeringRotation * 4);
	wheel_FL_Pos.RotateY(-steeringRotation * 4);

	wheel_FR_zR.RotateXDelta(rotationSpeed);
	wheel_FL_zR.RotateXDelta(rotationSpeed);
	wheel_BR_Pos.RotateXDelta(rotationSpeed);
	wheel_BL_Pos.RotateXDelta(rotationSpeed);
}

