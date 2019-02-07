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
        /****************************PLAY*******************************/
        case PLAY:    

            //print HUD
            arduboy.print(player.getLife());

            //move objects
            player.move( &arduboy );
            entitiesManager.moveEntities();

            //draw objects
            map.draw( &arduboy );
            player.draw( &arduboy );
            entitiesManager.drawEntities();
            dialogManager.draw( &arduboy );

            if(entitiesManager.isLevelFinished()) //next level triggered
            {
                map.startNextLevel();
                entitiesManager.startNewLevel();
                player.levelStart();
            } 
            else if(arduboy.pressed( B_BUTTON ))//menu triggered
            {
                mode = GameMode::MENU;
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
