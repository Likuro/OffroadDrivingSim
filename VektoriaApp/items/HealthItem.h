#pragma once
#include "Vektoria\Root.h"
#include "Item.h"

const int HEALING = 20;

using namespace Vektoria;

class HealthItem :
    public Item
{
public:
    HealthItem();
    void trigger(DriveController* car);
    void update(float fTime, float fTimeDelta);
};

