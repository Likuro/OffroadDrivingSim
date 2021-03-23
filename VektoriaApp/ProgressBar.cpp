#include "ProgressBar.h"

float clampValue(float value, float min, float max)
{
	if (value > max)
		value = max;
	if (value < min)
		value = min;
	return value;
}

ProgressBar::ProgressBar(CMaterial * mat, CViewport * root, float max, float currentvalue, float xpos, float ypos, float l, float h)
{
	barMaterial = mat;
	posx = xpos;
	posy = ypos;
	height = h;
	length = l;
	progressMax = max;
	progressValue = currentvalue;

	update();
	root->AddOverlay(&bar);
}

void ProgressBar::update()
{
	// Länge wird geupdatet

	// Verhindern, dass Health unter 0 gehen
	progressValue = clampValue(progressValue, 0.f, progressMax);
	progressPercent = progressValue / progressMax;
	rect.Init(posx, posy, length * progressPercent, height);
	bar.Init(barMaterial, rect);
}
