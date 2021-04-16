#include "ScoreManager.h"

void ScoreManager::init(CViewport *tmp_viewport)
{
	score = 0;
	lastPos = CHVector(0.0f, 0.0f, 0.0f);
	
	scoreFont.LoadPreset("LucidaConsoleRed");
	scoreFont.SetChromaKeyingOn();
	scoreOutput.Init(CFloatRect(0.825f, 0.05f, 0.15f, 0.05f), 10, &scoreFont);
	tmp_viewport->AddWriting(&scoreOutput);

	scoreOutput.PrintInt(score);
}

void ScoreManager::update(CHVector tmp_pos)
{
	//score += tmp_pos.Dist(lastPos);
	if (score < (tmp_pos.Dist(CHVector(0.0f, 0.0f, 0.0f)))) {
		score = tmp_pos.Dist(CHVector(0.0f, 0.0f, 0.0f));
	}
	scoreOutput.PrintInt(score);
	lastPos = tmp_pos;
}

int ScoreManager::getScore()
{
	return score;
}
