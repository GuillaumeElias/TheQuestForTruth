#include "Menu.h"
#include "ItemsManager.h"

namespace
{
    static const short MENU_CURSOR_LEFT_X = 50;
    static const short MENU_CURSOR_TOP_Y = 25;
    static const short MENU_INGAME_CURSOR_TOP_Y = 15;

    static const short CLUES_CURSOR_LEFT_X = 5;
    static const short CLUES_CURSOR_TOP_Y = 15;

    static const short INVENTORY_CURSOR_LEFT_X = 5;
    static const short INVENTORY_CURSOR_TOP_Y = 15;

    static const short LINE_HEIGHT = 15;
    static const short NB_ITEMS_INGAME = 3;
    static const short NB_ITEMS_PREGAME = 2;
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
            if( arduboy->justPressed(A_BUTTON) || arduboy->justPressed(B_BUTTON) )
            {
                selectedOption = NONE;
            }
            else
            {
                displayInventory(arduboy);
            }
            return;
    }

    short initCursorY;

    if(inGame)
    {
        initCursorY = MENU_INGAME_CURSOR_TOP_Y;
        short cursorY = initCursorY;
        arduboy->setCursor(MENU_CURSOR_LEFT_X, cursorY);
        arduboy->println(F("RESUME"));
        cursorY += LINE_HEIGHT;
        arduboy->setCursor(MENU_CURSOR_LEFT_X, cursorY);
        arduboy->println(F("CLUES"));
        cursorY += LINE_HEIGHT;
        arduboy->setCursor(MENU_CURSOR_LEFT_X, cursorY);
        arduboy->println(F("INVENTORY"));
    }
    else
    {
        initCursorY = MENU_CURSOR_TOP_Y;
        arduboy->setCursor(MENU_CURSOR_LEFT_X, initCursorY);
        arduboy->println(F("PLAY"));
        arduboy->setCursor(MENU_CURSOR_LEFT_X, initCursorY + LINE_HEIGHT);
        arduboy->println(F("ABOUT"));
    }

    if( arduboy->justPressed( DOWN_BUTTON ) )
    {
        if(selection < getNbItems())
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

    short ballY = initCursorY + SELECTION_BALL_UP_PADDING + LINE_HEIGHT * (selection - 1);
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
void Menu::displayInventory(Arduboy2 * arduboy)
{
    bool nothing = true;

    arduboy->setCursor(INVENTORY_CURSOR_LEFT_X, INVENTORY_CURSOR_TOP_Y);

    if((ItemsManager::instance()->getItems() & 0b00000001))
    {
        arduboy->print(F("- Pepper spray"));
        nothing = false;
    }

    if(nothing)
    {
        arduboy->print(F("No items yet."));
    }
}

//=============================================================
void Menu::printFromProgmem(Arduboy2 * arduboy, const char * textInProgMem)
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

//=============================================================
short Menu::getNbItems() const
{
    if(inGame)
    {
        return NB_ITEMS_INGAME;
    }
    return NB_ITEMS_PREGAME;
}
