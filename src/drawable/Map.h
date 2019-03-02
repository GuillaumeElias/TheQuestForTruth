#ifndef _MAP_H_
#define _MAP_H_

#include <Arduboy2.h>

#include "../Constants.h"
#include "../abstract/Drawable.h"
#include "../abstract/Singleton.h"
#include "../Levels.h"

class Map : public Drawable, public Singleton<Map>
{
    public:
        Map(const Position & playerPos);
        void draw( Arduboy2 * arduboy );
        void startLevel();
        void startNextLevel();

        bool checkCollision(const short& x, const short& y, const short& w, const short& h) const;
        bool checkCollisionForPoint(const short& x, const short& y) const;
        bool checkPlayerIsOnADoor() const;
        short getCurrentDoorNumber() const; // will be < 0 if none

        short getScrollX() const;
        short getScrollY() const;
        short getLevelHeight() const;
        short getLevelLength() const;
        short getCurrentLevel() const;
    private:
        const Position & playerPosition;

        short current_level;
        short scroll_x, scroll_y;
        short level_height;
        short level_length;
};

#endif
