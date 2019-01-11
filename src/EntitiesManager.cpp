#include "EntitiesManager.h"

//==========================================================
EntitiesManager::EntitiesManager(Arduboy2 * ardu)
    : arduboy(ardu)  
    , enemies_number(0)
{
}

//==========================================================
void EntitiesManager::drawEnemies() const
{
    for(short i=0; i < enemies_number; i++)
    {
        enemies[i].draw( arduboy );
    }
}

//==========================================================
void EntitiesManager::moveEnemies()
{
    for(short i=0; i < enemies_number; i++)
    {
        enemies[i].move( arduboy );
    }
}

//==========================================================
void EntitiesManager::spawnEnemies(Map * map)
{
    for ( short i = 0; i < map->getLevelHeight(); i++ )
    {
        for( short j = 0; j < map->getLevelLength(); j++ )
        {
            levels::Tile tile = levels::getTile(map->getCurrentLevel(), i, j);
            if(tile == levels::Tile::_ENEMY)
            {
                enemies[enemies_number].setMap(map);
                enemies[enemies_number].spawn( { j * TILE_LENGTH, i * TILE_LENGTH } );
                enemies_number++;
            }
        }
    }
}

//==========================================================
const CollisionCheckResult EntitiesManager::collisionCheck(const Position & ppos) const
{
    for(short i=0; i < enemies_number; i++)
    {
        if(Enemy::checkEnemyCollision(enemies[i].getPos(), ppos))
        {
            return HIT_ENEMY;
        }
    }

    return FREE;
}
