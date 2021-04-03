#include "BoostItem.h"

BoostItem::BoostItem()
{
}

void BoostItem::trigger()
{
}

void BoostItem::update(float fTime, float fTimeDelta)
{
	lifeTime += fTimeDelta;
	Transform.RotateYDelta(HALFPI * fTimeDelta);
	Transform.TranslateYDelta(amplitude * sinf(fTime * periode) * fTimeDelta);
}
