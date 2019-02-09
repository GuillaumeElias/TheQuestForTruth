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

    private:
        void printNextLine();
        void printSentence(char * charArray);
        int8 currentSentenceSize, currentLetterPosition, currentLineIndex, currentNbOfLines;
        int8 letterFrameCounter;
        Trigger * currentTrigger;
        
        char * currentSentence;

};



#endif
