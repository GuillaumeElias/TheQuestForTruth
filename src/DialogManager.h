#ifndef _DIALOG_MANAGER_H_
#define _DIALOG_MANAGER_H_

#include <Arduboy2.h>
#include "abstract/Singleton.h"
#include "abstract/Drawable.h"
#include "Trigger.h"

class DialogManager : public Singleton<DialogManager>, public Drawable
{
    public: 
        DialogManager();

        void draw( Arduboy2 * arduboy) override;

        void printTextForTrigger(Trigger * trigger);
        void printTextNb(int8 dialogNb);
        void printSingleSentence(__FlashStringHelper * stringSentence, int8 extraTextPaddingX = 0);
        void printSingleSentence(PGM_P sentenceString, int8 extraTextPaddingX = 0);

    private:
        void printSentence(__FlashStringHelper * stringSentence);
        void printSentence(PGM_P stringSentence);
        void printNextLineForTrigger();
        void reset();
        inline char getChar(short i);

        int8 currentSentenceSize, currentLetterPosition, currentLineIndex, currentNbOfLines;
        int8 letterFrameCounter;
        int8 extraTextPaddingX;
        Trigger * currentTrigger;
        
        PGM_P currentSentence;

};



#endif
