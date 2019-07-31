/**
* The Question For Truth is a game for Arduboy
*/

#include <Arduboy2.h>
#include "src/Game.h"

Game game;

//==========================================================
void setup()
{
    game.init();
    randomSeed(analogRead(0));

    Serial.begin(9600); //TODO remove
}

//==========================================================
void loop()
{
    game.update();
}
