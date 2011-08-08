/**
\file
\author
**/

#ifndef CFModExDriver_HPP_INCLUDED
#define CFModExDriver_HPP_INCLUDED


#include "IAudioDriver.hpp"
#include <FMODex/fmod.h>
#include <FMODex/fmod_errors.h>
#include <boost/shared_ptr.hpp>
#include <list>
#include <map>
#include <vector>
//#include <fusion/core/CSingleton.hpp>

namespace audio {
/**
Fait aussi office de factory avec des fonctions comme create sound

**/
class CSound;



struct SoundBuffer {
    SoundBuffer(FMOD_SOUND* snd = 0) : _sound(snd),references(0) {};

    FMOD_SOUND* getSound() { return _sound;};

    int references;

    ~SoundBuffer() ;

    protected:
        FMOD_SOUND* _sound;
};




class CFModExDriver :
        public IAudioDriver
        //,public fus::CSingleton<CFModExDriver>
{
    //friend class fus::CSingleton<CFModExDriver>;

private:
    FMOD_SYSTEM* _audioSystem;
    //FMOD_CHANNEL *_mainChannel;
    FMOD_CHANNELGROUP *_masterGroup;

//    typedef boost::shared_ptr<CSound> TSound;
//FMOD_SOUND*
    typedef std::map<std::string, SoundBuffer > TLoadedSounds;
    //typedef std::map<FMOD_SOUND*,int> TSoundReferences;
    TLoadedSounds _sounds;
    //TSoundReferences _counters;
//CSound*
//    std::vector< CSound* > _sounds;


protected:
    friend class CSound;
    void decrementCounter(const std::string& filename);

public:

    static bool ERRCHECK(const FMOD_RESULT& result);

    CFModExDriver();
    ~CFModExDriver();

    //const int& maxChannelsNumber
    bool init(const SAudioParameters&);


	void update();
	//void playSound(SoundType type, float *pos, int age = 0);

    /**
    2nd param a vrai si nouveau channel
    **/
	//createSound(filename ,bool);
    bool getFMODExVersion(unsigned int &version) const ;

    ISound* getSound(const char* filename);
    ISound* getMusic(const std::string& filename);

    //bool addMusicToPlaylist(CSound*);

	void stopMusic();
	void pauseGameMusic(const bool&);
	//void setMusicMode(SoundType);
	void setMusicVolume(const float& );
	void setMasterVolume(const float& );
	void getMasterVolume(const float& );
	//void setSoundVolume(const float&);

    //FMOD_SOUND* loadFmodExSound(const char*,const bool& stream);
    FMOD_SYSTEM* getSystem() { return _audioSystem;};


    void collectGarbage();
protected:
    CSound* getFmodExSound(const std::string& filename,const bool& stream) ;
    FMOD_SOUND* loadFmodExSound(const std::string& filename,const bool& stream);

};

}

#endif // CEXPLOSIONS_HPP_INCLUDED
