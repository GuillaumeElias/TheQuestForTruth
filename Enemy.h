#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <Arduboy2.h>

#include "Constants.h"
#include "Player.h"
#include "Map.h"

class Enemy : public Drawable, public Movable
{
    public:
        Enemy();

        void spawn( const Position & spawnPosition );
        void move( Arduboy2 * arduboy ) override;
        void draw( Arduboy2 * arduboy ) override;
        void setMap(Map * mp);
    private:
        Position pos;
        Map * map;

        bool displaySpriteA;
        bool facingRight;
        bool dead;

        int8 animFrameCounter;

};

#endif
