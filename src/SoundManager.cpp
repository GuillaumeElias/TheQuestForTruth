#include "SoundManager.h"
#include "drawable/Map.h"


//==========================================================
SoundManager::SoundManager(Arduboy2 * arduboy)
    : tones(arduboy->audio.enabled)
    , nbSequences(9)
    , currentSeqTick(0)
    , currentSequence(0)
    , currentSoundPlaying(0)
    , currentChordModes(0)
    , currentBaseMidiNote(0)
    , currentOrderInChord(0)
    , noteDuration(24)
    , sequenceRepeat(4)
    , nbNotesInSequence(4)
{
    pinMode(PIN_SPEAKER_1, OUTPUT);
    tones.volumeMode(VOLUME_ALWAYS_NORMAL);
}

//==========================================================
void SoundManager::startMusicForLevel()
{
    /*switch(Map::instance()->getCurrentLevel())
    {
        case 0:
        case 1:
    } TODO finish off
    */
    startMusic();
}

//==========================================================
void SoundManager::startMusic(short baseNote, short speed, short noteDuration, short numberOfSequences)
{

    this->currentBaseMidiNote = baseNote;
    this->currentOrderInChord = 0;
    this->noteDuration = noteDuration;
    this->nbSequences = numberOfSequences;
    this->currentSpeed = speed;
    this->currentSeqTick = 0;
    //TODO set sequenceRepeat to random

    //set up timer 1
    TCCR1A = 0;
    TCCR1B = 0b00001100;
    TIMSK1 = 0b00000010;
    TCNT1 = 0; 

    setSpeed(speed);

    //set prescaler to 1024
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12) | (1 << CS10); 

    interrupts();
}


//==========================================================
void SoundManager::playSound(Sound sound)
{
    tones.volumeMode(VOLUME_ALWAYS_HIGH);
    currentSoundPlaying = 1;

    switch(sound){
        case PLAYER_HIT:
            tones.tone( 440, 150);
            break;
        case PLAYER_FIRE:
            tones.tone(40,100);
            break;
        case HAPPY_SOUND:
            tones.tone(880, 120, 1175, 120, 1318 , 250);
            break;
        case UP:
            tones.tone(880,50);
            break;
        case DOWN:
            tones.tone(440,50);
            break;
        case OK:
            tones.tone(1318,50);
            break;
        case LETTER:
            tones.tone(1760,5);
            break;
        case DEATH:
            currentSoundPlaying = 5;
            tones.tone(120, 200, 110, 200, 100 , 200);
    }
}

//==========================================================
void SoundManager::setSpeed(int8 speed)
{
    OCR1A = 15624 / speed;
}

//==========================================================
void SoundManager::startNoteBurst()
{
    currentSeqTick = 0x7F;
}

//==========================================================
void SoundManager::stopMusic()
{
    //turn timer off
    TIMSK1 = 0x0; 
    //interrupts();
}

//==========================================================
void SoundManager::resumeMusic()
{
    //turn timer back on
    TIMSK1 = 0b00000010;
    //interrupts();
}

//==========================================================
void SoundManager::playNextNote()
{
    if(currentSoundPlaying > 0 )
    {
        currentSoundPlaying--;
        if(currentSoundPlaying == 0)
        {
            tones.volumeMode(VOLUME_ALWAYS_NORMAL);
        }
        return;
    }

    if(currentSeqTick == 0x7F)
    {
        currentSeqTick = -4;
        setSpeed(20);
    }

    if(currentSeqTick < 0) //if in note burst mode
    {
        currentSeqTick++;
        playNote(currentBaseMidiNote + 8 - abs(currentSeqTick));
        if(currentSeqTick == 0)
        {
            setSpeed(currentSpeed);
        }
        return;
    }
    
    
    if(currentOrderInChord >= nbNotesInSequence - 1)
    {
        currentSeqTick++;
        if(currentSeqTick >= sequenceRepeat)
        {
            gotoNextSequence();
        }

        currentOrderInChord = 0;
    }
    else
    {
        currentOrderInChord++;
    }
    
    int noteMidi = currentBaseMidiNote + computePositionInChord();
    playNote(noteMidi);
    
}

//==========================================================
void SoundManager::playNote(short midiNote)
{
    uint16_t noteHz = 440 * pow(2, ((midiNote - 69)/12.0));
    tones.tone(noteHz, noteDuration);
}

//==========================================================
void SoundManager::gotoNextSequence()
{
    if(currentSequence >= nbSequences - 1)
    {
        currentSequence = 0;
        currentChordModes = 0x00;
        currentBaseMidiNote = random(24, 74);
    }
    else
    {
        currentSequence++;

        short randomBit = random(0,7);

        if(random(0,3) == 0)
        {
            currentChordModes = 0; //reset modes every 1/3
        }
        else
        {
            currentChordModes ^= 1 << randomBit;
        }

        if(currentSequence % 2)
        {
            currentBaseMidiNote += random(0,3) * 2 - 3;
        }
    }
    currentSeqTick = 0;
}

//==========================================================
int8 SoundManager::computePositionInChord()
{
    switch(currentOrderInChord)
    {
        case 0: //root
            return 0;

        case 1: //third
            if(currentChordModes & SUS_2) return 2;
            if(currentChordModes & SUS_4) return 5;
            if(currentChordModes & MAJOR_THIRD) return 4;
            return 3;

        case 2: //fifth
            if(currentChordModes & DIMINISHED_5TH) return 6;
            if(currentChordModes & AUGMENTED_5TH) return 8;
            return 7;

        case 3: //seventh or octave
            if(currentChordModes & SIXTH) return 9;
            if(currentChordModes & MINOR_7TH) return 10;
            if(currentChordModes & MAJOR_7TH) return 11;
            return 12;
    }
}

//==========================================================
ISR(TIMER1_COMPA_vect)
{ 
    SoundManager::instance()->playNextNote();
}


