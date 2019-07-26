#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "abstract/Singleton.h"
#include "Constants.h"

typedef enum __attribute__ ((packed))
{
    PLAYER_HIT,
    ENEMY_HIT
} Sound;

typedef enum __attribute__ ((packed))
{
    MAJOR_THIRD     = 0b10000000, //if not set -> minor
    MINOR_7TH       = 0b01000000,
    MAJOR_7TH       = 0b00100000, //if neither minor or major 7th -> octave
    SUS_2           = 0b00010000,
    SUS_4           = 0b00001000,
    DIMINISHED_5TH  = 0b00000100,
    AUGMENTED_5TH   = 0b00000010,
    SIXTH           = 0b00000001,
} ChordModesMasks;

class SoundManager : public Singleton<SoundManager>
{
    public:
        SoundManager(Arduboy2 * arduboy);
        void init();
        void startMusicForLevel();
        void startMusic(short baseNote = 69, short speed = 10, short noteDuration = 24, short numberOfSequences = 9);
        void resumeMusic();
        void playSound(Sound sound);
        void stopMusic();
        void playNextNote();

    private:
        void gotoNextSequence();
        int8 computePositionInChord();

        void setSpeed(int8 speed);
        ArduboyTones tones;

        int8 nbSequences;
        int8 currentSeqTick;
        int8 currentSequence;
        int8 currentSoundPlaying;

        byte currentChordModes;
        int8 currentBaseMidiNote;
        int8 currentOrderInChord;

        int8 noteDuration;
        int8 sequenceRepeat;
        int8 nbNotesInSequence;

};

#endif
