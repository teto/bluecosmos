#include "CSpriteManager.hpp"
//#include "../game_engine.hpp"
#include "C2DSprite.hpp"
#include "CBillboardSprite.hpp"
#include <irrlicht.h>


using namespace irr;

CSpriteManager::CSpriteManager(irr::IrrlichtDevice * device) :
_device(device)
{
    //ctor

}

CSpriteManager::~CSpriteManager()
{
    //dtor
}



C2DSprite*
CSpriteManager::add2Dsprite(irr::video::ITexture* texture,const irr::s32& nb_largeur,const irr::s32& nb_hauteur,const bool& autoUpdated)
{
    //
    C2DSprite* sprite = new C2DSprite();
    sprite->init(texture,nb_largeur,nb_hauteur);

//    //
//    if(autoUpdated){
//        _sprites.push_back(sprite);
//    }
    return sprite;
}



CBillboardSprite*
CSpriteManager::addBillboardSprite(irr::video::ITexture* texture,const irr::s32& nb_largeur,const irr::s32& nb_hauteur)
{
    CBillboardSprite* sprite = new CBillboardSprite();
    // surtt ne pas inverser les 2 lignes qui suivent sinon crash !!
    sprite->_node = _device->getSceneManager()->addBillboardSceneNode();
    sprite->init(texture,nb_largeur,nb_hauteur);

    //_sprites.push_back(sprite);
    return sprite;
}

//void
//CSpriteManager::addSprite(ISprite* sprite,const bool& loop){
//
//    //_sprites.push_back(std::make_pair(sprite,loop));
//    // TODO verifier que c'est pas nul
//    sprite->enableLoop(loop);
//    _sprites.push_back(sprite);
//
////    ISceneNode
////    IBillboardSceneNode*
////    addBillboardSceneNode (ISceneNode *parent=0,
////    const core::dimension2d< f32 > &size=core::dimension2d< f32 >(10.0f, 10.0f),
////    const core::vector3df &position=core::vector3df(0, 0, 0),
////    s32 id=-1, video::SColor colorTop=0xFFFFFFFF,
////    video::SColor colorBottom=0xFFFFFFFF);
//
//// lui associer un texture animator
////ESNAT_TEXTURE
////ItextureAnimator
//}

/*
void
CSpriteManager::update(const irr::u32& elapsedTime){
    // si jamais on veut redimensionner les sprites
    //engine->driver->enableMaterial2D();
    //irr::u32 elapsedTime = _engine->getElapsedTime();
    for(TSpritesMap::iterator i( _sprites.begin() ), end(_sprites.end());i != end;++i){

        ISprite* sprite = *i;

        // si explosion terminee
        if(sprite->update(elapsedTime )){
            delete sprite;
            i = _sprites.erase(i);
            continue;
        }

    }
    //engine->driver->enableMaterial2D(false);
}

void
CSpriteManager::draw2Dsprites()
{
    for(TSpritesMap::iterator i = _sprites.begin();i != _sprites.end();++i){

        ISprite* sprite = *i;
        sprite->draw( _device->getVideoDriver() );
    }
}
*/
