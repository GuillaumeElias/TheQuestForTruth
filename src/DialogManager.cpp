#include "DialogManager.h"
#include "drawable/Map.h"
#include "ItemsManager.h"

namespace
{
    static const short DEFAULT_TRIGGER_TEXT_PADDING_X = 30;
    static const short TRIGGER_TEXT_PADDING_Y = 20;
}

//======================================================================
DialogManager::DialogManager()
    : currentSentenceSize(0)
    , currentLineIndex(0)
    , currentTrigger(nullptr)
    , readFromPgmMem(false)
    , extraTextPaddingX(0)
{
    
}

//======================================================================
void DialogManager::printTextForTrigger(Trigger * trigger)
{
    currentTrigger = trigger;
    currentLineIndex = 0;
    readFromPgmMem = false;
    printNextLineForTrigger();
}

//======================================================================
void DialogManager::printNextLineForTrigger()
{
    extraTextPaddingX = DEFAULT_TRIGGER_TEXT_PADDING_X;

    switch(currentTrigger->id)
    {
        case 1:
            currentNbOfLines = 4;
            switch(currentLineIndex)
            {
                case 0: printSentence("He did it again."); break;
                case 1: printSentence("It is really bad."); break;
                case 2: printSentence("Go accross the hill."); break;
                case 3: printSentence("You will see."); break;
            }

        break;

        case 2:
            currentNbOfLines = 4;
            extraTextPaddingX = 68;

            switch(currentLineIndex)
            {
                case 0: extraTextPaddingX = -5; printSentence("Hello."); break;
                case 1: printSentence("This is the Village."); break;
                case 2: printSentence("Beware of the ghosts."); break;
                case 3: printSentence("They are everywhere."); break;
            }

        break;

        case 3:
            currentNbOfLines = 5;
            switch(currentLineIndex)
            {
                case 0: printSentence("Hello young boy."); break;
                case 1: extraTextPaddingX = 58; printSentence("Where are you off to?"); break;
                case 2: printSentence("Those legs..."); break;
                case 3: extraTextPaddingX = 60; printSentence("They look good on you."); break;
                case 4: printSentence("He he he!."); break;
            }
            
            break;

    }
}

//======================================================================
void DialogManager::printSingleSentence(char * charArray, bool readFromPgmMemory, int8 extraPadX)
{
    readFromPgmMem = readFromPgmMemory;
    extraTextPaddingX = extraPadX;
    currentTrigger = nullptr;
    printSentence(charArray);
}

//======================================================================
void DialogManager::printSentence(char * charArray)
{
    reset();

    currentSentence = charArray;

    if(readFromPgmMem)
    {
        currentSentenceSize = strlen_P(charArray);
    }
    else
    {
        currentSentenceSize = strlen(charArray);
    }
}

//======================================================================
void DialogManager::reset()
{
    currentSentenceSize = 0;
    currentLetterPosition = 1;
    letterFrameCounter = 0;
    currentSentence = nullptr;
}

//======================================================================
void DialogManager::draw(Arduboy2 * arduboy)
{
    if(currentSentenceSize == 0) return;

    if(letterFrameCounter > DIALOG_LETTER_NBFRAMES)
    {
        if(currentLetterPosition >= currentSentenceSize)
        {
            if(letterFrameCounter > DIALOG_LETTER_NBFRAMES + DIALOG_SENTENCE_END_NBFRAMES)
            {
                currentSentenceSize = 0;
                currentLetterPosition = 0;

                if(currentLineIndex < currentNbOfLines)
                {
                    currentLineIndex++;
                    printNextLineForTrigger();
                }
                return;
            }
        }
        else
        {
            currentLetterPosition++;
            letterFrameCounter = 0;
        }
    }

    short startScreenX = DIALOG_DEFAULT_INIT_CURSOR_X;
    short screenY = DIALOG_DEFAULT_CURSOR_Y;
    if(currentTrigger)
    {
        startScreenX = currentTrigger->pos.x - Map::instance()->getScrollX();
        screenY =  currentTrigger->pos.y - Map::instance()->getScrollY() - TRIGGER_TEXT_PADDING_Y;
    }
    
    startScreenX -= extraTextPaddingX;

    short nbCharacterOnCurrentLine = 0;
    for(int8 i=0; i < currentLetterPosition; i++)
    {
        short cursorX = startScreenX + nbCharacterOnCurrentLine * DIALOG_CHAR_WIDTH;
        char currentChar = getChar(i);
        if(currentChar == '\n')
        {
            screenY += DIALOG_CHAR_HEIGHT;
            cursorX = startScreenX;
            nbCharacterOnCurrentLine = 0;
        }
        else
        {
            arduboy->setCursor(cursorX, screenY);
            arduboy->write(currentChar);
            nbCharacterOnCurrentLine++;
        }
    }

    letterFrameCounter++;
}

//======================================================================
char DialogManager::getChar(short i)
{
    if(readFromPgmMem)
    {
        return pgm_read_byte(&currentSentence[i]);
    }
    
    return currentSentence[i];
}