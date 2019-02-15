#include "BoxView.h"
#include "DialogManager.h"

namespace
{
    static const short CINEMATIC_FRAME_MOVE = 5;

    static const short NB_INSTRUCTIONS_SEQ_1 = 40;
    static const short NB_INSTRUCTIONS_SEQ_2 = 40;
    static const short NB_INSTRUCTIONS_SEQ_3 = DIALOG_LETTER_NBFRAMES * 19 + DIALOG_SENTENCE_END_NBFRAMES;     //depends on number of letters in "THE QUEST FOR TRUTH"
    static const short NB_INSTRUCTIONS_SEQ_4 = 80;
    static const short END_SEQ_2 = NB_INSTRUCTIONS_SEQ_1 + NB_INSTRUCTIONS_SEQ_2;
    static const short END_SEQ_3 = NB_INSTRUCTIONS_SEQ_1 + NB_INSTRUCTIONS_SEQ_2 + NB_INSTRUCTIONS_SEQ_3;
    static const short END_SEQ_4 = NB_INSTRUCTIONS_SEQ_1 + NB_INSTRUCTIONS_SEQ_2 + NB_INSTRUCTIONS_SEQ_3 + NB_INSTRUCTIONS_SEQ_4;
}

//====================================================================
BoxView::BoxView()
    :  frameCount(0)
    ,  inscructionNb(0)

    ,  aX(20)
    ,  aY(14)
  
    ,  bX(110)
    ,  bY(14)
  
    ,  cX(20)
    ,  cY(50)
  
    ,  dX(110)
    ,  dY(50)
  
    ,  aaX(0)
    ,  aaY(0)
  
    ,  bbX(128)
    ,  bbY(0)
  
    ,  ccX(0)
    ,  ccY(64)
  
    ,  ddX(128)
    ,  ddY(64)
{
    
}


//====================================================================
void BoxView::update(Arduboy2 * arduboy)
{
    if( arduboy->pressed( UP_BUTTON ) )
    {
        moveUp();
    }    
    else if( arduboy->pressed( DOWN_BUTTON ) )
    {
        moveDown();
    }
    else if( arduboy->pressed( RIGHT_BUTTON ) )
    {
        moveRight();
    }
    else if( arduboy->pressed( LEFT_BUTTON ) )
    {
        moveLeft();
    }

    drawLines(arduboy);
}

//====================================================================
bool BoxView::updateCinematic(Arduboy2 * arduboy)
{
    if(aX < 0)
    {
        return false;
    }

    //SEQUENCE 1
    if(inscructionNb < NB_INSTRUCTIONS_SEQ_1)
    {
        moveDown();
        inscructionNb++;
    }
    //SEQUENCE 3
    else if(inscructionNb >= END_SEQ_2 && inscructionNb < END_SEQ_3)
    {
        if(inscructionNb == END_SEQ_2)
        {
            DialogManager::instance()->printSentence("THE QUEST\nFOR TRUTH");
        }
        else if(inscructionNb == END_SEQ_3 - 1)
        {
            DialogManager::instance()->printSentence("");
        }
        DialogManager::instance()->draw( arduboy );
        inscructionNb++;
    }
    else if(frameCount > CINEMATIC_FRAME_MOVE)
    {
        //SEQUENCE 2
        if(inscructionNb >= NB_INSTRUCTIONS_SEQ_1 && inscructionNb < END_SEQ_2)
        {
            moveUp();
        }
        //SEQUENCE 4
        else if(inscructionNb >= END_SEQ_3 && inscructionNb < END_SEQ_4)
        {
            moveUp();
        }

        inscructionNb++;
        frameCount = 0;
    }
    
    frameCount++;
    drawLines(arduboy);

    return true;
}

//====================================================================
void BoxView::drawLines(Arduboy2 * arduboy)
{
    //inner lines
    arduboy->drawLine(aX, aY, bX, bY);
    arduboy->drawLine(cX, cY, dX, dY);
    arduboy->drawLine(aX, aY, cX, cY);
    arduboy->drawLine(bX, bY, dX, dY);

    //outer lines
    arduboy->drawLine(aaX, aaY, aX, aY);
    arduboy->drawLine(bbX, bbY, bX, bY);
    arduboy->drawLine(ccX, ccY, cX, cY);
    arduboy->drawLine(ddX, ddY, dX, dY);
}

//====================================================================
void BoxView::moveUp()
{
    aX -= 4;
    aY -= 4;
    bX += 4;
    bY -= 4;
    cX -= 4;
    cY += 4;
    dX += 4;
    dY += 4;
}

//====================================================================
void BoxView::moveDown()
{
    aX += 4;
    aY += 4;
    bX -= 4;
    bY += 4;
    cX += 4;
    cY -= 4;
    dX -= 4;
    dY -= 4;
}

//====================================================================
void BoxView::moveLeft()
{
    aX += 4;
    aY += 1;
    aaY += 1;
    cX += 4;
    cY -= 1;
    ccY -= 1;
    
    bX += 4;
    bY -= 1;
    bbY -= 1;
    dX += 4;
    dY += 1;
    ddY += 1;
}

//====================================================================
void BoxView::moveRight()
{
    aX -= 4;
    aY -= 1;
    aaY -= 1;
    cX -= 4;
    cY += 1;
    ccY += 1;
    
    bX -= 4;
    bY += 1;
    bbY += 1;
    dX -= 4;
    dY -= 1;
    ddY -= 1;
}