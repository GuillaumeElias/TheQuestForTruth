#ifndef _GAME_H_
#define _GAME_H_

#include <Arduboy2.h>

#include "EntitiesManager.h"
#include "DialogManager.h"
#include "Menu.h"
#include "BoxView.h"
#include "drawable/Player.h"
#include "drawable/Map.h"

typedef enum __attribute__ ((packed))
{
    PLAY,
    MENU,
    ANIM,
    HOUSE,
    CINEMATIC
} GameMode;

class Game
{
    public:	
        Game();
        void init();
        void update();

    private:
        Arduboy2 arduboy;

        Menu menu;
        Player player;
        Map map;
        EntitiesManager entitiesManager;
        DialogManager dialogManager;
        BoxView boxView;

        GameMode mode;
};

#endif
