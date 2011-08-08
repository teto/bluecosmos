/**
* \file sound.h
* You can read the following tutorial to learn about Fmod: http://lfe.developpez.com/FMODMP3/#L6
*/
#ifndef _CSOUND_HPP_INCLUDED
#define _CSOUND_HPP_INCLUDED

#include <fmodex/fmod.h>
#include <fmodex/fmod_errors.h>
#include <string>
#include <boost/noncopyable.hpp>
#include "ISound.hpp"

namespace audio {

class CFModExDriver;

// http://matthieu-brucher.developpez.com/tutoriels/cpp/boost/smartptrs/#LVI
class CSound : public ISound,
               public boost::noncopyable
{

protected:
    FMOD_CHANNEL *_channel;

    std::string _filename;
    FMOD_SOUND   *_sound;

    CFModExDriver& _driver;
    typedef unsigned int TTimeUnit;

public:
    // TODO fonction Clone ?

    //static FMOD_SYSTEM  *_audioSystem;
//FMOD_SYSTEM *system,
    CSound( CFModExDriver& driver,  FMOD_SOUND *snd, const std::string& filename);
    ~CSound();

    void play();
    // met en pause
    void pause();
    // met a la fin
    bool stop();

    void setPosition(const TTimeUnit& );
    void forwardJump(const TTimeUnit& );

    TTimeUnit TimeLeft() const;
    //TODO: mettre en statique
    void SetVolume(const float& volume) const;
    CSound::TTimeUnit getCurrentPos() const ;

    TTimeUnit getLength() const;

    const std::string& getFilename() const { return _filename;} ;
    std::string getTitle() const ;
    std::string getArtist() const ;
};

}

#endif
