#pragma once
#include "Vektoria\Root.h"
#include "Item.h"

using namespace Vektoria;

class HealthItem :
    public Item
{
public:
    HealthItem();
    void trigger();
    void update(float fTime, float fTimeDelta);
};

