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

class SoundManager : public Singleton<SoundManager>
{
    public:
        SoundManager(Arduboy2 * arduboy);
        void init();
        void startMusic(int level);
        void playSound(Sound sound);

        void stopMusic();

        bool isPlaying() const;
        void playNextNote();

    private:
        void gotoNextSequence();
        void setSpeed(int8 speed);
        bool playing;
        ArduboyTones tones;

        int8 currentNote;
        int8 currentSeqTick;
        int8 currentSequence;
        int8 currentSoundPlaying;

        int8 nbSequences = 9;
        int8 sequenceSpeed = 10;
        int noteDuration;

};

static const int8 music_1_nb_notes = 4;
static const int8 music_1_sequences_repeat = 4;
static const int8 music_1_speed = 10;

static const short music_1[][music_1_nb_notes] = 
{
    {440, 523, 659, 523},
    {440, 523, 698, 523},
    {440, 523, 784, 523},
    {494, 587, 698, 587},
    {494, 587, 659, 587},
    {131, 155, 196, 233},
    {146, 174, 220, 262},
    {174, 208, 262, 311},
    {174, 195, 262, 294}
};





#endif
