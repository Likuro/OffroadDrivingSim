#pragma once
#include "PrefabRoad.h"

class SpecialPrefabRoad : public PrefabRoad
{
public:

	SpecialPrefabRoad(char* tmp_modelpath, char* tmp_groundhitboxpath, char* tmp_frontalhitboxpath, CGeos* tmp_roadTilesHitboxGround, CGeos* tmp_roadTilesHitboxFrontal, CHVector tmp_itemspawn1, CHVector tmp_itemspawn2, CHVector tmp_itemspawn3, int tmp_laneshift) 
	:PrefabRoad(tmp_modelpath, tmp_groundhitboxpath, tmp_frontalhitboxpath, tmp_roadTilesHitboxGround, tmp_roadTilesHitboxFrontal, tmp_itemspawn1, tmp_itemspawn2, tmp_itemspawn3), laneshift(tmp_laneshift) {};

	int getLaneShift();
private:

	//positive Werte -> links negative Werte -> rechts
	int laneshift;
};

