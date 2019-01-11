#ifndef _UTILS_H_
#define _UTILS_H_

#include "Constants.h"

//==========================================================
bool rectangleCollision(const Rectangle & rectA, const Rectangle & rectB)
{
    return rectA.pos.x                < rectB.pos.x + rectB.width 
        && rectA.pos.x + rectA.width  > rectB.pos.x 
        && rectA.pos.y                < rectB.pos.y + rectB.height
        && rectA.pos.y + rectA.height > rectB.pos.y;
}

#endif
