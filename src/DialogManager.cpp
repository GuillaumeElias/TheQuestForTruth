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
{
    
}

//======================================================================
void DialogManager::printTextForTrigger(Trigger * trigger)
{
    currentTrigger = trigger;
    currentLineIndex = 0;
    readFromPgmMem = false;
    printNextLine();
}

//======================================================================
void DialogManager::printNextLine()
{
    triggerTextPaddingX = DEFAULT_TRIGGER_TEXT_PADDING_X;

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
            triggerTextPaddingX = 68;

            switch(currentLineIndex)
            {
                case 0: triggerTextPaddingX = -5; printSentence("Hello."); break;
                case 1: printSentence("This is the Village."); break;
                case 2: printSentence("Beware of the ghosts."); break;
                case 3: printSentence("They are everywhere."); break;
            }

        break;

    }
}

//======================================================================
void DialogManager::printSingleSentence(char * charArray, bool readFromPgmMemory)
{
    readFromPgmMem = readFromPgmMemory;
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
        currentSentenceSize = strlen_P((char*)charArray);
    }
    else
    {
        char* p = charArray;
        for (; *p != '\0'; ++p);
        currentSentenceSize = p - charArray;
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
                    printNextLine();
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
        startScreenX = currentTrigger->pos.x - Map::instance()->getScrollX() - triggerTextPaddingX;
        screenY =  currentTrigger->pos.y - Map::instance()->getScrollY() - TRIGGER_TEXT_PADDING_Y;
    }

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
        char tBuffer[22];
        strcpy_P(tBuffer, (char*)currentSentence);
        return tBuffer[i];
    }
    
    return currentSentence[i];
}