#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;
class ProgressBar
{
public: 
	ProgressBar(CMaterial* mat, CViewport* root, float max, float currentvalue, float xpos, float ypos, float l, float h);
	void update();


	float progressValue;
	float progressMax;
	float progressPercent;
	float posx;
	float posy;
	float height;
	float length;
	COverlay bar;
	CFloatRect rect;
	CMaterial* barMaterial;
};

