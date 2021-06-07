#pragma once
#include "Vektoria\Root.h"

#define switchTime 10000


using namespace Vektoria;

class SkyManager
{
public:
	void init(CScene* tmp_scene, CPlacement* tmp_camera, CCamera* tmp_Ccamera);
	void update(int tmp_score);
private:

	float scoreTime;

	CScene* mySkyScene;
};
