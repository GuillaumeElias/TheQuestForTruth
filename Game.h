#ifndef _GAME_H_
#define _GAME_H_

#include <Arduboy2.h>

#include "Player.h"
#include "Map.h"
#include "Enemy.h"

class Game
{
	private:
		Arduboy2 arduboy;

		Player player;
		Map map;
        
        Enemy enemies[MAX_ENEMIES_PER_LEVEL];
        short enemies_number;

        void drawEnemies() const;
        void spawnEnemies();
        void moveEnemies();
        
	public:	
		Game();
		void init();
		void update();
};

#endif
