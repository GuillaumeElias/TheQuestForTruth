#include "Map.h"
#include "../Tiles.h"

//=============================================================
Map::Map(const Position & playerPos)
    : playerPosition(playerPos)
    , current_level(0)
    , scroll_x(0)
    , scroll_y(0)
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
    else if(scroll_x + SCREEN_WIDTH > level_width * TILE_LENGTH)
    {
        scroll_x = level_width * TILE_LENGTH - SCREEN_WIDTH;
    }

    //COMPUTE SCROLL_Y BASED ON PLAYER POSITION
    scroll_y = playerPosition.y + PLAYER_HEIGHT - MID_HEIGHT;
    if(scroll_y < 0)
    {
        scroll_y = 0;
    }
    else if(scroll_y + SCREEN_HEIGHT > LEVEL_HEIGHT * TILE_LENGTH)
    {
        scroll_y = LEVEL_HEIGHT * TILE_LENGTH - SCREEN_HEIGHT;
    }

    short x = 0;
    short y = 0;

    for(short index = 0; index < level_length; index ++)
    {        
        levels::Cell c = levels::getCell(current_level, index);
        
        if(c.count == 0xFF)
        {
            drawTile(c.tile, x, y, arduboy); 
                        
            y += TILE_LENGTH;
            x = 0;
        }
        else
        {
            short stopX = x + c.count * TILE_LENGTH;
            for(; x < stopX; x += TILE_LENGTH)
            {
                drawTile(c.tile, x, y, arduboy);                
            }
        }
    }
}

//=============================================================
void Map::drawTile(levels::Tile tile, short x, short y, Arduboy2 * arduboy)
{
    short screenX = x - scroll_x;
    short screenY = y - scroll_y;
    if(screenX > -TILE_LENGTH && screenX <= SCREEN_WIDTH && screenY > -TILE_LENGTH && screenY <= SCREEN_HEIGHT)
    {
        switch(tile)
        {
            case levels::Tile::WALL:
                arduboy->drawBitmap(screenX, screenY, tiles::WALL, TILE_LENGTH, TILE_LENGTH);
                break;
            case levels::Tile::WALL_BACK:
                arduboy->drawBitmap(screenX, screenY, tiles::WALL_BACK, TILE_LENGTH, TILE_LENGTH);
                break;
            case levels::Tile::DOOR_UP:
                arduboy->drawBitmap(screenX, screenY, tiles::DOOR_UP, TILE_LENGTH, TILE_LENGTH);
                break;
            case levels::Tile::BRICK:
                arduboy->drawBitmap(screenX, screenY, tiles::BRICK, TILE_LENGTH, TILE_LENGTH);
                break;   
            default:
                //no texture
            break;
            case levels::Tile::FIRTREE_UPLEFT:
                arduboy->drawBitmap(screenX, screenY, tiles::FIRTREE_UPLEFT, TILE_LENGTH, TILE_LENGTH);
                break;
            case levels::Tile::FIRTREE_UPRIGHT:
                arduboy->drawBitmap(screenX, screenY, tiles::FIRTREE_UPRIGHT, TILE_LENGTH, TILE_LENGTH);
                break;
            case levels::Tile::FIRTREE_DOWNLEFT:
                arduboy->drawBitmap(screenX, screenY, tiles::FIRTREE_DOWNLEFT, TILE_LENGTH, TILE_LENGTH);
                break;
            case levels::Tile::FIRTREE_DOWNRIGHT:
                arduboy->drawBitmap(screenX, screenY, tiles::FIRTREE_DOWNRIGHT, TILE_LENGTH, TILE_LENGTH);
                break;
            case levels::Tile::DIRT:
                arduboy->drawBitmap(screenX, screenY, tiles::DIRT, TILE_LENGTH, TILE_LENGTH);
                break;
            case levels::Tile::_TRIGGER_END_LEVEL:
                static int circleSize = 0;
                circleSize = (circleSize + 1) % (TILE_LENGTH / 2);
                arduboy->drawCircle(screenX, screenY, circleSize);
                break;
        }
    }
}

//=============================================================
void Map::startLevel()
{
    level_length = levels::getLevelSize(current_level);
    level_width = 1; //precount the last cell of the row
    bool parseWidth = true;

    short row = 0;
    level_row_indexes[0] = 0;

    for(short index = 0; index < level_length; index ++)
    {
        levels::Cell c = levels::getCell(current_level, index);
        
        if(c.count == 0xFF)
        {      
            parseWidth = false;
            if(index < level_length - 1)
            {
                ++row;
                level_row_indexes[row] = index + 1;
            }
        }
        else if(parseWidth)
        {
            level_width += c.count;
        }
    }
}

//=============================================================
void Map::startNextLevel()
{
    current_level++;
    startLevel();
}

//=============================================================
bool Map::checkCollision(short x, short y, short w, short h) const
{
    return checkCollisionForPoint(x             , y         )   //1
        || checkCollisionForPoint(x + w / 2     , y         )   //2      1-----2-----3
        || checkCollisionForPoint(x + w         , y         )   //3      |           |
        || checkCollisionForPoint(x             , y + h / 2 )   //4      4           7
        || checkCollisionForPoint(x             , y + h     )   //5      |           |
        || checkCollisionForPoint(x + w / 2     , y + h     )   //6      5-----6-----8
        || checkCollisionForPoint(x + w         , y + h / 2 )   //7
        || checkCollisionForPoint(x + w         , y + h     );  //8
}

//=============================================================
bool Map::checkCollisionForPoint(short x, short y) const
{
    short tile_i = y / TILE_LENGTH;
    short tile_j = x / TILE_LENGTH;
    
    levels::Tile tile = getTile(current_level, tile_i, tile_j);
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

    levels::Tile tile = getTile(current_level, tile_i, tile_j);

    short doorNb = tile - levels::Tile::DOOR_HOUSE_0;
    if(doorNb > 3)
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
short Map::getLevelLength() const
{
    return level_length;
}

//=============================================================
short Map::getCurrentLevel() const
{
    return current_level;
}

//=============================================================
void Map::reset()
{
    current_level = 0;
}


//=============================================================
levels::Tile Map::getTile(short level, short i, short j) const
{
    short colCount = 0;
    short index = level_row_indexes[i];
    short stopI = index + level_width;
    for(; index < stopI; ++index)
    {
        levels::Cell c = levels::getCell(current_level, index);

        colCount += (c.count == 0xFF) ? 1 : c.count;
        if(colCount >= j + 1)
        {
            return c.tile;
        }
        
    }
}
