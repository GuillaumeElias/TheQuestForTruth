#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

typedef int8_t int8;

struct Position { 
    short x; short y;
    Position( short _x, short _y ) : x(_x) , y(_y) {}
};

struct Rectangle{
    Position pos;
    short width, height;
};

//COLLISION CHECK RESULT
typedef enum __attribute__ ((packed))
{
    FREE,
    HIT_ENEMY,
    HIT_TRIGGER
} CollisionCheckResult;

static const short SCREEN_HEIGHT = 64;
static const short SCREEN_WIDTH = 128;
static const short MID_WIDTH = SCREEN_WIDTH / 2;
static const short MID_HEIGHT = SCREEN_HEIGHT / 2;
static const short PLAYER_HEIGHT = 20;
static const short PLAYER_WIDTH = 9;
static const short PLAYER_LIFE = 5;
static const short PLAYER_ANIM_NB_FRAMES = 30;
static const short PLAYER_HIT_NB_FRAMES = 10;
static const short PLAYER_MOVE = 1;
static const float PLAYER_JUMP_VELOCITY = 2.0f;
static const float PLAYER_Y_VELOCITY_INC = 0.1f;
static const float PLAYER_FALL_MAX_VELOCITY = 2.0f;
static const short TILE_LENGTH = 10;
static const short TILE_SCREEN_Y_OFFSET = SCREEN_HEIGHT % TILE_LENGTH;
static const short MAX_ENEMIES_PER_LEVEL = 5;
static const short ENEMY_MOVE = 1;
static const short ENEMY_WALK_MAX = 40;
static const short ENEMY_WALK_FRAME_SKIP = 2;


#endif
