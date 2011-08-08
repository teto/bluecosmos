/**
\file
\author
**/
#ifndef ISOUNDMANAGER_HPP_INCLUDED
#define ISOUNDMANAGER_HPP_INCLUDED


#include "ISoundManager.hpp"
#include <fusion/core/CSingleton.hpp>


namespace audio {

enum EDriverType {
Null,
Fmodex,
OpenAl
};



class CSoundManager :
    public ISoundManager,
    public fus::CSingleton<CFModExDriver>
{
public:

    CSoundManager();
    //virtual ~CSoundManager();


    virtual bool init(const SAudioParameters&) = 0;


	virtual void update() = 0;

	virtual void stopMusic() = 0;
	virtual void pauseGameMusic(const bool&) = 0;

	virtual void setMusicVolume(const float&) = 0;


	//virtual void playSound(SoundType type, float *pos, int age = 0) = 0;
	//virtual void setSoundVolume(const float&) = 0;
//	virtual void setMusicIndex(int) = 0;
//	virtual void nextMusicIndex() = 0;
//virtual void setMusicMode(SoundType) = 0;
    //virtual ISound* loadSound(const char*,const bool&) = 0;


protected:

};

} //!end of 'audio' namespace

#endif // CEXPLOSIONS_HPP_INCLUDED
