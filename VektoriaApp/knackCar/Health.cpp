#include "Health.h"
void Health::clampHealth()
{
	if (m_currentHealth > m_maxHealth)
	{
		m_currentHealth = m_maxHealth;
	}
	else if (m_currentHealth < 0)
	{
		m_currentHealth = 0;
	}
}

void Health::setHealth(int value)
{
	m_currentHealth = value;
	clampHealth();
}

int Health::getHealth()
{
	return m_currentHealth;
}

int Health::getMaxHealth()
{
	return m_maxHealth;
}

void Health::dealDamage(int damage)
{
	m_currentHealth -= damage;
	clampHealth();
}

void Health::heal(int heal)
{
	m_currentHealth += heal;
	clampHealth();
}

bool Health::isDead()
{
	if (m_currentHealth == 0)
		return true;

	return false;
}
