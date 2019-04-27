#include "Enemy.h"
#include "../Utils.h"
#include "Player.h"

namespace
{
    static const short ENEMY_1_WIDTH = 10;
    static const short ENEMY_1_HEIGHT = 18;
    static const short ENEMY_2_WIDTH = 12;
    static const short ENEMY_2_HEIGHT = 12;
}

PROGMEM static const byte BITMAP_1[] = {0xfc, 0x06, 0xc3, 0x01, 0x01, 0x01, 0xc3, 0x06, 
  0x1c, 0xe0, 0xff, 0x05, 0x82, 0xa5, 0xd0, 0x55, 
  0xa2, 0x85, 0x00, 0xff, 0x03, 0x01, 0x01, 0x03, 
  0x01, 0x03, 0x01, 0x01, 0x03, 0x01};

PROGMEM static const byte BITMAP_2[] = {0xf0, 0x0c, 0x02, 0x1a, 0x99, 0x81, 0x81, 0x99, 
  0x1a, 0x02, 0x0c, 0xf0, 0x00, 0x03, 0x04, 0x05, 
  0x08, 0x08, 0x08, 0x08, 0x05, 0x04, 0x03, 0x00};

//==========================================================
Enemy::Enemy()
    : pos(0,0)
    , initPos(0,0)
    , displaySpriteA( true )
    , facingRight( true )
    , animFrameCounter( 0 )
    , dead( true )
{

}

//==========================================================
 void Enemy::spawn( const Position & spawnPosition, int8 enemyType )
 {
     type = enemyType;
     pos = spawnPosition;
     initPos = spawnPosition;
     dead = false;
 }

//==========================================================
TriggerEvent Enemy::move( Arduboy2 * arduboy )
{
    if(dead) return NO_EVENT;

    if(walkFrameSkipped > ENEMY_WALK_FRAME_SKIP)
    {
        walkFrameSkipped = 0;
    }
    else
    {
        walkFrameSkipped++;
        return NO_EVENT; //only move every n frames
    }

    int8 diffX = pos.x - initPos.x;
    if(diffX > ENEMY_WALK_MAX || checkEnemyCollision(Player::instance()->getPos(), {pos.x + ENEMY_MOVE, pos.y}))
    {
        facingRight = false;
    }
    else if(diffX < -ENEMY_WALK_MAX || checkEnemyCollision(Player::instance()->getPos(), {pos.x - ENEMY_MOVE, pos.y}))
    {
        facingRight = true;
    }

    if(facingRight)
    {
        pos.x += ENEMY_MOVE; 
    }
    else
    {
        pos.x -= ENEMY_MOVE;
    }

    return NO_EVENT;
}

//==========================================================
void Enemy::draw( Arduboy2 * arduboy )
{
    if(dead) return;

    short screenX = pos.x - Map::instance()->getScrollX();
    short screenY = pos.y - Map::instance()->getScrollY(); 

    switch(type)
    {
        case 1:
            arduboy->drawBitmap(screenX, screenY, BITMAP_1, ENEMY_1_WIDTH, ENEMY_1_HEIGHT);
            break;
        case 2:
            arduboy->drawBitmap(screenX, screenY, BITMAP_2, ENEMY_2_WIDTH, ENEMY_2_HEIGHT);
            break;
    }
    
}

//==========================================================
const Position & Enemy::getPos() const
{
    return pos;
}

//==========================================================
bool Enemy::checkEnemyCollision(const Position & playerPosition, const Position & enemyPosition)
{
    if(rectangleCollision({playerPosition, PLAYER_WIDTH, PLAYER_HEIGHT}, {enemyPosition, getWidth(), getHeight()}))
    {
        Player::instance()->takeHit();
        return true;
    }
    return false;
}

//==========================================================
short Enemy::getWidth() const
{
    switch(type)
    {
        case 1:
            return ENEMY_1_WIDTH;
        case 2:
            return ENEMY_2_WIDTH;
    }
}

//==========================================================
short Enemy::getHeight() const
{
    switch(type)
    {
        case 1:
            return ENEMY_1_HEIGHT;
        case 2:
            return ENEMY_2_HEIGHT;
    }
}
