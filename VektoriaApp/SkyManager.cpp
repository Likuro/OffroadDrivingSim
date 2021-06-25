#include "SkyManager.h"

void SkyManager::init(CScene* tmp_scene, CPlacement* tmp_Pcamera, CCamera* tmp_Ccamera)
{
	mySkyScene = tmp_scene;
	mySkyScene->SetSkyOn(tmp_Pcamera, true);
	//tmp_Ccamera->Init(QUARTERPI, 0.1f, 30000.f, true, mySkyScene->GetSkyLightPlacement());

	mySkyScene->SetSkyShadowResolution(16000, 16000);
	mySkyScene->SetSkyShadowDepth(1000);
	mySkyScene->SetLightAmbient(0.6f);
}

void SkyManager::update(int tmp_score)
{
	//umrechung und convertierung von int score zu float zwischen 0-1
	tmp_score = tmp_score % (switchTime+1);
	scoreTime = tmp_score;
	scoreTime = scoreTime / switchTime;

	mySkyScene->SetSkyTimeOfDay(scoreTime);
	mySkyScene->SetLightAmbient(0.6f);
}