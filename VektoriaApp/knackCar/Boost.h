#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;

class Boost
{
public:
	Boost(float maxBoost, float currentBoost) : m_maxBoost{ maxBoost }, m_currentBoost{ currentBoost } {};

	void clampBoost();
	void setBoost(float value);
	float getBoost();
	float getMaxBoost();

	void addBoost(float value);
	void substractBoost(float value);

	bool isEmpty();
private:
	float m_currentBoost;
	float m_maxBoost;
};

