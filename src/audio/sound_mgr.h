#ifndef __sound_mgr__
#define __sound_mgr__

#include <string>
#include <list>
#include <FMODEX/fmod.h>

class sound_mgr{
    public:
        sound_mgr();
        ~sound_mgr();
        int play(const std::string &);

        std::string getArtist();
        std::string getTitle();
        unsigned int getLength();
        unsigned int getCurrentPos();

        void pause();
        void resume();
        void avancer(unsigned int);
        void reculer(unsigned int);
        void setVolume(float);

        void remove_effects();
        void add_echo(unsigned int);
        void add_filtre(unsigned int, unsigned int);

        void update();
    private:
        FMOD_SYSTEM  *sys;
        FMOD_SOUND   *sound;
        FMOD_CHANNEL *channel;
        FMOD_DSP     *echo;
        FMOD_DSP     *filtre1;
        FMOD_DSP     *filtre2;
};


#endif

