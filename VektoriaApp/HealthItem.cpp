#include "HealthItem.h"


HealthItem::HealthItem()
{
}

void HealthItem::trigger()
{
}

void HealthItem::update(float fTime, float fTimeDelta)
{
	lifeTime += fTimeDelta;
	Transform.RotateYDelta(HALFPI * fTimeDelta);
	Transform.TranslateYDelta(amplitude * sinf(fTime * periode) * fTimeDelta);
}
