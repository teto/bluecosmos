/**
* \file resource_sound.h
http://khayyam.developpez.com/articles/cpp/fmodex/#LIII-2
*/
#include "CSound.hpp"
#include "CFModexDriver.hpp"
#include <fmodex/fmod.h>
#include <fmodex/fmod_errors.h>
#include <boost/assert.hpp>

// static member
//FMOD_SYSTEM* CSound::_audioSystem = 0;

namespace audio {


CSound::CSound(CFModExDriver& driver, FMOD_SOUND *snd, const std::string& filename) :
_channel(0),
_sound(0),
_driver(driver),
_filename(filename)
{
//    BOOST_ASSERT( driver);
    BOOST_ASSERT( snd );

    _sound = snd;
//    assert(system && sound);
    // FMOD_2D signifie qu'il n'y aura pas de traitement 3D
    // LE fmod non blocking prevents framerate from being impacted
    //FMOD_NONBLOCKING |
//    FMOD_System_CreateStream(
//        _audioSystem,
//        filename.c_str(),
//        FMOD_HARDWARE | FMOD_LOOP_OFF | FMOD_2D,
//        0,
//        &_sound
//    );
}

//Destructor
CSound::~CSound(){

    _driver.decrementCounter(_filename);
}



std::string
CSound::getArtist() const {
    FMOD_TAG         tag;
    FMOD_Sound_GetTag(_sound, "ARTIST", 0, &tag);
    std::string s((char*)tag.data);

    return s;
}

/*
récupérer le titre du morceau courant
*/
std::string
CSound::getTitle() const {
    FMOD_TAG         tag;
    FMOD_Sound_GetTag( _sound, "TITLE", 0, &tag);
    std::string s((char*)tag.data);

    return s;
}





void
CSound::play(){

    FMOD_RESULT result = FMOD_System_PlaySound( _driver.getSystem(), FMOD_CHANNEL_FREE, _sound, 0, &_channel);
    CFModExDriver::ERRCHECK(result);
    //return true;
}



bool
CSound::stop(){
    //Fmod_Sound_Release(mSound);
    FMOD_Channel_SetPaused(_channel,true);

    return false;
}

// FMOD_Channel_IsPlaying



void
CSound::SetVolume(const float& volume) const {

    FMOD_Channel_SetVolume(_channel,volume);
    //return false;
}



void
CSound::pause(){
    FMOD_Channel_SetPaused(_channel,true);
    //return false;
}



//en milliseconde
CSound::TTimeUnit
CSound::getLength() const{

    TTimeUnit i;
    FMOD_Sound_GetLength(_sound, &i, FMOD_TIMEUNIT_MS);
    return i;
}



//en milliseconde
CSound::TTimeUnit
CSound::TimeLeft() const {
    TTimeUnit i = getLength() - getCurrentPos();
    //FMOD_Channel_GetPosition(_channel, &i, FMOD_TIMEUNIT_MS);
    return i;
}


CSound::TTimeUnit
CSound::getCurrentPos() const {
    CSound::TTimeUnit i;
    FMOD_Channel_GetPosition( _channel, &i, FMOD_TIMEUNIT_MS  );
    return i;
}

void
CSound::setPosition(const CSound::TTimeUnit& position){

    //CSound::TTimeUnit  length   = getLength();


//    if(current + interval < length)
    // return ?
    FMOD_Channel_SetPosition( _channel, position, FMOD_TIMEUNIT_MS );
}

void
CSound::forwardJump(const CSound::TTimeUnit& interval){
    CSound::TTimeUnit  current  = getCurrentPos();
//    CSound::TTimeUnit  length   = getLength();
    setPosition(current + interval);
//    if(current + interval < length)
//        FMOD_Channel_SetPosition(channel, c+i,FMOD_TIMEUNIT_MS );
}

//void
//CSound::backwardJump(unsigned int i){
//    unsigned int c=getCurrentPos();
//    if(c-i>0)
//        FMOD_Channel_SetPosition(channel, c-i,FMOD_TIMEUNIT_MS );
//}


}
