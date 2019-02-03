#include "DialogManager.h"
#include "drawable/Map.h"

namespace
{
    short CURSOR_Y = 15;
    short DEFAULT_INIT_MARGIN_X = 30;
    short TRIGGER_TEXT_PADDING_X = 30;
    short TRIGGER_TEXT_PADDING_Y = 30;
    short CHAR_WIDTH = 6;
}

//======================================================================
DialogManager::DialogManager()
    : currentSentenceSize(0)
    , currentLineIndex(0)
    , currentTrigger(nullptr)
{
    
}

//======================================================================
void DialogManager::printTextForTrigger(Trigger * trigger)
{
    currentTrigger = trigger;
    currentLineIndex = 0;
    printNextLine();
}

//======================================================================
void DialogManager::printNextLine()
{
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

    }
}

//======================================================================
void DialogManager::printSentence(char * charArray)
{
    currentSentence = charArray;

    char* p = charArray;
    for (; *p != '\0'; ++p);
    currentSentenceSize = p - charArray;
    currentLetterPosition = 1;
    letterFrameCounter = 0;
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

    short startScreenX = DEFAULT_INIT_MARGIN_X;
    short screenY = CURSOR_Y;
    if(currentTrigger)
    {
        startScreenX = currentTrigger->pos.x - Map::instance()->getScrollX() - TRIGGER_TEXT_PADDING_X;
        screenY =  currentTrigger->pos.y - Map::instance()->getScrollY() - TRIGGER_TEXT_PADDING_Y;
    }

    for(int8 i=0; i < currentLetterPosition; i++)
    {
        short cursorX = startScreenX + i * CHAR_WIDTH;
        arduboy->setCursor(cursorX, screenY);
        arduboy->write(currentSentence[i]);
    }

    letterFrameCounter++;
}
