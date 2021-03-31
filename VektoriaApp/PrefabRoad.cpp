#include "PrefabRoad.h"

PrefabRoad::PrefabRoad(char* tmp_modelpath, char* tmp_hitboxpath, CGeos *tmp_roadTilesHitbox)
{
	strcpy(modelpath, tmp_modelpath);
	strcpy(hitboxpath, tmp_hitboxpath);
	roadModel = loadModel.LoadGeo(modelpath, true);
	roadHitbox = loadHitbox.LoadGeo(hitboxpath, true);
	tmp_roadTilesHitbox->Add(roadHitbox);
	
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
