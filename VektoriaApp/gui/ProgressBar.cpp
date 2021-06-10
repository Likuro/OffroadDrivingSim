#include "ProgressBar.h"

ProgressBar::ProgressBar(CMaterial * mat, COverlay* root, float max, float currentvalue, float xpos, float ypos, float l, float h)
{
	m_barMaterial = mat;
	m_posx = xpos;
	m_posy = ypos;
	m_height = h;
	m_length = l;
	m_progressMax = max;
	m_progressValue = currentvalue;

	update(m_progressValue);
	root->AddOverlay(&m_bar);
}

void ProgressBar::update(float progressValue)
{
	// Länge wird geupdatet
	m_progressValue = progressValue;
	m_progressPercent = m_progressValue / m_progressMax;
	m_rect.Init(m_posx, m_posy, m_length * m_progressPercent, m_height);
	m_bar.Init(m_barMaterial, m_rect);
}
