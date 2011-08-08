/**
* \file intro.cpp
**/
#include "CFadingImage.hpp"

#include <fusion/logging/CConsoleLogger.hpp>
#include <iostream>

using namespace irr;
using namespace core;

//! Constructor
//"images/bluecosmos.png"
// Passer la position du sprite dans le constructor
CFadingImage::CFadingImage(
    irr::video::ITexture* texture
) :
//_alpha(0),
_repeat(0),
_texture(texture)
{
    BOOST_ASSERT( texture );
    // color transparent at start
    _color.set(0,255,255,255);
}


CFadingImage::~CFadingImage()
{

}

//    const int& times = 1,
//CFadingImage&
//CFadingImage::operator()(

CFadingImage&
CFadingImage::addFading(
    //const int& value,
    const irr::u32& length,
    const irr::video::SColor& color
)
{
    //
    SFading fading;
    //fading.targetedAlpha = value;
    //fading.delta = value/length;
    fading.timer.setTimer(length);
    fading.targetedColor  = color;
//    fading.times    = times;


    _fadings.push_back(fading);
    return *this;
}


/**** Function Update() ****/
bool
CFadingImage::update(const irr::u32& elapsedTime)
{
    // If no fading registered
    if( _fadings.empty() ){
        return false;
    }

    SFading& fading = _fadings.front();
    //video::SColor color;
    // if max time reached
    fading.timer.update(elapsedTime);
    if( fading.timer.reached() ){
        // set alpha value = target alpha
        //_alpha = fading.targetedAlpha;
        _color = fading.targetedColor;

        // appeler ca repeat ou loop
        if(_repeat){
            // move the 1st element to the last one
// TODO ptet qu'il aya une meilleure maniere de faire ca
            //_INFO << "repeat enabled";
            fading.timer.restart();
            _fadings.push_back( fading );

        }
        // In every case we pop the succeeded one
        _fadings.pop_front();
        //_INFO << "Pop front";
    }


    return true;
};



/**** Function Draw() ****/
void
CFadingImage::draw(irr::video::IVideoDriver *driver)
{

    irr::video::SColor color = _color;
    if(_fadings.size()){
        SFading &fading = _fadings.front();
        color = fading.targetedColor.getInterpolated(_color,fading.timer.getAdvancement());

//        _INFO << "advancement   :" << fading.timer.getAdvancement();
//        _INFO << "time passed   :" << fading.timer.getElapsedTime();

    }


    // Image source clipping
    core::recti  srcRect(irr::core::position2di(0,0), _texture->getOriginalSize());

    // true => enable alpha
     driver->draw2DImage  ( _texture, _position, srcRect, 0, color, true );

}
