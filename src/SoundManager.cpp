#include "SoundManager.h"


//==========================================================
SoundManager::SoundManager(Arduboy2 * arduboy)
    : tones(arduboy->audio.enabled)
    , playing(false)
    , currentNote(0)
    , currentSequence(0)
    , currentSoundPlaying(0)
    , noteDuration(24)
{
    pinMode(PIN_SPEAKER_1, OUTPUT);
    tones.volumeMode(VOLUME_ALWAYS_NORMAL);
}

//==========================================================
void SoundManager::startMusic(int level)
{

    nbSequences = arraysize(music_1);

    noInterrupts();
    TCCR1A = 0;
    TCCR1B = 0b00001100;
    TIMSK1 = 0b00000010;
    TCNT1 = 0; 

    setSpeed(music_1_speed);

    //set prescaler to 1024
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12) | (1 << CS10); 

    interrupts();

    playing=true;
    playNextNote();
}


//==========================================================
void SoundManager::playSound(Sound sound)
{
    tones.noTone();
    tones.volumeMode(VOLUME_ALWAYS_HIGH);
    currentSoundPlaying = 2;

    switch(sound){
        case PLAYER_HIT:
            tones.tone( 440, 150);
            break;
        case ENEMY_HIT:
            tones.tone( 880, 150);
            break;
    }
}

//==========================================================
void SoundManager::setSpeed(int8 speed)
{
    OCR1A = 15624 / speed;
}

//==========================================================
void SoundManager::stopMusic()
{
    playing=false;
    tones.noTone();
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
    
    if(currentNote >= music_1_nb_notes - 1)
    {
        currentSeqTick++;
        if(currentSeqTick >= music_1_sequences_repeat)
        {
            gotoNextSequence();
        }

        currentNote = 0;
    }
    else
    {
        currentNote++;
    }
    
    int note = music_1[currentSequence][currentNote];

    if(note == 0)
    {
        tones.noTone();
    }
    else
    {
        tones.tone(note, noteDuration);
    }
}

//==========================================================
void SoundManager::gotoNextSequence()
{
    if(currentSequence >= nbSequences - 1)
    {
        currentSequence = 0;
    }
    else
    {
        currentSequence++;
    }
    currentSeqTick = 0;
}

//==========================================================
bool SoundManager::isPlaying() const
{
    return playing;
}

//==========================================================
ISR(TIMER1_COMPA_vect){
    if(SoundManager::instance()->isPlaying())
    {
        SoundManager::instance()->playNextNote();
    }
}