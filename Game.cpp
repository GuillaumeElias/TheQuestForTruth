#include "Game.h"

//==========================================================
Game::Game()
	: map( player.getPos() )
    , enemies_number(0)
{
}

//==========================================================
void Game::init()
{
	arduboy.begin();
	arduboy.clear();

	player.setMap( &map );
	map.startLevel();
	player.levelStart();
    spawnEnemies();
}

//==========================================================
void Game::update()
{
	if (!arduboy.nextFrame())
		return;

	arduboy.clear();
	//arduboy.print("=The quest for truth=");

	//move objects
	player.move( &arduboy );

	//draw objects
	map.draw( &arduboy );
	player.draw( &arduboy );
    drawEnemies();

    arduboy.display();
}


//==========================================================
void Game::drawEnemies() const
{
    for(short i=0; i < enemies_number; i++)
    {
        enemies[i].draw( &arduboy );
    }
}

//==========================================================
void Game::moveEnemies()
{
    for(short i=0; i < enemies_number; i++)
    {
        enemies[i].move( &arduboy );
    }
}

//==========================================================
void Game::spawnEnemies()
{
    for ( short i = 0; i < map.getLevelHeight(); i++ )
    {
        for( short j = 0; j < map.getLevelLength(); j++ )
        {
            levels::Tile tile = levels::getTile(map.getCurrentLevel(), i, j);
            if(tile == levels::Tile::_ENEMY)
            {
                enemies[enemies_number].setMap(&map);
                enemies[enemies_number].spawn( { j * TILE_LENGTH, i * TILE_LENGTH } );
                enemies_number++;
            }
        }
    }
}
