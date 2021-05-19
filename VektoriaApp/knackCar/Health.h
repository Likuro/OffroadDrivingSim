#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;

class Health
{
public:
	Health(int maxHealth, int currentHealth) : m_maxHealth{ maxHealth }, m_currentHealth{ currentHealth }{};

	void clampHealth();

	void setHealth(int value);
	int getHealth();
	int getMaxHealth();

	void dealDamage(int damage);
	void heal(int heal);

	bool isDead();

private:
	int m_currentHealth;
	int m_maxHealth;
};

