#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <Arduboy2.h>

#include "../Constants.h"
#include "../abstract/Drawable.h"
#include "../abstract/Movable.h"
#include "../EntitiesManager.h"
#include "Map.h"

class Player : public Drawable, public Movable, public HitTaker
{
    public:
        Player();
        void levelStart();

        void move( Arduboy2 * arduboy ) override;
        void draw( Arduboy2 * arduboy ) override;
        void takeHit() override;

        inline Position & getPos() {return pos; }

        void setMap( Map * map );
        void setEntitiesManager( EntitiesManager * entitiesManager );
        int8 getLife() const;
    private:

        bool isFalling() const;
        bool somethingIsAbove() const;
        bool checkCollisionWithEntities(Position pos); //return true if there is a collision

        int8 life;
        Position pos;

        Map * map;
        EntitiesManager * entitiesManager;
        float yVelocity;
        bool jumping;
        bool beingHit;

        bool displaySpriteA;
        bool facingRight;
        int8 animFrameCounter;
        int8 hitFrameCounter;

};

#endif
