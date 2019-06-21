#include "DialogManager.h"
#include "drawable/Map.h"
#include "ItemsManager.h"

namespace
{
    static const short DEFAULT_TRIGGER_TEXT_PADDING_X = 30;
    static const short TRIGGER_TEXT_PADDING_Y = 20;

    size_t getStringLength(PGM_P p)
    {
        size_t n = 0;
        while (1) {
            unsigned char c = pgm_read_byte(p++);
            if (c == 0) break;
            n++;
        }
        return n;
    }

}

//======================================================================
DialogManager::DialogManager()
    : currentSentenceSize(0)
    , currentLineIndex(0)
    , currentTrigger(nullptr)
    , extraTextPaddingX(0)
{
    
}

//======================================================================
void DialogManager::printTextForTrigger(Trigger * trigger)
{
    currentTrigger = trigger;
    currentLineIndex = 0;
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
                case 0: printSentence(F("He did it again.")); break;
                case 1: printSentence(F("It is really bad.")); break;
                case 2: printSentence(F("Go accross the hill.")); break;
                case 3: printSentence(F("You will see.")); break;
            }

        break;

        case 2:
            currentNbOfLines = 4;
            extraTextPaddingX = 68;

            switch(currentLineIndex)
            {
                case 0: extraTextPaddingX = -5; printSentence(F("Hello.")); break;
                case 1: printSentence(F("This is the Village.")); break;
                case 2: printSentence(F("Beware of the ghosts.")); break;
                case 3: printSentence(F("They are everywhere.")); break;
            }

        break;

        case 3:
            currentNbOfLines = 5;
            switch(currentLineIndex)
            {
                case 0: printSentence(F("Those big balls.")); break;
                case 1: printSentence(F("I hate them.")); break;
                case 2: extraTextPaddingX = 60; printSentence(F("Grab the pepper spray.")); break;
                case 3: extraTextPaddingX = 60; printSentence(F("And jump the bastards!")); break;
                case 4: printSentence(F("Yeay!")); break;
            }
            
            break;

    }
}
//======================================================================
void DialogManager::printSingleSentence(const __FlashStringHelper * stringSentence, int8 extraPadX)
{
    printSingleSentence( reinterpret_cast<PGM_P>(stringSentence),  extraPadX);
}

//======================================================================
void DialogManager::printSingleSentence(PGM_P stringSentence, int8 extraPadX)
{
    extraTextPaddingX = extraPadX;
    currentTrigger = nullptr;
    printSentence(stringSentence);
}

//======================================================================
void DialogManager::printSentence(const __FlashStringHelper * sentenceString)
{
    printSentence( reinterpret_cast<PGM_P>(sentenceString) );
}

//======================================================================
void DialogManager::printSentence(PGM_P sentenceString)
{
    reset();

    currentSentence = sentenceString;
    currentSentenceSize = getStringLength(sentenceString);
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
    return pgm_read_byte(currentSentence + i);
}