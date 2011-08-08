/**
\file
\author
**/
#ifndef IAudioDriver_HPP_INCLUDED
#define IAudioDriver_HPP_INCLUDED


#include "SAudioParameters.hpp"

namespace audio {


class ISound;
class SAudioParameters;


class IAudioDriver
{
public:

    //IAudioDriver();
    //virtual ~IAudioDriver();


    virtual bool init(const SAudioParameters&) = 0;


	virtual void update() = 0;
//
//	virtual void stopMusic() = 0;
//	virtual void pauseGameMusic(const bool&) = 0;
//	virtual void setMusicVolume(const float&) = 0;
    virtual void collectGarbage() {};
    virtual ISound* getSound(const char*) { return 0;};
protected:
    SAudioParameters _parameters;
};

} //!end of 'audio' namespace

#endif // CEXPLOSIONS_HPP_INCLUDED
