#include "Character.h"
#include "../Utils.h"
#include "Player.h"

namespace
{
    static const short CHARACTER_WIDTH = 5;
    static const short CHARACTER_HEIGHT = 20;
}

PROGMEM static const byte BITMAP_A[] = {0x87, 0x8f, 0xff, 0x0f, 0x00, 0x13, 0x1e, 0xe1, 
0xff, 0x00, 0x08, 0x07, 0x00, 0x00, 0x0f};

PROGMEM static const byte BITMAP_B[] = {0x80, 0x87, 0xef, 0x1f, 0x0f, 0x0f, 0x00, 0xe9, 
0xff, 0x00, 0x08, 0x07, 0x00, 0x00, 0x0f};

//==========================================================
Character::Character()
    : pos(0,0)
    , displaySpriteA( true )
    , facingRight( true )
    , animFrameCounter( 0 )
    , visible( false )
{

}

//==========================================================
 void Character::spawn( const Position & spawnPosition )
 {
     pos = spawnPosition;
     visible = true;
 }

//==========================================================
void Character::move( Arduboy2 * arduboy )
{
    if(!visible) return;

    //Frame animation
    if(animFrameCounter > PLAYER_ANIM_NB_FRAMES)
    {
        displaySpriteA = !displaySpriteA;
        animFrameCounter = 0;
    }
    animFrameCounter++;
}

//==========================================================
void Character::draw( Arduboy2 * arduboy )
{
    if(!visible) return;

    short screenX = pos.x - Map::instance()->getScrollX();
    short screenY = pos.y - Map::instance()->getScrollY(); 
    
    if(displaySpriteA)
    {
        arduboy->drawBitmap(screenX, screenY, BITMAP_A, CHARACTER_WIDTH, CHARACTER_HEIGHT);
    }
    else
    {
        arduboy->drawBitmap(screenX, screenY, BITMAP_B, CHARACTER_WIDTH, CHARACTER_HEIGHT);
    }
}

//==========================================================
const Position & Character::getPos() const
{
    return pos;
}

//==========================================================
bool Character::checkCharacterCollision(const Position & playerPosition, const Position & CharacterPosition)
{
    return rectangleCollision({playerPosition, PLAYER_WIDTH, PLAYER_HEIGHT}, {CharacterPosition, CHARACTER_WIDTH, CHARACTER_HEIGHT});
}
