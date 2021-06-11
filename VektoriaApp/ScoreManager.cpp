#include "ScoreManager.h"

void ScoreManager::init(COverlay* tmp_viewport)
{
	score = defaultscore;
	time = 0;
	lastPos = CHVector(0.0f, 0.0f, 0.0f);
	
	scoreFont.LoadPreset("LucidaConsoleRed");
	scoreFont.SetChromaKeyingOn();
	scoreOutput.Init(CFloatRect(0.825f, 0.05f, 0.15f, 0.05f), 10, &scoreFont);
	tmp_viewport->AddWriting(&scoreOutput);

	scoreOutput.PrintInt(score);
}

void ScoreManager::update(CHVector tmp_pos, float tmp_ftime)
{
	time += tmp_ftime;
	if (time >= refreshrate) {
		score += tmp_pos.Dist(lastPos);
		scoreOutput.PrintInt(score);
		lastPos = tmp_pos;
		time = 0;
	}
}

int ScoreManager::getScore()
{
	return score;
}

void ScoreManager::resetScore()
{
	score = defaultscore;
	time = 0;
	lastPos = CHVector(0.0f, 0.0f, 0.0f);

}
