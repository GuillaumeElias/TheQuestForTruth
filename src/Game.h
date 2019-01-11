#ifndef _GAME_H_
#define _GAME_H_

#include <Arduboy2.h>

#include "drawable/Player.h"
#include "drawable/Map.h"
#include "EntitiesManager.h"

class Game
{
	private:
		Arduboy2 arduboy;

		Player player;
		Map map;
		EntitiesManager entitiesManager;
        
	public:	
		Game();
		void init();
		void update();
};

#endif
