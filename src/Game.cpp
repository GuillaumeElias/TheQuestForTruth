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
    entitiesManager.spawnEntities( &map );
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
    entitiesManager.moveEntities();

    //draw objects
    map.draw( &arduboy );
    player.draw( &arduboy );
    entitiesManager.drawEntities();
    dialogManager.draw( &arduboy );

    arduboy.display();
}
