#ifndef _ENTITIES_MANAGER_H_
#define _ENTITIES_MANAGER_H_

#include <Arduboy2.h>
#include "abstract/Singleton.h"
#include "drawable/Map.h"
#include "drawable/Enemy.h"
#include "drawable/Character.h"
#include "Trigger.h"

class EntitiesManager : public Singleton<EntitiesManager>
{
    public: 
        EntitiesManager(Arduboy2 * arduboy);

        void drawEntities() const;
        void spawnEntities(Map * map);
        void moveEntities();

        const CollisionCheckResult collisionCheck(const Position & pos) const;
        void triggerCheckAndExecute(const Position & pos);

    private:
        Arduboy2 * arduboy;
        
        Enemy enemies[MAX_ENEMIES_PER_LEVEL];
        Character characters[MAX_CHARACTERS_PER_LEVEL];
        Trigger triggers[MAX_TRIGGERS_PER_LEVEL];

        int8 enemies_number, character_number, trigger_number;
};



#endif
