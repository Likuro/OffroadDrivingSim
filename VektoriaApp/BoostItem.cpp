#include "BoostItem.h"

BoostItem::BoostItem()
{
	Icon = IconObject.LoadGeo(modelPath, false);
	Transform.AddGeo(Icon);
}

void BoostItem::trigger()
{
}

void BoostItem::update(float fTime, float fTimeDelta)
{
	Transform.RotateYDelta(HALFPI * fTimeDelta);
	Transform.TranslateYDelta(amplitude * sinf(fTime * periode) * fTimeDelta);
}
