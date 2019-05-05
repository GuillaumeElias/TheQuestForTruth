#include "Enemy.h"
#include "../Utils.h"
#include "Player.h"

namespace
{
    static const short ENEMY_1_WIDTH = 10;
    static const short ENEMY_1_HEIGHT = 18;
    static const short ENEMY_2_WIDTH = 12;
    static const short ENEMY_2_HEIGHT = 12;
    static const short PARALYSED_TICKS = 500;
    static const short FOLLOW_PLAYER_DISTANCE = TILE_LENGTH * 5;
    static const short ENEMY_DEATH_TICKS = 21;
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
    , life(0)
    , displaySpriteA( true )
    , facingRight( true )
    , animFrameCounter( 0 )
    , paralysedCounter( 0 )
{

}

//==========================================================
 void Enemy::spawn( const Position & spawnPosition, int8 enemyType )
 {
     type = enemyType;
     pos = spawnPosition;
     initPos = spawnPosition;

     switch(type)
     {
        case 1:
            life = 1;
            break;
        case 2:
            life = 10;
            break;
     }
 }

//==========================================================
TriggerEvent Enemy::move( Arduboy2 * arduboy )
{
    if(life <= 0) return NO_EVENT;

    if(paralysedCounter != 0)
    { 
        shakeEnemyForParalysis();
        return;
    }

    if(walkFrameSkipped > ENEMY_WALK_FRAME_SKIP)
    {
        walkFrameSkipped = 0;
    }
    else
    {
        walkFrameSkipped++;
        return NO_EVENT; //only move every n frames
    }

    short distancePlayerX = Player::instance()->getPos().x - pos.x;

    if(type == 2 && abs(distancePlayerX) < FOLLOW_PLAYER_DISTANCE) //PLAYER IS NEARBY
    {
        if(checkEnemyCollision(Player::instance()->getPos(), {pos.x, pos.y}, true))
        {
            life = -ENEMY_DEATH_TICKS;
            return NO_EVENT;
        }

        short dx = distancePlayerX;
        short dy = Player::instance()->getPos().y - pos.y;
        float norm = sqrt(dx * dx + dy * dy); //normalise vector
        if (norm)
        {
            dx *= ENEMY_FOLLOW_MOVE / norm;
            dy *= ENEMY_FOLLOW_MOVE / norm;
        }

        short newPosX = pos.x + dx;
        short newPosY = pos.y + dy;
        
        if(!Map::instance()->checkCollision(newPosX, newPosY, getWidth(), getHeight() ) )
        {
            pos.x = newPosX;
            pos.y = newPosY;
        }
    }
    else //NORMAL PATROL MOVE
    {
        int8 diffX = pos.x - initPos.x;
        if(diffX > ENEMY_WALK_MAX || checkEnemyCollision(Player::instance()->getPos(), {pos.x + ENEMY_MOVE, pos.y}, true))
        {
            facingRight = false;
        }
        else if(diffX < -ENEMY_WALK_MAX || checkEnemyCollision(Player::instance()->getPos(), {pos.x - ENEMY_MOVE, pos.y}, true))
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
    
    return NO_EVENT;
}

//==========================================================
void Enemy::draw( Arduboy2 * arduboy )
{
    if(life == 0) return;

    short screenX = pos.x - Map::instance()->getScrollX();
    short screenY = pos.y - Map::instance()->getScrollY(); 

    if(life < 0)
    {
        arduboy->drawCircle(screenX + getWidth() / 2, screenY + getHeight() / 2, abs(life / 3));
        life++;
        return;
    }

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
bool Enemy::checkEnemyCollision(const Position & enemyPosition, const Position & playerPosition, bool damageOn)
{
    //TODO redo that more accurately
    if(life > 0 && rectangleCollision({playerPosition, PLAYER_WIDTH, PLAYER_HEIGHT}, {enemyPosition, getWidth(), getHeight()}))
    {
        if(damageOn)
        {
            Player::instance()->takeHit();
        }
        return true;
    }
    return false;
}

//==========================================================
void Enemy::onHit( const HitType & type )
{
    if(type == HitType::PEPPER_SPRAY && paralysedCounter == 0)
    {
        paralysedCounter = PARALYSED_TICKS;
    }
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

//==========================================================
bool Enemy::isAlive() const
{
    return life > 0;
}

//==========================================================
void Enemy::shakeEnemyForParalysis()
{
    if(paralysedCounter > 0)
    {
        if(paralysedCounter % 2)
        {
            pos.y--;
        }
        else if(pos.y + getHeight() < Map::instance()->getLevelHeight() * TILE_LENGTH)
        {
            pos.y++;
        }
    
        paralysedCounter--;
    }
}