#ifndef _MOVABLE_H_
#define _MOVABLE_H_

#include "../Constants.h"

/** Interface for all movable objects */
class Movable
{
    public:
        virtual TriggerEvent move( Arduboy2 * arduboy ) = 0;
};

#endif