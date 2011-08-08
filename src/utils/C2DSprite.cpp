#include "C2DSprite.hpp"

using namespace irr;

//const core::position2d< s32 > &  destPos,
void
C2DSprite::draw(irr::video::IVideoDriver* driver)
{


    //on determine ligne et colonne a afficher
    s32 col  = getCurrentCol();
    s32 line = getCurrentLine();

    core::position2di topLeft(line*_clippingSize.Height,col*_clippingSize.Width);
    core::recti sourceRect(topLeft,topLeft + _clippingSize);


    driver->draw2DImage  ( _texture,
    _position,
    sourceRect,
    0, //dest clipping
    irr::video::SColor(255,255,255,255),    // color
    true
    );

}
