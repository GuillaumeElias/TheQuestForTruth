#include "Player.h"
#include "../ItemsManager.h"
#include "../SoundManager.h"

PROGMEM static const byte BITMAP_A_RIGHT[] = {0x1c, 0x22, 0xc1, 0xe1, 0x92, 0x9c, 0x80, 0x80, 
  0x80, 0x00, 0x00, 0xff, 0x01, 0x02, 0x04, 0x08, 
  0x10, 0x00, 0x0c, 0x03, 0x00, 0x01, 0x02, 0x04, 
  0x08, 0x00, 0x00};

PROGMEM static const byte BITMAP_B_RIGHT[] = {0x1c, 0x22, 0xc1, 0xe1, 0x92, 0x5c, 0x40, 0x20, 
  0x20, 0x00, 0x00, 0xff, 0x00, 0x01, 0x01, 0x02, 
  0x02, 0x04, 0x0c, 0x03, 0x00, 0x01, 0x01, 0x02, 
  0x02, 0x04, 0x04};

PROGMEM static const byte BITMAP_A_LEFT[] = {0x80, 0x80, 0x80, 0x9c, 0x92, 0xe1, 0xc1, 0x22, 
  0x1c, 0x00, 0x10, 0x08, 0x04, 0x02, 0x01, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x08, 0x04, 0x02, 0x01, 
  0x00, 0x03, 0x0c};

PROGMEM static const byte BITMAP_B_LEFT[] = {0x20, 0x20, 0x40, 0x5c, 0x92, 0xe1, 0xc1, 0x22, 
  0x1c, 0x04, 0x02, 0x02, 0x01, 0x01, 0x00, 0xff, 
  0x00, 0x00, 0x04, 0x04, 0x02, 0x02, 0x01, 0x01, 
  0x00, 0x03, 0x0c};

PROGMEM static const byte BITMAP_FIRING_1_RIGHT[] PROGMEM = { 0x1c, 0x22, 0xc1, 0xe1, 0x92, 0xcc, 0x60, 0xe0, 
  0x20, 0x00, 0x00, 0xff, 0x02, 0x04, 0x0f, 0x08, 
  0x0f, 0x00, 0x0c, 0x03, 0x00, 0x01, 0x01, 0x02, 
  0x02, 0x04, 0x04};

PROGMEM static const byte BITMAP_FIRING_1_LEFT[] PROGMEM = { 0x20, 0xe0, 0x60, 0xcc, 0x92, 0xe1, 0xc1, 0x22, 
  0x1c, 0x00, 0x0f, 0x08, 0x0f, 0x04, 0x02, 0xff, 
  0x00, 0x00, 0x04, 0x04, 0x02, 0x02, 0x01, 0x01, 
  0x00, 0x03, 0x0c };

//==========================================================
Player::Player()
    : pos(0, 0)
    , life(PLAYER_LIFE)
    , displaySpriteA( true )
    , facingRight( true )
    , yVelocity( 0.0f )
    , animFrameCounter(0)
    , hitFrameCounter(0)
{
}

//==========================================================
void Player::levelStart()
{
    pos.x = 0;
    pos.y = LEVEL_HEIGHT * TILE_LENGTH - PLAYER_HEIGHT - 1;
}


//==========================================================
TriggerEvent Player::move( Arduboy2 * arduboy )
{
    short newY = pos.y, newX = pos.x;
    bool falling = fall();

    //handle jump
    if(jumping)
    {
        yVelocity += PLAYER_Y_VELOCITY_INC;
        if(yVelocity >= 0 )   //reached jump peak or there is something above player
        {
            jumping = false;
            yVelocity = 0.0f;
        }
        else if( somethingIsAbove() )
        {
            jumping = false;
            yVelocity = -yVelocity;
        }
    }

    //Check buttons
    if( arduboy->buttonsState()	!= 0 )
    {
        if( arduboy->pressed( RIGHT_BUTTON ) )
        {
            facingRight = true;
            newX += PLAYER_MOVE;
        }
        else if( arduboy->pressed(LEFT_BUTTON) )
        {
            facingRight = false;
            newX -= PLAYER_MOVE;
        }
        if( !jumping && !falling && arduboy->justPressed( A_BUTTON )) //jump only works when on the ground
        {
            jumping = true;
            yVelocity = -PLAYER_JUMP_VELOCITY;
            SoundManager::instance()->startNoteBurst();
        }
        else if(arduboy->pressed( B_BUTTON ) && ItemsManager::instance()->hasItem(1))
        {
            fire();
            SoundManager::instance()->playSound(PLAYER_FIRE);
        }

        //Player animation
        if(animFrameCounter > PLAYER_ANIM_NB_FRAMES)
        {
            displaySpriteA = !displaySpriteA;
            animFrameCounter = 0;
        }
    }

    //if no collision -> apply new position
    if( !checkCollisionWithMap(newX, newY - 1) && !checkCollisionWithEntities({newX, newY}))
    {
        pos.x = newX;
        pos.y = newY;
    }

    pos.y += yVelocity; //apply velocity to player position regardless of collision (y collision is already handled)

    EntitiesManager::instance()->triggerCheckAndExecute(pos);

    return NO_EVENT;
}

