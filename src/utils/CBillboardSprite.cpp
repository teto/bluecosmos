#include "CBillboardSprite.hpp"
#include <fusion/logging/ILogger.hpp>

using namespace irr;

CBillboardSprite::CBillboardSprite() :
_node(0)
{
}

CBillboardSprite::~CBillboardSprite()
{
    _node->remove();
}

bool
CBillboardSprite::init(irr::video::ITexture* texture,const irr::s32& nb_largeur,const irr::s32& nb_hauteur)
{
    // il faut initialiser le _node public
    // parametrise le materiau du billboard
    if(!ISprite::init(texture,nb_largeur,nb_hauteur)){
        return false;
    }
    _node->setMaterialTexture (0, texture);
    _node->setSize( core::dimension2df(3,3) );
    _node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL) ;
    _node->setMaterialFlag(video::EMF_LIGHTING ,false);
    //irr::video::SMaterial& material =
    core::matrix4& mat = _node->getMaterial(0).getTextureMatrix(0);
    mat[8] = 0.f;
    mat[9] = 0.f;
    mat[0] = (1.f/nb_largeur);
    mat[1] = 0;
    mat[4] = 0;
    mat[5] = (1.f/nb_hauteur);
    //_node->setTextureMatrix ()


    //matrix.setScale (irr::core::vector3df( 2*(1.f/nb_largeur),(1.f/nb_hauteur),0));
    return true;
}

bool
CBillboardSprite::update(const irr::u32& elapsedTime) {

    core::matrix4& mat = _node->getMaterial(0).getTextureMatrix(0);
//,
    // upper left u/v
    //*_texture->getSize().Width
    //*_texture->getSize().Height
    mat[8] = (irr::f32)getCurrentLine()/(irr::f32)_horizontal;
    mat[9] = (irr::f32)getCurrentCol() /(irr::f32)_vertical;
    //_INFO << "sprite updated" << mat[8] << "/" << mat[9];
    //upper right decalage u/v (tjrs le mm)
//    mat[0] = (1.f/_horizontal);
//    mat[1] = 0;
//    //
//    mat[4] = 0;
//    mat[5] = (1.f/nb_hauteur);

    //buildTextureTransform()
    s32 col  = getCurrentCol();
    s32 line = getCurrentLine();

//_currentFrame
//    core::matrix4& matrix = _node->getMaterial(0).getTextureMatrix(0);
	//_node->vertices[1].TCoords.set()
//ISceneNode*

    //_clippingSize.Width,_clippingSize.Height
    //matrix.setTextureTranslate(0.25f,0.33f);
    return ISprite::update(elapsedTime);
}
// dans fct update
//
