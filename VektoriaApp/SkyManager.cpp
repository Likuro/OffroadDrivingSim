#include "SkyManager.h"

void SkyManager::init(CScene* tmp_scene, CPlacement* tmp_camera)
{
	myCamera = tmp_camera;
	mySkyScene = tmp_scene;
	mySkyScene->SetSkyOn(myCamera, true);
}

void SkyManager::update(int tmp_score)
{
	//umrechung und convertierung von int score zu float zwischen 0-1
	tmp_score = tmp_score % (switchTime+1);
	scoreTime = tmp_score;
	scoreTime = scoreTime / switchTime;

	mySkyScene->SetSkyTimeOfDay(scoreTime);
}