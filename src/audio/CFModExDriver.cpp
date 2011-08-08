#include "CFModExDriver.hpp"
#include "CSound.hpp"
#include "SAudioParameters.hpp"

//#include <fusion/logging/ILogger.hpp>
#include <fusion/fusion.hpp>

namespace audio {

SoundBuffer::~SoundBuffer() {


    if( references > 0){
        // TODO alors y a des erreurs
        _LOG_WARNING << "sound still used [" << references << "] times";
    }
    //
    else {
        _INFO << "Releasing sound";

        // Release sound
//        FMOD_Sound_Release(_sound);
    }
}

//Cette fonction callback sera branchée sur l'évènement "fin d'un son" par
//FMOD_Channel_SetCallback(channel, FMOD_CHANNEL_CALLBACKTYPE_END,  onEnd, 0);
CFModExDriver::CFModExDriver() :
_audioSystem(0),
//_mainChannel(0),
_masterGroup(0)
{
    //ctor

}



ISound*
CFModExDriver::getMusic(const std::string& filename) {
    return getFmodExSound(filename,true);
}


// supprimer de l'exterieur
void
CFModExDriver::decrementCounter(const std::string& filename){

    TLoadedSounds::iterator i = _sounds.find( filename );

    BOOST_ASSERT( i != _sounds.end() );
    // If
    i->second.references--;
}

//void
//CFModExDriver::incrementCounter(const std::string& filename){
//
//}


CSound*
CFModExDriver::getFmodExSound(const std::string& filename,const bool& stream) {

    FMOD_SOUND* resultingSound = 0;

    TLoadedSounds::iterator i = _sounds.find( filename );

/*
    for(TLoadedSounds::iterator i(_sounds.begin()),end(_sounds.end()); i != end; ++i){
        if( i->second.sound == _sounds.end() ){

    }
*/
    // If
    if( i == _sounds.end() ){

        _INFO << "Sound [" << filename << "] not loaded yet";

        resultingSound = loadFmodExSound( filename, false );

        if( ! resultingSound ){
            //return i->second;
            _LOG_ERROR << "Could not load sound [" << filename << "]";
            return 0;
        }
        else {

            //i =
            _INFO << "Audio file [" << filename << "] loaded";
            std::pair<TLoadedSounds::iterator,bool> result = _sounds.insert( std::make_pair( filename, SoundBuffer(resultingSound) ) ) ;
            i = result.first;
        }
    }
    else {

        i->second.references++;
    }



    CSound* sound = new CSound( *this, i->second.getSound(), filename );
    // Adds a reference toward the sound
    return sound ;
}



ISound*
CFModExDriver::getSound(const char* filename) {
    return getFmodExSound( std::string(filename),false);
}



void
//CFModExDriver::flushLoadedSounds() {
CFModExDriver::collectGarbage() {

    for(TLoadedSounds::iterator i(_sounds.begin()),end(_sounds.end()); i != end; ++i){

        if( i->second.references <= 0 ){

            // Releaser le son
            _INFO << "Erasing sound [" << i->first << "]";
            _sounds.erase(i);
        }
    }
}


//CSound*
FMOD_SOUND*
CFModExDriver::loadFmodExSound(const std::string& filename,const bool& stream){

    FMOD_SOUND* tempSound;
    FMOD_RESULT result;

    // Flags by default
    FMOD_MODE mode = FMOD_HARDWARE | FMOD_LOOP_OFF | FMOD_2D;

    // FMOD_System_CreateStream == FMOD_System_CreateSound with flag FMOD_CREATESTREAM
    if(stream){

        mode |=  FMOD_CREATESTREAM ;
    }

    result = FMOD_System_CreateSound(
            _audioSystem,
            filename.c_str(),
            mode,
            0,
            &tempSound
        );

    // If could not load sound
    if(ERRCHECK(result)) {

        return 0;
    }

//FMOD_3D FMOD_2D
    // else create sound
    //CSound* sound = new CSound(this, tempSound);
    return tempSound;

}

void
CFModExDriver::pauseGameMusic(const bool&){


}

// MuteEverything
//FMOD_ChannelGroup_SetMute( masterGroup, true)
//FMOD_ChannelGroup_SetMute

void
CFModExDriver::stopMusic() {

}



bool
CFModExDriver::ERRCHECK(const FMOD_RESULT& result)
{
    if (result != FMOD_OK)
    {
        _LOG_ERROR << "FMOD error! " <<  result << FMOD_ErrorString(result);
        return true;
    }
    return false;
}


void
CFModExDriver::setMusicVolume(const float& volume){
    // FMOD_Channel / float
    //FMOD_Channel_SetVolume( _mainChannel, volume);
}


void
CFModExDriver::setMasterVolume(const float& volume){
    // FMOD_Channel / float
    // can try overrideVolume too
    FMOD_ChannelGroup_SetVolume(_masterGroup, volume);

}


CFModExDriver::~CFModExDriver()
{


    //dtor
    FMOD_System_Close(_audioSystem);
    FMOD_System_Release(_audioSystem);
}



void
CFModExDriver::update()
{
    FMOD_System_Update(_audioSystem);
}


bool
CFModExDriver::getFMODExVersion(unsigned int &version) const {
    //FMOD_System_GetVersion(system, &version);
    return ERRCHECK( FMOD_System_GetVersion(_audioSystem, &version) );
}



//const int& maxChannelsNumber
bool
CFModExDriver::init(const SAudioParameters&)
{

    const int maxChannelsNumber = 4;
    FMOD_RESULT result;

    result = FMOD_System_Create(&_audioSystem);

    if(result != FMOD_OK){

        //fus::ILogger::Log(fus::EWarning)
        _LOG_WARNING << "Impossible to initialize FmodEx : " << FMOD_ErrorString(result);
        return false;
    }


    unsigned int version = 0;
    getFMODExVersion(version);

    // check version is correct
    if (version < FMOD_VERSION) {
        _LOG_WARNING << "Error!  You are using an old version of FMOD " << version << ".  This program requires " << FMOD_VERSION;
        return false;
    }

    result = FMOD_System_Init(_audioSystem, maxChannelsNumber, FMOD_INIT_NORMAL, NULL);

    if(result != FMOD_OK){

        //fus::ILogger::Log(fus::EWarning)
        _LOG_WARNING << "Impossible to init audio system : " << FMOD_ErrorString(result);
        return false;
    }
    //Specify user callbacks for FMOD's internal file manipulation functions.
//        result = _audioSystem->setFileSystem(&fmodFileOpenCallback, &fmodFileCloseCallback, &fmodFileReadCallback, &fmodFileSeekCallback, 2048);
//        if (result != FMOD_OK){
//
//        }


    // update var static
    //CSound::_audioSystem = _audioSystem;

    // TODO Parametrer le volume

    FMOD_System_GetMasterChannelGroup( _audioSystem, &_masterGroup);


    // TODO
    //FMOD_System_createChannelGroup()

    //fus::ILogger::Log(fus::ENotice)
    _INFO  << "Sound System ok";
    return true;

}

}
