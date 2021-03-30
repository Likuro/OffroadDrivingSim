#include "PrefabRoad.h"

PrefabRoad::PrefabRoad(char *tmp_path)
{
	strcpy(path, tmp_path);
	RoadModel = LoadModel.LoadGeo(path, true);
}

PrefabRoad::~PrefabRoad(void)
{
}

void PrefabRoad::addtoScene(CPlacement *tmp_roadPlacement)
{
	tmp_roadPlacement->AddGeo(RoadModel);
}

void PrefabRoad::subfromScene(CPlacement* tmp_roadPlacement)
{
	tmp_roadPlacement->SubGeo(RoadModel);
}
