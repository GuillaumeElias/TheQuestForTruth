#include "Menu.h"

namespace
{
    static const short CURSOR_LEFT_X = 30;
    static const short CURSOR_TOP_Y = 30;
    static const short LINE_HEIGHT = 10;
    static const short NB_ITEMS = 2;
    static const short SELECTION_BALL_WIDTH = 5;
}

//=============================================================
Menu::Menu()
    : selection( 1 )
    , inGame( false )
{
}

//=============================================================
void Menu::update(Arduboy2 * arduboy)
{
    if(inGame)
    {
        arduboy->setCursor(CURSOR_LEFT_X, CURSOR_TOP_Y);
        arduboy->println("RESUME");
        arduboy->setCursor(CURSOR_LEFT_X, CURSOR_TOP_Y + LINE_HEIGHT);
        arduboy->println("INVENTORY");
    }
    else
    {
        arduboy->setCursor(CURSOR_LEFT_X, CURSOR_TOP_Y);
        arduboy->println("PLAY");
        arduboy->setCursor(CURSOR_LEFT_X, CURSOR_TOP_Y + LINE_HEIGHT);
        arduboy->println("ABOUT");
    }

    if( arduboy->pressed( UP_BUTTON ) )
    {
        if(selection < NB_ITEMS)
        {
            selection++;
        }
    }
    else if( arduboy->pressed(DOWN_BUTTON) )
    {
        if(selection > 1)
        {
            selection--;
        }
    }
    if( arduboy->pressed(A_BUTTON) )
    {
        if(selection == 1)
        {
            selectedOption = GO;
        }
    }

    short ballY = CURSOR_TOP_Y;
    if(selection > 1)
    {
        ballY += LINE_HEIGHT;
    }

    arduboy->drawCircle(CURSOR_LEFT_X - SELECTION_BALL_WIDTH, ballY, SELECTION_BALL_WIDTH / 2);
}

//=============================================================
void Menu::setInGame(bool inGame)
{
    this->inGame = inGame;
}

//=============================================================
const MenuOption Menu::getSelectedOption() const
{
    return selectedOption;
}
