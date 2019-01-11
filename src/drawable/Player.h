#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <Arduboy2.h>

#include "../Constants.h"
#include "../abstract/Drawable.h"
#include "../abstract/Movable.h"
#include "../abstract/Singleton.h"
#include "../EntitiesManager.h"
#include "Map.h"

class Player : public Drawable, public Movable, public Singleton<Player>
{
    public:
        Player();
        void levelStart();

        void move( Arduboy2 * arduboy ) override;
        void draw( Arduboy2 * arduboy ) override;
        void takeHit();

        inline Position & getPos() {return pos; }

        int8 getLife() const;
    private:

        bool isFalling() const;
        bool somethingIsAbove() const;
        bool checkCollisionWithEntities(Position pos); //return true if there is a collision

        int8 life;
        Position pos;

        float yVelocity;
        bool jumping;
        bool beingHit;

        bool displaySpriteA;
        bool facingRight;
        int8 animFrameCounter;
        int8 hitFrameCounter;

};

#endif
