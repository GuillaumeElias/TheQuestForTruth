#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <Arduboy2.h>

#include "Movable.h"
#include "Constants.h"
#include "Map.h"

class Enemy : public Drawable, public Movable
{
    public:
        Enemy();

        void spawn( const Position & spawnPosition );
        void move( Arduboy2 * arduboy ) override;
        void draw( Arduboy2 * arduboy ) override;
        void setMap(Map * mp);
        
        const Position & getPos() const;

        static void setHitTaker(HitTaker * hitTaker);
        static bool checkEnemyCollision(const Position & playerPosition, const Position & enemyPosition);
    private:
        Position pos;
        Position initPos;
        
        Map * map;

        bool displaySpriteA;
        bool facingRight;
        bool dead;

        int8 animFrameCounter;
        int8 walkFrameSkipped;

        static HitTaker * Hit_Taker;

};

#endif
