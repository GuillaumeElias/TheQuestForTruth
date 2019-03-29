#include "Menu.h"
#include "ItemsManager.h"

namespace
{
    static const short MENU_CURSOR_LEFT_X = 50;
    static const short MENU_CURSOR_TOP_Y = 25;

    static const short CLUES_CURSOR_LEFT_X = 5;
    static const short CLUES_CURSOR_TOP_Y = 15;

    static const short LINE_HEIGHT = 15;
    static const short NB_ITEMS = 2;
    static const short SELECTION_BALL_WIDTH = 5;
    static const short SELECTION_BALL_UP_PADDING = 3;
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
    switch(selectedOption)
    {
        case ABOUT: 
        break;
        case CLUES:

            if( arduboy->justPressed(A_BUTTON) || arduboy->justPressed(B_BUTTON) )
            {
                selectedOption = NONE;
            }
            else
            {
                displayClues(arduboy);
            }
            return;
        case INVENTORY:
        break;
    }

    if(inGame)
    {
        arduboy->setCursor(MENU_CURSOR_LEFT_X, MENU_CURSOR_TOP_Y);
        arduboy->println(F("RESUME"));
        arduboy->setCursor(MENU_CURSOR_LEFT_X, MENU_CURSOR_TOP_Y + LINE_HEIGHT);
        arduboy->println(F("CLUES"));
    }
    else
    {
        arduboy->setCursor(MENU_CURSOR_LEFT_X, MENU_CURSOR_TOP_Y);
        arduboy->println(F("PLAY"));
        arduboy->setCursor(MENU_CURSOR_LEFT_X, MENU_CURSOR_TOP_Y + LINE_HEIGHT);
        arduboy->println(F("ABOUT"));
    }

    if( arduboy->justPressed( DOWN_BUTTON ) )
    {
        if(selection < NB_ITEMS)
        {
            selection++;
        }
    }
    else if( arduboy->justPressed(UP_BUTTON) )
    {
        if(selection > 1)
        {
            selection--;
        }
    }
    if( arduboy->justPressed(A_BUTTON) )
    {
        if(selection == 1)
        {
            selectedOption = GO;
        }
        if(inGame)
        {
            if(selection == 2)
            {
                selectedOption = MenuOption::CLUES;
            }
            else if(selection == 3)
            {
                selectedOption = MenuOption::INVENTORY;
            }
        }
        else //start
        {
           if(selection == 2)
            {
                selectedOption = MenuOption::ABOUT;
            }
        }
        
    }

    short ballY = MENU_CURSOR_TOP_Y + SELECTION_BALL_UP_PADDING;
    if(selection > 1)
    {
        ballY += LINE_HEIGHT;
    }

    arduboy->drawCircle(MENU_CURSOR_LEFT_X - SELECTION_BALL_WIDTH, ballY, SELECTION_BALL_WIDTH / 2);
}

//=============================================================
void Menu::displayClues(Arduboy2 * arduboy)
{
    bool nothing = true;

    arduboy->setCursor(CLUES_CURSOR_LEFT_X, CLUES_CURSOR_TOP_Y);

    if((ItemsManager::instance()->getCluesFound() & 0b00000001))
    {
        arduboy->print(F("1 - "));
        printFromProgmem(arduboy, CLUE_1);
        nothing = false;
    }

    if((ItemsManager::instance()->getCluesFound() & 0b00000010))
    {
        arduboy->setCursor(CLUES_CURSOR_LEFT_X, CLUES_CURSOR_TOP_Y + LINE_HEIGHT);
        arduboy->print(F("2 - "));
        printFromProgmem(arduboy, CLUE_2);
        nothing = false;
    }

    if(nothing)
    {
        arduboy->print(F("Nothing yet."));
    }
}

//=============================================================
void Menu::printFromProgmem(Arduboy2 * arduboy, char * textInProgMem)
{
    char tBuffer[strlen_P(textInProgMem)];
    strcpy_P(tBuffer, textInProgMem);
    arduboy->print(tBuffer);
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

//=============================================================
void Menu::clearSelectedOption()
{   
    selectedOption = NONE;
}
