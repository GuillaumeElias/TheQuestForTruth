#include "DialogManager.h"

namespace
{
    short CURSOR_Y = 15;
    short INIT_CURSOR_I = 3;
    short CHAR_WIDTH = 6;
}

//======================================================================
DialogManager::DialogManager()
    : currentSentenceSize(0)
    , currentLineIndex(0)
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
                case 0: printSentence("He did it."); break;
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

    short marginX = INIT_CURSOR_I * CHAR_WIDTH;
    for(int8 i=0; i < currentLetterPosition; i++)
    {
        short cursorX = marginX + i * CHAR_WIDTH;
        arduboy->setCursor(cursorX, CURSOR_Y);
        arduboy->write(currentSentence[i]);
    }

    letterFrameCounter++;
}
