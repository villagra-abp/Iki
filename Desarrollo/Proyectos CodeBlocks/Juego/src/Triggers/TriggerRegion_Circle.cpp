#include "TriggerRegion_Circle.h"

TriggerRegion_Circle::TriggerRegion_Circle(Structs::TPosicion pos, double rad)
{
    center = pos;
    radius = rad;
}

TriggerRegion_Circle::~TriggerRegion_Circle()
{
    //dtor
}

bool TriggerRegion_Circle::isTouching(Structs::TPosicion EntityPos, double EntityRadius)
{
    //distances calculated in squared-distance space
    //return Vec2DDistanceSq(m_vPos, pos) <
    //(EntityRadius + m_dRadius)*(EntityRadius + m_dRadius)
    return false;
}