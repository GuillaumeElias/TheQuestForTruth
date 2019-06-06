#ifndef _LEVELS_H_
#define _LEVELS_H_

template <typename T, short N>
constexpr short arraysize(T(&)[N])
{
    return N;
}

namespace levels
{
    typedef enum __attribute__ ((packed))
    {
        VOID = 0,
        WALL = 1,
        WALL_BACK = 2,
        DOOR_UP = 3,
        BRICK = 4,
        FIRTREE_UPLEFT = 5,
        FIRTREE_UPRIGHT = 6,
        FIRTREE_DOWNLEFT = 7,
        FIRTREE_DOWNRIGHT = 8,
        DIRT = 9,
        DOOR_HOUSE_0 = 40, //NOTHING
        DOOR_HOUSE_1 = 41, //FIRST CLUE
        DOOR_HOUSE_2 = 42, //SECOND CLUE
        _ENEMY_1 = 51,
        _ENEMY_2 = 52,
        _CHARACTER_1 = 61,
        _CHARACTER_2 = 62,
        _CHARACTER_3 = 63,
        _ITEM_1 = 71,
        _TRIGGER_CHARACTER_1 = 81,
        _TRIGGER_CHARACTER_2 = 82,
        _TRIGGER_CHARACTER_3 = 83,
        _TRIGGER_END_LEVEL = 99
    } Tile;

    struct Cell
    {
        Tile tile;
        byte count; // FF -> end of row
    };

    union CellValue
    {
        uint16_t val;
        Cell c;
    };

    PROGMEM static const Cell LEVEL_0[] =
    { //LEVEL 0
        {0,47}, {1, 0xFF},
        {0,47}, {1, 0xFF},
        {0,47}, {1, 0xFF},
        {0,47}, {1, 0xFF},
        {0, 4}, {1,1}, {0,41}, {4,1}, {1,0xFF},
        {0, 4}, {1,1}, {0,41}, {4,1}, {1,0xFF},
        {0,40}, {52,1}, {0,6}, {1, 0xFF},
        {0, 9}, {81,1} , {61,1}, {0,9}, {51,1}, {0,26}, {1, 0xFF},
        {0,47}, {1, 0xFF},
        {0,4}, {1,43}, {1, 0xFF},
        {0,4}, {1,43}, {1, 0xFF},
        {0,2}, {1,2}, {0,43}, {1, 0xFF},
        {0,2}, {1,2}, {0,43}, {1, 0xFF}
    };

    static short getLevelSize(short level)
    {
        switch(level)
        {
            case 0: return arraysize(LEVEL_0);
        }
        return 0;
    }

    static Cell getCell(short level, short index)
    {
        switch(level)
        {
            case 0:
                CellValue cv = {pgm_read_word(&LEVEL_0[index])};
                return cv.c;
        }
    }

    static int8 getTileEnemyType(Tile t)
    {
        if(t >= _ENEMY_1 && t <= _ENEMY_2)
        {
            return t - _ENEMY_1 + 1;
        }
        return -1;
    }

    static bool isCharacterTile(Tile t)
    {
        return t >= _CHARACTER_1 && t <= _CHARACTER_3;
    }

    static int8 getTileItemId(Tile t)
    {
        if(t >= _ITEM_1 && t <= _ITEM_1)
        {
            return t - _ITEM_1 + 1;
        }
        return -1;
    }

    static int8 getTileTriggerId(Tile t)
    {
        if(t >= _TRIGGER_CHARACTER_1 && t <= _TRIGGER_END_LEVEL)
        {
            return t - _TRIGGER_CHARACTER_1 + 1;
        }
        return -1;
    }
    
}

#endif
