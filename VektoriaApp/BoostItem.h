#pragma once
#include "Vektoria\Root.h"
#include "Item.h"

using namespace Vektoria;

class BoostItem :
    public Item
{
public:
    BoostItem();
    void trigger();
    void update(float fTime, float fTimeDelta);
};
