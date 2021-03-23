#include "HealthBar.h"

void HealthBar::changeHealth(float value)
{
	progressValue += value;
	update();
}

bool HealthBar::isAlive()
{
	if (progressValue < 0.01f)
		return false;
	else
		return true;
}
