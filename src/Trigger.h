#ifndef _TRIGGER_H_
#define _TRIGGER_H_

#include "Constants.h"

struct Trigger
{
    Trigger()
        : id(0)
        , pos(0,0)
        , triggered(true)
    {}
    int8 id;
    Position pos;
    bool triggered;
};

#endif
