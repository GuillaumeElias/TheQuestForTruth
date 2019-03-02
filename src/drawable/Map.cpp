#include "Map.h"
#include "../Tiles.h"

//=============================================================
Map::Map(const Position & playerPos)
    : playerPosition(playerPos)
    , current_level(0)
    , scroll_x(0)
    , scroll_y(0)
    , level_height(0)
    , level_length(0)
{
}

//=============================================================
void Map::draw(Arduboy2 * arduboy)
{
    //COMPUTE SCROLL_X BASED ON PLAYER POSITION
    scroll_x = playerPosition.x - MID_WIDTH;
    if(scroll_x < 0)
    {
        scroll_x = 0;
    }
    else if(scroll_x + SCREEN_WIDTH > level_length * TILE_LENGTH)
    {
        scroll_x = level_length * TILE_LENGTH - SCREEN_WIDTH;
    }

    short level_start_j = scroll_x / TILE_LENGTH;
    short scroll_offset_x = - (scroll_x % TILE_LENGTH);


    //COMPUTE SCROLL_Y BASED ON PLAYER POSITION
    scroll_y = playerPosition.y + PLAYER_HEIGHT - MID_HEIGHT;
    if(scroll_y < 0)
    {
        scroll_y = 0;
    }
    else if(scroll_y + SCREEN_HEIGHT > level_height * TILE_LENGTH)
    {
        scroll_y = level_height * TILE_LENGTH - SCREEN_HEIGHT;
    }

    short level_up_i = scroll_y / TILE_LENGTH;
    short level_bottom_i = level_up_i + SCREEN_HEIGHT / TILE_LENGTH;
    short scroll_offset_y = -(scroll_y % TILE_LENGTH);

    //DRAW SCREEN
    short screen_y = SCREEN_HEIGHT + scroll_offset_y - TILE_SCREEN_Y_OFFSET;
    for (short i = level_bottom_i; i >= level_up_i; i--)
    {
        short screen_x = scroll_offset_x;
        for (short j = level_start_j; j < level_length; j++)
        {
            levels::Tile tile = levels::getTile(current_level, i, j);
            
            switch(tile)
            {
                case levels::Tile::WALL:
                    arduboy->drawBitmap(screen_x, screen_y, tiles::WALL, TILE_LENGTH, TILE_LENGTH);
                    break;
                case levels::Tile::WALL_BACK:
                    arduboy->drawBitmap(screen_x, screen_y, tiles::WALL_BACK, TILE_LENGTH, TILE_LENGTH);
                    break;
                case levels::Tile::DOOR_UP:
                    arduboy->drawBitmap(screen_x, screen_y, tiles::DOOR_UP, TILE_LENGTH, TILE_LENGTH);
                    break;
                case levels::Tile::BRICK:
                    arduboy->drawBitmap(screen_x, screen_y, tiles::BRICK, TILE_LENGTH, TILE_LENGTH);
                    break;   
                case levels::Tile::DOOR_HOUSE_1:
                    //to texture
                break;
                case levels::Tile::FIRTREE_UPLEFT:
                    arduboy->drawBitmap(screen_x, screen_y, tiles::FIRTREE_UPLEFT, TILE_LENGTH, TILE_LENGTH);
                    break;
                case levels::Tile::FIRTREE_UPRIGHT:
                    arduboy->drawBitmap(screen_x, screen_y, tiles::FIRTREE_UPRIGHT, TILE_LENGTH, TILE_LENGTH);
                    break;
                case levels::Tile::FIRTREE_DOWNLEFT:
                    arduboy->drawBitmap(screen_x, screen_y, tiles::FIRTREE_DOWNLEFT, TILE_LENGTH, TILE_LENGTH);
                    break;
                case levels::Tile::FIRTREE_DOWNRIGHT:
                    arduboy->drawBitmap(screen_x, screen_y, tiles::FIRTREE_DOWNRIGHT, TILE_LENGTH, TILE_LENGTH);
                    break;
                case levels::Tile::DIRT:
                    arduboy->drawBitmap(screen_x, screen_y, tiles::DIRT, TILE_LENGTH, TILE_LENGTH);
                    break;
                case levels::Tile::_TRIGGER_END_LEVEL:
                    arduboy->drawCircle(screen_x + TILE_LENGTH / 3, screen_y + TILE_LENGTH / 3, TILE_LENGTH / 3);
                    break;
            }
            screen_x += TILE_LENGTH;
        }

        screen_y -= TILE_LENGTH;
    }
}

//=============================================================
void Map::startLevel()
{
    level_height = sizeof( levels::LEVEL_TILES[current_level]) / sizeof(*levels::LEVEL_TILES[current_level] );
    level_length = sizeof( *levels::LEVEL_TILES[current_level]) / sizeof(**levels::LEVEL_TILES[current_level] );
}

//=============================================================
void Map::startNextLevel()
{
    current_level++;
    startLevel();
}

//=============================================================
bool Map::checkCollision(const short& x, const short& y, const short& w, const short& h) const
{
    return checkCollisionForPoint(x, y) || checkCollisionForPoint(x + w, y) ||  checkCollisionForPoint(x, y + h) ||  checkCollisionForPoint(x + w, y + h);
}

//=============================================================
bool Map::checkCollisionForPoint(const short& x, const short& y) const
{
    short tile_i = y / TILE_LENGTH;
    short tile_j = x / TILE_LENGTH;
    
    levels::Tile tile = levels::getTile(current_level, tile_i, tile_j);
    return tile == levels::Tile::WALL || tile == levels::Tile::DIRT || tile == levels::Tile::BRICK;
}

//=============================================================
bool Map::checkPlayerIsOnADoor() const
{
    return getCurrentDoorNumber() >= 0;
}

//=============================================================
short Map::getCurrentDoorNumber() const
{
    short tile_i = playerPosition.y / TILE_LENGTH + 1;
    short tile_j = playerPosition.x / TILE_LENGTH;

    levels::Tile tile = levels::getTile(current_level, tile_i, tile_j);

    short doorNb = tile - levels::Tile::DOOR_HOUSE_0;
    if(doorNb > 2)
    {
        return -1;
    }
    return doorNb;
}

//=============================================================
short Map::getScrollX() const
{
    return scroll_x;
}

//=============================================================
short Map::getScrollY() const
{
    return scroll_y;
}

//=============================================================
short Map::getLevelHeight() const
{
    return level_height;
}

//=============================================================
short Map::getLevelLength() const
{
    return level_length;
}

//=============================================================
short Map::getCurrentLevel() const
{
    return current_level;
}
