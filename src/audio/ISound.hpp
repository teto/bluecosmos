/**
* \file sound.h
* You can read the following tutorial to learn about Fmod: http://lfe.developpez.com/FMODMP3/#L6
*/
#ifndef _ISOUND_HPP_INCLUDED
#define _ISOUND_HPP_INCLUDED

namespace audio {

class ISound
{


public:

    virtual void play() = 0;
    // met en pause
    virtual void pause() = 0;
    // met a la fin
    virtual bool stop() = 0;

//    void setPosition(const TTimeUnit& );
//    void forwardJump(const TTimeUnit& );

//    TTimeUnit TimeLeft() const;
//    //TODO: mettre en statique
//    void SetVolume(const float& volume) const;
//    CSound::TTimeUnit getCurrentPos() const ;
//
//    TTimeUnit getLength() const;
};
}

#endif
