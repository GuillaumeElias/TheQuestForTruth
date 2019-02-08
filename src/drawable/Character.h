#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <Arduboy2.h>

#include "../abstract/Movable.h"
#include "../Constants.h"
#include "Map.h"

class Character : public Drawable, public Movable
{
    public:
        Character();
        Character(int8 characterId);

        void spawn( const Position & spawnPosition );
        void move( Arduboy2 * arduboy ) override;
        void draw( Arduboy2 * arduboy ) override;
        
        const Position & getPos() const;

        bool checkCharacterCollision(const Position & playerPosition, const Position & enemyPosition);
    private:

        short getWidth() const;
        short getHeight() const;

        Position pos;
        
        int8 id;
        bool displaySpriteA;
        bool facingRight;
        bool visible;

        int8 animFrameCounter;
        int8 walkFrameSkipped;

};

#endif
