#include "EntitiesManager.h"
#include "DialogManager.h"
#include "ItemsManager.h"
#include "Utils.h"

//==========================================================
EntitiesManager::EntitiesManager(Arduboy2 * ardu)
    : arduboy(ardu)  
    , enemies_number(0)
    , character_number(0)
    , trigger_number(0)
    , triggerEvent(NO_EVENT)
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

    if(itemToBePickedUp.isPresent())
    {
        itemToBePickedUp.draw( arduboy );
    }
}

//==========================================================
void EntitiesManager::moveEntities()   //we assume there will only be one event triggered per call
{
    TriggerEvent generatedEvent = NO_EVENT;
    for(int8 i=0; i < enemies_number; i++)
    {
        generatedEvent = enemies[i].move( arduboy );
    }

    for(int8 i=0; i < character_number; i++)
    {
        generatedEvent = characters[i].move( arduboy );
    }

    if(generatedEvent != NO_EVENT)
    {
        triggerEvent = generatedEvent;
    }
}

//==========================================================
void EntitiesManager::spawnEntities(Map * map)
{
    /*for ( short i = 0; i < map->getLevelHeight(); i++ )  //TODO parse level more efficienly
    {
        for( short j = 0; j < map->getLevelLength(); j++ )
        {
            levels::Tile tile = levels::getTile(map->getCurrentLevel(), i, j);
            if(levels::getTileEnemyType(tile) >= 0)
            {
                enemies[enemies_number].spawn( { j * TILE_LENGTH, i * TILE_LENGTH }, levels::getTileEnemyType(tile));
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
            }else if(levels::getTileItemId(tile) >= 0)
            {
                int8 itemId = levels::getTileItemId(tile);
                itemToBePickedUp.spawn(itemId, { j * TILE_LENGTH, i * TILE_LENGTH } );
            }
        }
    }*/
}

//==========================================================
const CollisionCheckResult EntitiesManager::collisionCheck(const Position & ppos)
{
    for(short i=0; i < enemies_number; i++)
    {
        if(enemies[i].checkEnemyCollision(enemies[i].getPos(), ppos, false))
        {
            return HIT_ENEMY;
        }
    }

    for(short i=0; i < character_number; i++)
    {
        if(characters[i].checkCharacterCollision(characters[i].getPos(), ppos))
        {
            return HIT_CHARACTER;
        }
    }

    if(itemToBePickedUp.isPresent() && itemToBePickedUp.collidesWithPlayer(ppos))
    {
        ItemsManager::instance()->foundItem(itemToBePickedUp.getId());
        itemToBePickedUp = Item();

        DialogManager::instance()->printSingleSentence(F("You found\nan item"));
    }

    return FREE;
}

//==========================================================
void EntitiesManager::fireCollisionCheck(const Position & pos, const short & rangeX, const short & rangeY, const HitType & hitType)
{
    for(short i=0; i < enemies_number; i++)
    {
        if(enemies[i].isAlive() && rectangleCollision({pos, rangeX, rangeY}, {enemies[i].getPos(), enemies[i].getWidth(), enemies[i].getHeight()}))
        {
            enemies[i].onHit(hitType);
        }
    }
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
                    triggers[i].triggered = true;
                    getCharacterWithId(62)->moveDistance(-50);
        
                    triggerEvent = START_ANIM;
                    break;
                case 3:
                    DialogManager::instance()->printTextForTrigger(&triggers[i]);
                    triggers[i].triggered = true;
                    break;
                case 19:
                    triggerEvent = END_LEVEL;
                    break;
            }
        }
    }
 
}

//==========================================================
TriggerEvent EntitiesManager::popTriggerEvent()
{
    TriggerEvent e = triggerEvent;
    triggerEvent = NO_EVENT;
    return e;
}

//==========================================================
void EntitiesManager::startNewLevel()
{
    clearEntities();
    spawnEntities(Map::instance());
    triggerEvent = NO_EVENT;
}

//==========================================================
Trigger * EntitiesManager::getTriggerForEvent(const TriggerEvent & event) const
{
    switch(event)
    {
        case START_DIALOG_2:
            return getTriggerWithId(2);
    }
    return nullptr;
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

    enemies_number = 0;
    character_number = 0;
    trigger_number = 0;

    itemToBePickedUp = Item();
}

//==========================================================
Character* EntitiesManager::getCharacterWithId(int8 characterId)
{
    for(short i=0; i < character_number; i++)
    {
        if(characters[i].getId() == characterId)
        {
            return &characters[i];
        }
    }
}

//==========================================================
Trigger* EntitiesManager::getTriggerWithId(int8 triggerId)
{
    for(short i=0; i < trigger_number; i++)
    {
        if(triggers[i].id == triggerId)
        {
            return &triggers[i];
        }
    }
}