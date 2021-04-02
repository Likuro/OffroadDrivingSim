#include "HealthItem.h"

HealthItem::HealthItem()
{
	Icon = IconObject.LoadGeo(modelPath, false);
	Transform.AddGeo(Icon);
}

void HealthItem::trigger()
{
}

void HealthItem::update(float fTime, float fTimeDelta)
{
	Transform.RotateYDelta(HALFPI * fTimeDelta);
	Transform.TranslateYDelta(amplitude * sinf(fTime * periode) * fTimeDelta);
}
