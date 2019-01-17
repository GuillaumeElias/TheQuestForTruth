#ifndef _GAME_H_
#define _GAME_H_

#include <Arduboy2.h>

#include "EntitiesManager.h"
#include "DialogManager.h"
#include "drawable/Player.h"
#include "drawable/Map.h"

class Game
{
    private:
        Arduboy2 arduboy;

        Player player;
        Map map;
        EntitiesManager entitiesManager;
        DialogManager dialogManager;
        
    public:	
        Game();
        void init();
        void update();
};

#endif
