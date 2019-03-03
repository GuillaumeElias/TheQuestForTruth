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
        void printSingleSentence(char * charArray, bool readFromPgm = false);

    private:
        void printSentence(char * charArray);
        void printNextLine();
        void reset();
        inline char getChar(short i);

        int8 currentSentenceSize, currentLetterPosition, currentLineIndex, currentNbOfLines;
        int8 letterFrameCounter;
        int8 triggerTextPaddingX;
        Trigger * currentTrigger;
        bool readFromPgmMem;
        
        char * currentSentence;

};



#endif
