#include "Game.h"

//==========================================================
Game::Game()
    : map( player.getPos() )
    , entitiesManager( &arduboy )
    , mode( GameMode::MENU )
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
    arduboy.pollButtons();

    switch(mode)
    {
        /****************************PLAY/ANIM*******************************/
        case PLAY: 
        case ANIM:
        {
            //PRINT HUD
            arduboy.print(player.getLife());

            //MOVE OBJECTS
            if(mode == PLAY) //don't move player if in animation
            {
                player.move( &arduboy );
            }
            entitiesManager.moveEntities();

            //DRAW OBJECTS
            map.draw( &arduboy );
            player.draw( &arduboy );
            entitiesManager.drawEntities();
            dialogManager.draw( &arduboy );

            TriggerEvent event = entitiesManager.popTriggerEvent();
            if(event == TriggerEvent::END_LEVEL) //next level triggered
            {
                map.startNextLevel();
                entitiesManager.startNewLevel();
                player.levelStart();
            }
            else if(event == TriggerEvent::START_ANIM) //start animation
            {
                mode = ANIM;
            }
            else if(event == TriggerEvent::STOP_ANIM) //start animation
            {
                mode = PLAY;
            }
            else if(isStartDialogEvent(event))
            {
                mode = PLAY;
                dialogManager.printTextForTrigger(entitiesManager.getTriggerForEvent(event));
            }
            else if(arduboy.pressed( B_BUTTON )) //menu triggered
            {
                mode = GameMode::MENU;
            }
        }
        break;

        /****************************MENU*******************************/
        case MENU:
            menu.update(&arduboy);

            if(menu.popSelectedOption() == MenuOption::GO)
            {
                mode = GameMode::PLAY;
                menu.setInGame(true);
            }

            break;
    }

    arduboy.display();
}
