#pragma once
#include "ProgressBar.h"

using namespace Vektoria;
class HealthBar : public ProgressBar
{
public:
	HealthBar(CMaterial* mat, CViewport* root, float max, float currentvalue, float xpos, float ypos, float l, float h) : ProgressBar(mat, root, max, currentvalue, xpos, ypos, l, h) {};
	
	void changeHealth(float value);
	bool isAlive();
};

