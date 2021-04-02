#include "PrefabRoad.h"

PrefabRoad::PrefabRoad(char* tmp_modelpath, char* tmp_hitboxpath, CGeos *tmp_roadTilesHitbox, CHVector tmp_itemspawn1, CHVector tmp_itemspawn2, CHVector tmp_itemspawn3)
{
	strcpy(modelpath, tmp_modelpath);
	strcpy(hitboxpath, tmp_hitboxpath);
	roadModel = loadModel.LoadGeo(modelpath, true);
	roadHitbox = loadHitbox.LoadGeo(hitboxpath, true);
	tmp_roadTilesHitbox->Add(roadHitbox);

	itemspawns[0] = tmp_itemspawn1;
	itemspawns[1] = tmp_itemspawn2;
	itemspawns[2] = tmp_itemspawn3;
	
}

PrefabRoad::~PrefabRoad(void)
{
}

void PrefabRoad::addtoScene(CPlacement *tmp_roadPlacement, CPlacement* tmp_hitboxPlacement)
{
	tmp_roadPlacement->AddGeo(roadModel);
	tmp_hitboxPlacement->AddGeo(roadHitbox);
}

void PrefabRoad::subfromScene(CPlacement* tmp_roadPlacement, CPlacement* tmp_hitboxPlacement)
{
	tmp_roadPlacement->SubGeo(roadModel);
	tmp_hitboxPlacement->SubGeo(roadHitbox);
}

CHVector PrefabRoad::getItemspawnPosition()
{
	return itemspawns[std::rand() % 3];
}
