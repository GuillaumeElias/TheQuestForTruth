#include "Enemy.h"

namespace
{
    static const short ENEMY_WIDTH = 10;
    static const short ENEMY_HEIGHT = 18;
}

PROGMEM static const byte BITMAP_A[] = {0xfc, 0x06, 0xc3, 0x01, 0x01, 0x01, 0xc3, 0x06, 
  0x1c, 0xe0, 0xff, 0x05, 0x82, 0xa5, 0xd0, 0x55, 
  0xa2, 0x85, 0x00, 0xff, 0x03, 0x01, 0x01, 0x03, 
  0x01, 0x03, 0x01, 0x01, 0x03, 0x01};

//==========================================================
Enemy::Enemy()
    : pos(0,0)
    , displaySpriteA( true )
    , facingRight( true )
    , animFrameCounter( 0 )
    , dead( true )
{

}

//==========================================================
 void Enemy::spawn( const Position & spawnPosition )
 {
     pos = spawnPosition;
 }

//==========================================================
void Enemy::move( Arduboy2 * arduboy )
{

}

//==========================================================
void Enemy::draw( Arduboy2 * arduboy )
{
    short screenX = pos.x - map->getScrollX();
    short screenY = pos.y - map->getScrollY(); 
    
    arduboy->drawBitmap(screenX, screenY, BITMAP_A, ENEMY_WIDTH, ENEMY_HEIGHT);
}

//==========================================================
void Enemy::setMap(Map * mp)
{
    this->map = mp;
}
