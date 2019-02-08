#include "EntitiesManager.h"
#include "DialogManager.h"
#include "Utils.h"

//==========================================================
EntitiesManager::EntitiesManager(Arduboy2 * ardu)
    : arduboy(ardu)  
    , enemies_number(0)
    , character_number(0)
    , trigger_number(0)
    , levelFinished(false)
{
}

//==========================================================
void EntitiesManager::drawEntities() const
{
    for(int8 i=0; i < enemies_number; i++)
    {
        enemies[i].draw( arduboy );
    }

    for(int8 i=0; i < character_number; i++)
    {
        characters[i].draw( arduboy );
    }
}

//==========================================================
void EntitiesManager::moveEntities()
{
    for(int8 i=0; i < enemies_number; i++)
    {
        enemies[i].move( arduboy );
    }

    for(int8 i=0; i < character_number; i++)
    {
        characters[i].move( arduboy );
    }
}

//==========================================================
void EntitiesManager::spawnEntities(Map * map)
{
    for ( short i = 0; i < map->getLevelHeight(); i++ )
    {
        for( short j = 0; j < map->getLevelLength(); j++ )
        {
            levels::Tile tile = levels::getTile(map->getCurrentLevel(), i, j);
            if(tile == levels::Tile::_ENEMY)
            {
                enemies[enemies_number].spawn( { j * TILE_LENGTH, i * TILE_LENGTH } );
                enemies_number++;
            }
            else if(levels::isCharacterTile(tile))
            {
                characters[character_number] = Character(tile);
                characters[character_number].spawn( { j * TILE_LENGTH, i * TILE_LENGTH } );
                character_number++;
            }
            else if(levels::getTileTriggerId(tile) >= 0)
            {
                triggers[trigger_number].pos = { j * TILE_LENGTH, i * TILE_LENGTH };
                triggers[trigger_number].id = levels::getTileTriggerId(tile);
                triggers[trigger_number].triggered = false;
                trigger_number++;
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

//==========================================================
void EntitiesManager::triggerCheckAndExecute(const Position & ppos)
{
    for(int8 i=0; i < trigger_number; i++)
    {
        if(triggers[i].triggered) continue;

        if( rectangleCollision({ppos, PLAYER_WIDTH, PLAYER_HEIGHT}, {triggers[i].pos, TRIGGER_WIDTH, TRIGGER_HEIGHT}) )
        {
            switch(triggers[i].id)
            {
                case 1:
                    DialogManager::instance()->printTextForTrigger(&triggers[i]);
                    triggers[i].triggered = true;
                    break;
                case 2:
                    DialogManager::instance()->printTextForTrigger(&triggers[i]);
                    triggers[i].triggered = true;
                    break;
                case 19:
                    levelFinished = true;
                    break;
            }
        }
    }
 
}

//==========================================================
bool EntitiesManager::isLevelFinished() const
{
    return levelFinished;
}

//==========================================================
void EntitiesManager::startNewLevel()
{
    clearEntities();
    spawnEntities(Map::instance());
    levelFinished = false;
}

//==========================================================
void EntitiesManager::clearEntities()
{
    for(short i=0; i < enemies_number; i++)
    {
        enemies[i] = Enemy();
    }
    for(short i=0; i < character_number; i++)
    {
        characters[i] = Character();
    }
    for(short i=0; i < trigger_number; i++)
    {
        triggers[i] = Trigger();
    }
}
