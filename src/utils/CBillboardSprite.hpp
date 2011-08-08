#ifndef CBILLBOARDSPRITE_HPP_INCLUDED
#define CBILLBOARDSPRITE_HPP_INCLUDED

#include "ISprite.hpp"


class CBillboardSprite :
public ISprite
{

public:
    CBillboardSprite();
    ~CBillboardSprite();

    bool init(irr::video::ITexture* texture,const irr::s32& nb_largeur,const irr::s32& nb_hauteur);


    void setPosition(const irr::core::vector3df & pos) {
        _node->setPosition(pos);
    };
    bool update(const irr::u32& elapsedTime);

    irr::scene::IBillboardSceneNode* _node;
};

#endif // CBILLBOARDSPRITE_HPP_INCLUDED
