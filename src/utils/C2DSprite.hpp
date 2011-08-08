#ifndef C2DSPRITE_HPP_INCLUDED
#define C2DSPRITE_HPP_INCLUDED

#include "ISprite.hpp"

class C2DSprite :
public ISprite
{
public:
    //bool init(irr::video::ITexture* texture,const irr::s32& nb_largeur,const irr::s32& nb_hauteur);

    void draw(irr::video::IVideoDriver* driver);

    void setPosition(const irr::core::position2di & pos) {
        _position = pos;
    };

public:
    irr::core::position2di _position;
};

#endif // C2DSPRITE_HPP_INCLUDED
