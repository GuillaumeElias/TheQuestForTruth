#include "Game.h"

//==========================================================
Game::Game()
    : map( player.getPos() )
    , entitiesManager( &arduboy )
{
    
}

//==========================================================
void Game::init()
{
    arduboy.begin();
    arduboy.clear();

    map.startLevel();
    player.levelStart();
    entitiesManager.spawnEnemies( &map );
}

//==========================================================
void Game::update()
{
    if (!arduboy.nextFrame())
        return;

    arduboy.clear();
    arduboy.print(player.getLife());

    //move objects
    player.move( &arduboy );
    entitiesManager.moveEnemies();

    //draw objects
    map.draw( &arduboy );
    player.draw( &arduboy );
    entitiesManager.drawEnemies();

    arduboy.display();
}
