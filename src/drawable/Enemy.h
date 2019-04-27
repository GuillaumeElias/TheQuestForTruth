#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <Arduboy2.h>

#include "../abstract/Movable.h"
#include "../Constants.h"
#include "Map.h"

class Enemy : public Drawable, public Movable
{
    public:
        Enemy();

        void spawn( const Position & spawnPosition, int8 enemyType);
        TriggerEvent move( Arduboy2 * arduboy ) override;
        void draw( Arduboy2 * arduboy ) override;
        
        const Position & getPos() const;

        bool checkEnemyCollision(const Position & playerPosition, const Position & enemyPosition);
    private:
        short getWidth() const;
        short getHeight() const;

        int8 type;
        Position pos;
        Position initPos;
        
        bool displaySpriteA;
        bool facingRight;
        bool dead;

        int8 animFrameCounter;
        int8 walkFrameSkipped;

};

#endif
