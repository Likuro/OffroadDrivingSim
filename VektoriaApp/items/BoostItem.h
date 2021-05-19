#pragma once
#include "Vektoria\Root.h"
#include "Item.h"

const float BOOSTRESTORE = 20.f;

using namespace Vektoria;

class BoostItem :
    public Item
{
public:
    BoostItem();
    void trigger(DriveController* car);
    void update(float fTime, float fTimeDelta);
};
