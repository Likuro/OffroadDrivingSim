#include "Vehicle.h"

void Vehicle::Init(CScene* scene, CPlacement* cam, CMaterial* mat, int carID) {

	scene->AddPlacement(&pos);
	pos.AddPlacement(&carFramePos);
	switch (carID)
	{
	case 0:
		BuildSuperCar(mat, carID);
		break;
	case 1:
		BuildMonsterTruck(mat, carID);
		break;
	case 2:
		BuildBus(mat, carID);
		break;
	case 3:
		BuildOldCar(mat, carID);
		break;
	default:
		break;
	}
	
	//carFramePos.Translate(CHVector(0,-3.f,0));
	
	this->currentMaxSpeed = 0;
}

void Vehicle::BuildSuperCar(CMaterial* mat, int ID)
{
	carID = ID;
	char* modelPath = "models\\Vehicles\\SuperCar\\Offroadcar_Toon.obj";
	char* FR_Path = "models\\Vehicles\\SuperCar\\FrontLeft_Toon.obj";
	char* FL_Path = "models\\Vehicles\\SuperCar\\FrontRight_Toon.obj";
	
	CHMat m;
	m.TranslateY(-1);

	//model
	CFileWavefront file;
	carFramePos.AddPlacement(&model_Pos);
	modelGeo = file.LoadGeo(modelPath, true);
	modelGeo->Transform(m);
	modelGeo->SetMaterial(mat);
	model_Pos.AddGeo(modelGeo);
	model_Pos.RotateYDelta(3.14);
	model_Pos.TranslateDelta(0, 0.2, 0);

	//modelGeo->m_anodeinstance[0].m_aabb.IsInside();

	//front wheels
	carFramePos.AddPlacement(&frontWheels_Pos);
	frontWheels_Pos.Translate(0, -1.28f, -1.15f);

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
	backWheels_Pos.Translate(0, -1.28, 1.85f);

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

	this->accelerator = 0.8f;
	this->deaccelerator = 0.2f;
	this->maxSpeed = 260;
}

void Vehicle::BuildMonsterTruck(CMaterial* mat, int ID)
{
	carID = ID;
	char* modelPath = "models\\Vehicles\\MonsterTruck\\TruckKarosserie.obj";
	char* FR_Path = "models\\Vehicles\\MonsterTruck\\FrontRight_Truck.obj";
	char* FL_Path = "models\\Vehicles\\MonsterTruck\\FrontLeft_Truck.obj";

	CHMat m;
	m.TranslateY(-0.3f);

	//model
	CFileWavefront file;
	carFramePos.AddPlacement(&model_Pos);
	modelGeo = file.LoadGeo(modelPath);
	modelGeo->Transform(m);
	modelGeo->SetMaterial(mat);
	model_Pos.AddGeo(modelGeo);
	model_Pos.RotateYDelta(3.14);
	model_Pos.TranslateDelta(0, 0.2, 0);

	//modelGeo->m_anodeinstance[0].m_aabb.IsInside();

	//front wheels
	carFramePos.AddPlacement(&frontWheels_Pos);
	frontWheels_Pos.Translate(0, -1.f, -2.4f);

	frontWheels_Pos.AddPlacement(&wheel_FR);
	wheel_FR_Geo = file.LoadGeo(FR_Path);
	//wheel_FR_Geo->Transform(m);
	wheel_FR_zR.AddGeo(wheel_FR_Geo);
	wheel_FR.Translate(1.3f, 0, 0);
	wheel_FR.AddPlacement(&wheel_FR_Pos);
	wheel_FR_Pos.AddPlacement(&wheel_FR_zR);

	frontWheels_Pos.AddPlacement(&wheel_FL);
	wheel_FL_Geo = file.LoadGeo(FL_Path);
	//wheel_FL_Geo->Transform(m);
	wheel_FL_zR.AddGeo(wheel_FL_Geo);
	wheel_FL.Translate(-1.15f, 0, 0);
	wheel_FL.AddPlacement(&wheel_FL_Pos);
	wheel_FL_Pos.AddPlacement(&wheel_FL_zR);

	//back wheels
	carFramePos.AddPlacement(&backWheels_Pos);
	backWheels_Pos.Translate(0, -1.f, 2.7f);

	backWheels_Pos.AddPlacement(&wheel_BR);
	wheel_BR.Translate(1.2f, 0, 0);
	wheel_BR_Geo = file.LoadGeo(FR_Path);
	//wheel_BR_Geo->Transform(m);
	wheel_BR_Pos.AddGeo(wheel_BR_Geo);
	wheel_BR.AddPlacement(&wheel_BR_Pos);

	backWheels_Pos.AddPlacement(&wheel_BL);
	wheel_BL_Geo = file.LoadGeo(FL_Path);
	//wheel_BL_Geo->Transform(m);
	wheel_BL_Pos.AddGeo(wheel_BL_Geo);
	wheel_BL.Translate(-1.05f, 0, 0);
	wheel_BL.AddPlacement(&wheel_BL_Pos);

	backWheels_Pos.AddPlacement(&emitterPos);
	//Add emiiter effect to placement

	//carFramePos.RotateY(1.74);

	pos.SetTranslationSensitivity(100.f);
	pos.SetRotationSensitivity(2.f);

	this->accelerator = 0.8f;
	this->deaccelerator = 0.2f;
	this->maxSpeed = 170;
}

