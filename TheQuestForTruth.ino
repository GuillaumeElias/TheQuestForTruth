/**
* The Question For Truth is a game for Arduboy
*/

#include <Arduboy2.h>
#include "MemoryFree.h"

#include "Game.h"

Game game;

//==========================================================
void setup()
{
    game.init();
    Serial.begin(9600); //TODO remove
    
    Serial.print("freeMemory()=");
    Serial.println(freeMemory()); //TODO remove
}

//==========================================================
void loop()
{
    game.update();
}
