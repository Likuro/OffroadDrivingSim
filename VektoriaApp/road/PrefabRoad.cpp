#include "PrefabRoad.h"

PrefabRoad::PrefabRoad(char* tmp_modelpath, char* tmp_groundhitboxpath, char* tmp_frontalhitboxpath, CGeos *tmp_roadTilesHitboxGround, CGeos* tmp_roadTilesHitboxFrontal, CHVector tmp_itemspawn1, CHVector tmp_itemspawn2, CHVector tmp_itemspawn3)
{
	strcpy(modelpath, tmp_modelpath);
	strcpy(groundhitboxpath, tmp_groundhitboxpath);
	strcpy(frontalhitboxpath, tmp_frontalhitboxpath);
	roadModel = loadModel.LoadGeo(modelpath, true);
	roadHitboxGround = loadHitboxGround.LoadGeo(groundhitboxpath, true);
	roadHitboxFrontal = loadHitboxFrontal.LoadGeo(frontalhitboxpath, true);

	roadModel->EstimateTangentsAndBitangents2();

	tmp_roadTilesHitboxGround->Add(roadHitboxGround);
	tmp_roadTilesHitboxFrontal->Add(roadHitboxFrontal);

	itemspawns[0] = tmp_itemspawn1;
	itemspawns[1] = tmp_itemspawn2;
	itemspawns[2] = tmp_itemspawn3;
	
}

PrefabRoad::~PrefabRoad(void)
{
}

void PrefabRoad::addtoScene(CPlacement *tmp_roadPlacement, CPlacement* tmp_hitboxGroundPlacement, CPlacement* tmp_hitboxFrontalPlacement)
{
	tmp_roadPlacement->AddGeo(roadModel);
	tmp_hitboxGroundPlacement->AddGeo(roadHitboxGround);
	tmp_hitboxFrontalPlacement->AddGeo(roadHitboxFrontal);
}

void PrefabRoad::subfromScene(CPlacement* tmp_roadPlacement, CPlacement* tmp_hitboxGroundPlacement, CPlacement* tmp_hitboxFrontalPlacement)
{
	tmp_roadPlacement->SubGeo(roadModel);
	tmp_hitboxGroundPlacement->SubGeo(roadHitboxGround);
	tmp_hitboxFrontalPlacement->SubGeo(roadHitboxFrontal);
}

void PrefabRoad::addMaterial(char *tmp_basecolor, char *tmp_heightmap, char *tmp_normalmap, char *tmp_roughness)
{
	myMaterial.MakeTextureDiffuse(tmp_basecolor);
	//myMaterial.MakeTextureHeight(tmp_heightmap);
	myMaterial.MakeTextureBump(tmp_normalmap);
	//Roughness muss noch importiert werden
	myMaterial.MakeTextureSpecular(tmp_roughness);

	roadModel->SetMaterial(&myMaterial);
}

void PrefabRoad::addMaterial(CMaterial* tmp_material)
{
	roadModel->SetMaterial(tmp_material);
}

CHVector PrefabRoad::getItemspawnPosition()
{
	return itemspawns[std::rand() % 3];
}
