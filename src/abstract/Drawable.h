#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

//Forward declarations
class Arduboy2;

/** Interface for all drawable objects */
class Drawable
{
    public:
        virtual void draw( Arduboy2 * arduboy) = 0;
};

#endif