#include "Player.h"

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

//==========================================================
Player::Player()
    : pos(0, SCREEN_HEIGHT - PLAYER_HEIGHT)
    , displaySpriteA( true )
    , facingRight( true )
    , yVelocity( 0.0f )
{

}

//==========================================================
void Player::levelStart()
{
    pos.x = 0;
    pos.y = map->getLevelHeight() * TILE_LENGTH - PLAYER_HEIGHT;
}


//==========================================================
void Player::move( Arduboy2 * arduboy )
{
    short newY = pos.y, newX = pos.x;
    bool falling = isFalling();

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
    //handle falling
    else if( falling )
    {
        if(yVelocity < PLAYER_FALL_MAX_VELOCITY)
        {
            yVelocity += PLAYER_Y_VELOCITY_INC;
        }
    }
    else
    {
        if(yVelocity > 1.01f) //TODO cope with high velocity collision in less ugly way
        {
            yVelocity = 1.0f;
        }
        else
        {
            yVelocity = 0;
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
        if( !jumping && !falling && arduboy->pressed( A_BUTTON )) //jump only works when on the ground
        {
            jumping = true;
            yVelocity = -PLAYER_JUMP_VELOCITY;
        }

        //Player animation
        if(animFrameCounter > PLAYER_ANIM_NB_FRAMES)
        {
            displaySpriteA = !displaySpriteA;
            animFrameCounter = 0;
        }
    }

    //if no collision -> apply new position
    if( !map->checkCollision(newX, newY - 1, PLAYER_WIDTH, PLAYER_HEIGHT) )
    {
        pos.x = newX;
        pos.y = newY;
    }

    pos.y += yVelocity; //apply velocity to player position regardless of collision (y collision is already handled)
}

//==========================================================
void Player::draw( Arduboy2 * arduboy )
{
    short screenX = pos.x - map->getScrollX();
    short screenY = pos.y - map->getScrollY(); 

    if(facingRight) //Avoid flags and set bitmap pointer instead?
    {
        if(displaySpriteA)
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
        if(displaySpriteA)
        {
            arduboy->drawBitmap(screenX, screenY, BITMAP_A_LEFT, PLAYER_WIDTH, PLAYER_HEIGHT);
        }
        else
        {
            arduboy->drawBitmap(screenX, screenY, BITMAP_B_LEFT, PLAYER_WIDTH, PLAYER_HEIGHT);
        }
    }

    animFrameCounter++;
}

//==========================================================
void Player::setMap( Map * map )
{
    this->map = map;
}

//==========================================================
bool Player::isFalling() const
{
    short playerY = pos.y + PLAYER_HEIGHT + ( (yVelocity > 1.01f) ? ceil(yVelocity) : 1); //"below" Y depends on yVelocity //TODO find better way to handle it

    return playerY < map->getLevelHeight() * TILE_LENGTH
        && !map->checkCollisionForPoint(pos.x, playerY )
        && !map->checkCollisionForPoint(pos.x + PLAYER_WIDTH, playerY );
}

//==========================================================
bool Player::somethingIsAbove() const
{
    return map->checkCollisionForPoint(pos.x, pos.y) || map->checkCollisionForPoint(pos.x + PLAYER_WIDTH, pos.y);
}