#pragma once
#include "Vektoria\Root.h"

#define refreshrate 0.1

using namespace Vektoria;

class ScoreManager
{
public:

	void init(CViewport *tmp_viewport);
	void update(CHVector tmp_pos, float tmp_ftime);
	int getScore();
	void resetScore();

private:

	int score;
	float time;
	CWriting scoreOutput;
	CWritingFont scoreFont;
	CHVector lastPos;
};
