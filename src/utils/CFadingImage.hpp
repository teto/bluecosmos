/**
* \file intro.h
*/

#ifndef CFADINGIMAGE_HPP
#define CFADINGIMAGE_HPP


#include <irrlicht.h>
#include <list>
#include "TClock.hpp"

//Fadein time § fadeout time
//addFading(-255,time),
//bool repeat

// Prendre en compte la position
class CFadingImage
{

public:
// overallTime in millisecond
    CFadingImage(irr::video::ITexture* texture);
    ~CFadingImage();

/**
\param Alpha value desired for the image
\param Length in milliseconds
\param
\param

\return
**/


    CFadingImage&
    addFading(
               //const int& value = 255,
               const irr::u32& length = 2000,
               const irr::video::SColor& = irr::video::SColor(255,255,255,255)
               );

    bool update(const irr::u32& elapsedTime);
    void draw(irr::video::IVideoDriver *driver);

// est-ce que l'image est -en boucle
    bool _repeat;
    irr::core::position2di _position;
    //float _alpha;

protected:

    struct SFading {
    //int targetedAlpha;    //targeted alpha value
    //float delta;
    TTimer timer;
    //int times;
    irr::video::SColor targetedColor;
    };

    typedef std::list<SFading> TFadings;
    TFadings _fadings;

    irr::video::ITexture* _texture;
    irr::video::SColor _color;

//    irr::u32 mTimeLeft;    //milliseconds
//    TTimer* _timer;
    //TTimer timer;


};

#endif
