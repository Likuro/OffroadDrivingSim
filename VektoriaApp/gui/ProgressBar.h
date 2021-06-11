#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;
class ProgressBar
{
public: 
	ProgressBar(CMaterial* mat, COverlay* root, float max, float currentvalue, float xpos, float ypos, float l, float h);
	void update(float progressValue);

private:
	float m_progressValue;
	float m_progressMax;
	float m_progressPercent;
	float m_posx;
	float m_posy;
	float m_height;
	float m_length;
	COverlay m_bar;
	CFloatRect m_rect;
	CMaterial* m_barMaterial;
};

