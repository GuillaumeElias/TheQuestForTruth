#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <Arduboy2.h>

#include "Constants.h"
#include "Drawable.h"
#include "Movable.h"
#include "Map.h"

class Player : public Drawable, public Movable
{
    public:
        Player();
        void levelStart();

        void move( Arduboy2 * arduboy ) override;
        void draw( Arduboy2 * arduboy ) override;

        inline Position & getPos() {return pos; }

        void setMap( Map * map );
    private:

        bool isFalling() const;
        bool somethingIsAbove() const;

        Map * map;
        Position pos;
        float yVelocity;
        bool jumping;

        bool displaySpriteA;
        bool facingRight;
        int8 animFrameCounter;

};

#endif
