#include "Vehicle.h"

void Vehicle::Init(CScene* scene, CPlacement* cam, CMaterial* mat, float accelerationValue, float deaccelerationValue, float maxSpeed) {

	scene->AddPlacement(&pos);

	char* modelPath = "models\\car\\offroadcar.obj";
	char* FR_Path = "models\\car\\FrontRight.obj";
	char* FL_Path = "models\\car\\FrontLeft.obj";

	pos.AddPlacement(&carFramePos);
	//model
	CFileWavefront file;
	carFramePos.AddPlacement(&model_Pos);
	modelGeo = file.LoadGeo(modelPath);
	model_Pos.AddGeo(modelGeo);	
	model_Pos.RotateYDelta(3.14);
	model_Pos.ScaleDelta(2,2,2);
	model_Pos.TranslateDelta(0,0.2,0);

	//front wheels
	carFramePos.AddPlacement(&frontWheels_Pos);
	frontWheels_Pos.Translate(0,-1,-3.1);

	frontWheels_Pos.AddPlacement(&wheel_FR);
	wheel_FR_Geo = file.LoadGeo(FR_Path);
	wheel_FR_zR.AddGeo(wheel_FR_Geo);
	wheel_FR.Translate(2.5, 0, 0);
	wheel_FR_Pos.ScaleDelta(2, 2, 2);
	wheel_FR.AddPlacement(&wheel_FR_Pos);
	wheel_FR_Pos.AddPlacement(&wheel_FR_zR);

	frontWheels_Pos.AddPlacement(&wheel_FL);
	wheel_FL_Geo = file.LoadGeo(FL_Path);
	wheel_FL_zR.AddGeo(wheel_FL_Geo);
	wheel_FL.Translate(-2.5, 0, 0);
	wheel_FL_Pos.ScaleDelta(2, 2, 2);
	wheel_FL.AddPlacement(&wheel_FL_Pos);
	wheel_FL_Pos.AddPlacement(&wheel_FL_zR);

	//back wheels
	carFramePos.AddPlacement(&backWheels_Pos);
	backWheels_Pos.Translate(0,-1,4.6);

	backWheels_Pos.AddPlacement(&wheel_BR);
	wheel_BR.Translate(2.2, 0, 0);
	wheel_BR_Pos.ScaleDelta(2, 2, 2);
	wheel_BR_Geo = file.LoadGeo(FR_Path);
	wheel_BR_Pos.AddGeo(wheel_BR_Geo);
	wheel_BR.AddPlacement(&wheel_BR_Pos);

	backWheels_Pos.AddPlacement(&wheel_BL);
	wheel_BL_Geo = file.LoadGeo(FL_Path);
	wheel_BL_Pos.AddGeo(wheel_BL_Geo);
	wheel_BL.Translate(-2.2, 0, 0);
	wheel_BL_Pos.ScaleDelta(2, 2, 2);
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
		currentMaxSpeed = (maxSpeed / 5) * gear;
	else
		currentMaxSpeed = (maxSpeed / 5);

}

void Vehicle::UpdateFrontWheels(float steeringRotation, float clutch, float speed)
{
	float rotationSpeed;
	if(clutch > 0)
		rotationSpeed = -speed * 0.001;
	else
		rotationSpeed = speed * 0.001;

	wheel_FR_Pos.RotateY(-steeringRotation * 4);
	wheel_FR_Pos.ScaleDelta(2, 2, 2);
	wheel_FL_Pos.RotateY(-steeringRotation * 4);
	wheel_FL_Pos.ScaleDelta(2, 2, 2);

	wheel_FR_zR.RotateXDelta(rotationSpeed);//
	wheel_FL_zR.RotateXDelta(rotationSpeed);//
	wheel_BR_Pos.RotateXDelta(rotationSpeed);
	wheel_BL_Pos.RotateXDelta(rotationSpeed);
}

