#pragma once
#include "Vektoria\Root.h"

#define switchTime 3000


using namespace Vektoria;

class SkyManager
{
public:
	void init(CScene* tmp_scene, CPlacement* tmp_camera);
	void update(int tmp_score);
private:

	float scoreTime;

	CScene* mySkyScene;
	CPlacement* myCamera;
};

