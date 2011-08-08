/**
* \file
*
*/
//#include <fusion/utilities.hpp>
#include "ISprite.hpp"
#include <algorithm>
#include <irrlicht.h>

using namespace irr;

ISprite::ISprite() :
_horizontal(0),
_vertical(0),
_startFrame(0),
_endFrame(0),
_currentFrame(0),
_frameTime(20),          // en ms
_timeElapsedSinceLastFrame(0)
{
}

//setLoop
void
ISprite::setFrameNumbers(const irr::s32& horizontal,const irr::s32& vertical){

    _horizontal = std::max(1,horizontal);
    _vertical = std::max(1,vertical);
}


ISprite::~ISprite()
{
    //
}



irr::s32
ISprite::getFramesNumber() const {
    return _horizontal*_vertical;
}


void
ISprite::setLoopMode(const irr::s32& start,const irr::s32& end){

//    start =
    //nb de frames
    _startFrame = irr::core::clamp(start,0, getFramesNumber() - 1 );
    _endFrame = irr::core::clamp(end,0, getFramesNumber() - 1 );
    _currentFrame = _startFrame;
}



bool
ISprite::init(video::ITexture* texture,const int& nb_largeur,const int& nb_hauteur){

    //Assert(texture != 0);
// HACK ne fonctionne pas puisque le Assert fais le boulot
    if(texture == 0){
        //ILogger::Log(EWarning) << "No valid texture for the sprite ( texture == NULL )";
        return false;
        //throw SLoadingException(
    }


    _texture = texture;
    // On s'assure que ce soit superieur a 1 (evite division par 0 ensuite)
    setFrameNumbers(nb_largeur,nb_hauteur);
    setLoopMode(0,getFramesNumber()-1);

    // rectangle de base
    _clippingSize.set(_texture->getSize().Width/nb_largeur,_texture->getSize().Height/nb_hauteur);

    return true;
}


 /// TODOO
bool
ISprite::update(const irr::u32& elapsedTime){

    // update time left
    _timeElapsedSinceLastFrame += elapsedTime;

    // if a new frame is to be displayed
    if(_timeElapsedSinceLastFrame >= _frameTime){

        // resets time to wait until next frame
        _timeElapsedSinceLastFrame = 0;



        //// Met a jour le no de frame a afficher
        s32 result = _endFrame - _currentFrame;

        // lecture terminee,reenclenche si repeat ok
        if(result == 0){
            if(!_loop){
                return true;
            }
            _currentFrame = _startFrame;
        }
        // ordre de lecture normal
        else if( result > 0){
            ++_currentFrame;
        }
        else{
            --_currentFrame;
        }
    }

    return false;
}