void Vehicle::BuildBus(CMaterial* mat, int ID)
{
	carID = ID;
	char* modelPath = "models\\Vehicles\\Bus\\BusKarosserie.obj";
	char* FR_Path = "models\\Vehicles\\Bus\\BusFrontRight.obj";
	char* FL_Path = "models\\Vehicles\\Bus\\BusFrontLeft.obj";

	CHMat m;
	m.TranslateY(0.2f);

	//model
	CFileWavefront file;
	carFramePos.AddPlacement(&model_Pos);
	modelGeo = file.LoadGeo(modelPath);
	modelGeo->Transform(m);
	modelGeo->SetMaterial(mat);
	model_Pos.AddGeo(modelGeo);
	model_Pos.RotateYDelta(3.14);
	model_Pos.TranslateDelta(0, 0.2, 0);

	//modelGeo->m_anodeinstance[0].m_aabb.IsInside();

	//front wheels
	carFramePos.AddPlacement(&frontWheels_Pos);
	frontWheels_Pos.Translate(0, -1.f, -2.8f);

	frontWheels_Pos.AddPlacement(&wheel_FR);
	wheel_FR_Geo = file.LoadGeo(FR_Path);
	//wheel_FR_Geo->Transform(m);
	wheel_FR_zR.AddGeo(wheel_FR_Geo);
	wheel_FR.Translate(1.5f, 0, 0);
	wheel_FR.AddPlacement(&wheel_FR_Pos);
	wheel_FR_Pos.AddPlacement(&wheel_FR_zR);

	frontWheels_Pos.AddPlacement(&wheel_FL);
	wheel_FL_Geo = file.LoadGeo(FL_Path);
	//wheel_FL_Geo->Transform(m);
	wheel_FL_zR.AddGeo(wheel_FL_Geo);
	wheel_FL.Translate(-1.5f, 0, 0);
	wheel_FL.AddPlacement(&wheel_FL_Pos);
	wheel_FL_Pos.AddPlacement(&wheel_FL_zR);

	//back wheels
	carFramePos.AddPlacement(&backWheels_Pos);
	backWheels_Pos.Translate(0, -1.f, 2.3f);

	backWheels_Pos.AddPlacement(&wheel_BR);
	wheel_BR.Translate(1.5f, 0, 0);
	wheel_BR_Geo = file.LoadGeo(FR_Path);
	//wheel_BR_Geo->Transform(m);
	wheel_BR_Pos.AddGeo(wheel_BR_Geo);
	wheel_BR.AddPlacement(&wheel_BR_Pos);

	backWheels_Pos.AddPlacement(&wheel_BL);
	wheel_BL_Geo = file.LoadGeo(FL_Path);
	//wheel_BL_Geo->Transform(m);
	wheel_BL_Pos.AddGeo(wheel_BL_Geo);
	wheel_BL.Translate(-1.5f, 0, 0);
	wheel_BL.AddPlacement(&wheel_BL_Pos);

	backWheels_Pos.AddPlacement(&emitterPos);
	//Add emiiter effect to placement

	//carFramePos.RotateY(1.74);

	pos.SetTranslationSensitivity(100.f);
	pos.SetRotationSensitivity(2.f);

	this->accelerator = 0.8f;
	this->deaccelerator = 0.2f;
	this->maxSpeed = 120;
}

void Vehicle::BuildOldCar(CMaterial* mat, int ID)
{
	carID = ID;
	char* modelPath = "models\\Vehicles\\OldCar\\OldCarKarosserie.obj";
	char* FR_Path = "models\\Vehicles\\OldCar\\OldCarFrontRight.obj";
	char* FL_Path = "models\\Vehicles\\OldCar\\OldCarFrontLeft.obj";

	CHMat m;
	m.TranslateY(-0.9f);

	//model
	CFileWavefront file;
	carFramePos.AddPlacement(&model_Pos);
	modelGeo = file.LoadGeo(modelPath);
	modelGeo->Transform(m);
	modelGeo->SetMaterial(mat);
	model_Pos.AddGeo(modelGeo);
	model_Pos.RotateYDelta(3.14);
	model_Pos.TranslateDelta(0, 0.2, 0);

	//modelGeo->m_anodeinstance[0].m_aabb.IsInside();

	//front wheels
	carFramePos.AddPlacement(&frontWheels_Pos);
	frontWheels_Pos.Translate(0, -1.28f, -2.15f);

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
	wheel_FL.Translate(-0.82f, 0, 0);
	wheel_FL.AddPlacement(&wheel_FL_Pos);
	wheel_FL_Pos.AddPlacement(&wheel_FL_zR);

	//back wheels
	carFramePos.AddPlacement(&backWheels_Pos);
	backWheels_Pos.Translate(0, -1.28, 1.15f);

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
	wheel_BL.Translate(-0.8f, 0, 0);
	wheel_BL.AddPlacement(&wheel_BL_Pos);

	backWheels_Pos.AddPlacement(&emitterPos);
	//Add emiiter effect to placement

	//carFramePos.RotateY(1.74);

	pos.SetTranslationSensitivity(100.f);
	pos.SetRotationSensitivity(2.f);

	this->accelerator = 0.8f;
	this->deaccelerator = 0.2f;
	this->maxSpeed = 180;
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

int Vehicle::GetCarID()
{
	return carID;
}

