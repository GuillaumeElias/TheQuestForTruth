#include "Enemy.h"
#include "../Utils.h"
#include "Player.h"

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
    , initPos(0,0)
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
     initPos = spawnPosition;
     dead = false;
 }

//==========================================================
void Enemy::move( Arduboy2 * arduboy )
{
    if(dead) return;

    if(walkFrameSkipped > ENEMY_WALK_FRAME_SKIP)
    {
        walkFrameSkipped = 0;
    }
    else
    {
        walkFrameSkipped++;
        return; //only move every n frames
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
}

//==========================================================
void Enemy::draw( Arduboy2 * arduboy )
{
    if(dead) return;

    short screenX = pos.x - Map::instance()->getScrollX();
    short screenY = pos.y - Map::instance()->getScrollY(); 
    
    arduboy->drawBitmap(screenX, screenY, BITMAP_A, ENEMY_WIDTH, ENEMY_HEIGHT);
}

//==========================================================
const Position & Enemy::getPos() const
{
    return pos;
}

//==========================================================
bool Enemy::checkEnemyCollision(const Position & playerPosition, const Position & enemyPosition)
{
    if(rectangleCollision({playerPosition, PLAYER_WIDTH, PLAYER_HEIGHT}, {enemyPosition, ENEMY_WIDTH, ENEMY_HEIGHT}))
    {
        Player::instance()->takeHit();
        return true;
    }
    return false;
}
