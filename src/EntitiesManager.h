#ifndef _ENTITIES_MANAGER_H_
#define _ENTITIES_MANAGER_H_

#include <Arduboy2.h>
#include "drawable/Map.h"
#include "drawable/Enemy.h"

class EntitiesManager
{
    public: 
        EntitiesManager(Arduboy2 * arduboy);

        void drawEnemies() const;
        void spawnEnemies(Map * map);
        void moveEnemies();

        const CollisionCheckResult collisionCheck(const Position & pos) const;

    private:
        Arduboy2 * arduboy;
        
        Enemy enemies[MAX_ENEMIES_PER_LEVEL];
        short enemies_number;
};



#endif
