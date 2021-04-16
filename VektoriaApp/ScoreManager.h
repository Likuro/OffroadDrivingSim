#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;

class ScoreManager
{
public:

	void init(CViewport *tmp_viewport);
	void update(CHVector tmp_pos);
	int getScore();

private:

	int score;
	CWriting scoreOutput;
	CWritingFont scoreFont;
	CHVector lastPos;
};