//==========================================================
void Player::draw( Arduboy2 * arduboy )
{
    short screenX = pos.x - Map::instance()->getScrollX();
    short screenY = pos.y - Map::instance()->getScrollY(); 

    if(facingRight) //Avoid flags and set bitmap pointer instead?
    {
        if(firing)
        {
            arduboy->drawBitmap(screenX, screenY, BITMAP_FIRING_1_RIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
        }
        else if(displaySpriteA)
        {
            arduboy->drawBitmap(screenX, screenY, BITMAP_A_RIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
        }
        else
        {
            arduboy->drawBitmap(screenX, screenY, BITMAP_B_RIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
        }
    }
    else
    {
        if(firing)
        {
            arduboy->drawBitmap(screenX, screenY, BITMAP_FIRING_1_LEFT, PLAYER_WIDTH, PLAYER_HEIGHT);
        }
        else if(displaySpriteA)
        {
            arduboy->drawBitmap(screenX, screenY, BITMAP_A_LEFT, PLAYER_WIDTH, PLAYER_HEIGHT);
        }
        else
        {
            arduboy->drawBitmap(screenX, screenY, BITMAP_B_LEFT, PLAYER_WIDTH, PLAYER_HEIGHT);
        }
    }

    animFrameCounter++;

    if(beingHit)
    {
        if(hitFrameCounter > PLAYER_HIT_NB_FRAMES)
        {
            beingHit = false;
            hitFrameCounter = 0;
        }
        else
        {
            ++hitFrameCounter;
            if(hitFrameCounter < 2)
            {
                arduboy->invert(true);
            }
            else
            {
                arduboy->invert(false);
            }
        }
    } 

    if(firing)
    {
        drawMuzzleSparkles(arduboy);
    }

    firing = false;
}

//==========================================================
void Player::takeHit()
{
    if(!beingHit)
    {
        SoundManager::instance()->playSound(Sound::PLAYER_HIT);
        beingHit = true;
        life--;
    }
}

//==========================================================
int8 Player::getLife() const
{
    return life;
}

//==========================================================
void Player::setLife(int8 life)
{
    this->life = life;
}

//==========================================================
bool Player::fall()
{
    if(yVelocity < 0) return false; //don't apply gravity if the player is jumping (which is not really how it works in the real world, I know)

    short extraY = (yVelocity > 1.01f) ? ceil(yVelocity) : 1; //"below" Y depends on yVelocity //TODO find better way to handle it

    bool falling;
    /*do
    {
        extraY--;*/
        falling = !somethingIsBelow(extraY);
    /*}while(falling && extraY >= 1);*/

    if(falling)
    {
        if(yVelocity < PLAYER_FALL_MAX_VELOCITY)
        {
            yVelocity += PLAYER_Y_VELOCITY_INC;
        }
    }
    else
    {
        if(yVelocity > 1.01f)
        {
            yVelocity = 1.0f;
        }
        else
        {
            yVelocity = 0;
        }
    }


    return falling;
}

//==========================================================
bool Player::checkCollisionWithMap(const short & playerX, const short & playerY) const
{
    for(int x=playerX; x <= playerX + PLAYER_WIDTH; x+=3)
    {
        for(int y=playerY; y <= playerY + PLAYER_HEIGHT; y+=2)
        {
            if(Map::instance()->checkCollisionForPoint(x, y))
            {
                return true;
            }
        }
    }
    return false;
}

//==========================================================
bool Player::somethingIsBelow(const short & extraY)
{
    return pos.y + PLAYER_HEIGHT + extraY >= LEVEL_HEIGHT * TILE_LENGTH
        || checkCollisionWithMap(pos.x, pos.y + extraY)
        || checkCollisionWithEntities({pos.x, pos.y + extraY});
}

//==========================================================
bool Player::somethingIsAbove()
{
    return checkCollisionWithMap(pos.x, pos.y) || checkCollisionWithEntities(pos);
}

//===========================================================
bool Player::checkCollisionWithEntities(const Position & position)
{
    const CollisionCheckResult result = EntitiesManager::instance()->collisionCheck(position);
    if(result == HIT_ENEMY)
    {
        takeHit();
        return true;
    }
    return result != FREE;
}

//===========================================================
void Player::fire()
{
    firing = true;

    Position checkPos = pos;
    if(facingRight)
    {
        checkPos.x += PLAYER_WIDTH;
    }
    else
    {
        checkPos.x -= PLAYER_WIDTH;
    }
    
    EntitiesManager::instance()->fireCollisionCheck(checkPos, PEPPER_SPRAY_RANGE_X, PEPPER_SPRAY_RANGE_Y, HitType::PEPPER_SPRAY);
}

//===========================================================
void Player::drawMuzzleSparkles(Arduboy2 * arduboy)
{
    short screenX = pos.x - Map::instance()->getScrollX();
    short screenY = pos.y - Map::instance()->getScrollY() + TILE_LENGTH / 2;

    if(facingRight)
    {
        screenX += PLAYER_WIDTH;
    }
    else
    {
        screenX -= PLAYER_WIDTH;
    }

    for(int i=0; i<10; i++)
    {
        short randX = random(0, TILE_LENGTH);
        short randY = random(0, TILE_LENGTH);
        short fx = randX;

        if(!facingRight) fx = TILE_LENGTH - randX;

        if(randY <= fx) //making a triangle filtering points using: y < f(x)
        {
            arduboy->drawPixel(screenX + randX, screenY + randY);
            arduboy->drawPixel(screenX + randX, screenY - randY);
        }   
    }

    firing = false;
}