#include "Boost.h"

void Boost::clampBoost()
{
	if (m_currentBoost > m_maxBoost)
	{
		m_currentBoost = m_maxBoost;
	}
	else if (m_currentBoost < 0)
	{
		m_currentBoost = 0;
	}
}

void Boost::setBoost(float value)
{
	m_currentBoost = value;
	clampBoost();
}

float Boost::getBoost()
{
	return m_currentBoost;
}

float Boost::getMaxBoost()
{
	return m_maxBoost;
}

void Boost::addBoost(float value)
{
	m_currentBoost += value;
	clampBoost();
}

void Boost::substractBoost(float value)
{
	m_currentBoost -= value;
	clampBoost();
}

bool Boost::isEmpty()
{
	if (m_currentBoost < 0.f)
	{
		return true;
	}
	return false;
}
