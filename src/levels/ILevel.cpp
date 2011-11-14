/**
* \file entity_manager.cpp

* \todo utiliser des tableaux de pointeurs au lieu de switch/case




*/
#include "config.hpp"
#include "CFleet.hpp"
#include "entities/CStaticBattery.hpp"
//#include "enemy.hpp"
#include "entities/player.hpp"
//#include "IGameConfig.hpp"
#include "game_engine.hpp"
#include "CGraphicalLevel.hpp"
#include <algorithm>
#include <fusion/maths/macros.hpp>
#include <cmath>
#include <irrlicht.h>
#include "utils/CBillboardSprite.hpp"
#include <utf8.h>
#include "utils/CParticleManager.hpp"
#include "CSpeaker.hpp"
#include "utils/TClock.hpp"
#include "fightingState/CSinglePlayerState.hpp"
#include <boost/any.hpp>
#include <boost/make_shared.hpp>
//#include "audio/IAudioDriver.hpp"
#include "CSpeech.hpp"
#include <fusion/core/string.hpp>
#include "entities/CModel.hpp"


// Le rapetisser pr les tests
//#define _BC_MAX_ENTITIES 5

using namespace irr;


void
CGraphicalLevel::update( const TTimer::TimeType&) {

}


// TODO rename en addHills et passer l'adresse de texture ?
void
CGraphicalLevel::addLayer() {


    //_INFO << "addLayer not implemented";

    CGameEngine* engine = ENGINE;
    //_world->setParent( scene()->getRootSceneNode() );

//    skybox->getMaterial(0).FogEnable = true;


    //scene()->addLightSceneNode(_world );

//    scene::IAnimatedMesh *cloudMesh = engine->scene()->addHillPlaneMesh  ( "upperLayer",
//       core::dimension2df(100,100)  ,       //tileSize
//       core::dimension2d< u32 > (1,1),         //tileCount
//        0,         //material video::SMaterial *
//        0.0f,         //hillHeight
//        core::dimension2d< f32 >(0.0f, 0.0f),// countHills
//        core::dimension2d< f32 >(1,3) //  textureRepeatCount
//    );
//
//


    scene::IAnimatedMesh *mesh = engine->scene()->addHillPlaneMesh  ( "lowerLayer",
        core::dimension2df(30,30)  ,       //tileSize
        core::dimension2d< u32 > (10,10),         //tileCount
        0,         //material video::SMaterial *
        5.0f,         //hillHeight
        core::dimension2d< f32 >(0.0f, 0.0f),// countHills
        core::dimension2d< f32 >(3,3) //  textureRepeatCount
    );

    _terrain = engine->scene()->addAnimatedMeshSceneNode(mesh);

    //if(_world){
    _terrain->setParent(_world);
    //}

    _terrain->setMaterialFlag( video::EMF_LIGHTING, false);

    _terrain->setPosition( TVector3df(0,-10,0));
    // Sets background
    //_terrain->getMaterial(0).setTexture(
    _terrain->setMaterialTexture(
                0,      // Id
                engine->driver()->getTexture("images/terrain-texture.jpg")
                );
//
//    _layer->setMaterialFlag(video::EMF_LIGHTING, false);
//    _layer->setMaterialTexture(
//                0,      // Id
//                // background
//                engine->driver()->getTexture("images/seamlessSky.png")
//                );

    // Ca renvoie 1 donc un seul material est utilisé
    //_INFO << _terrain->getMaterialCount();

//EMT_TRANSPARENT_ALPHA_CHANNEL
// EMT_TRANSPARENT_ADD_COLOR
// EMT_DETAIL_MAP
//EMT_SOLID_2_LAYER (not implemented in the OGL driver)
//EMT_TRANSPARENT_VERTEX_ALPHA
_terrain->setMaterialType( video::EMT_SOLID );
//_layer->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL );
//
//    _layer->setParent(_world);


    // Create fog
    //EFT_FOG_LINEAR
//    engine()->driver()->setFog(SColor(0,0, 0, 0),
//                             EFT_FOG_LINEAR,    //!< fog type
//                             10               //!< Start
////                             ,100,               //!< end
////                             0.1,              //!< density
////                             false,             //!< pixel fog
////                             false              //!< range fog
//                             );


}


void
CGraphicalLevel::setBackground( const char* pathToSkyDomeTexture) {

    //
    CGameEngine* engine = ENGINE;
    //CGameEngine* engine = engine();

    video::ITexture* texture = engine->driver()->getTexture(pathToSkyDomeTexture);
    _world = engine->scene()->addSkyDomeSceneNode( texture,16,8,0.95f,2.0f);
}





//
//
//void
//CGraphicalLevel::updatePlayerProgress(const float& playerProgress) {
//
//    _upperProgress += playerProgress;
//
//    // TODO if layer
//}






/*
void
CGraphicalLevel::addSpriteExplosion(const core::vector3df &pos) const
{


    //const & pos
    // transformer les coors 3D en 2D
    core::position2di pos2d = _engine->smgr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition (pos);

    //_INFO << "positioin de l'explosion" << pos2d.X << "/" << pos2d.Y;
    CBillboardSprite* sprite = _engine->_spriteManager->addBillboardSprite(
                                        _engine->driver->getTexture("images/explosion.png"),
                                        4,      // x number
                                        3       //y number
                                        );
    //256x192 la taille d'emoticons.png
    //sprite->init(_engine->driver->getTexture("emoticons.png"),4,3);
    sprite->setFrameTime(30);
    sprite->setPosition(pos);


}
*/



//! Constructor
CGraphicalLevel::CGraphicalLevel() :
    _terrain(0),
    _layer(0),
    _world(0)
{

}

//
//CGameEngine* engine
//bool
//CGraphicalLevel::init( CSinglePlayerState* state ){
//
//
//    _fightingState = state;
//    BOOST_ASSERT(_fightingState != 0);
//
//    _alliedFleet = boost::make_shared<CFleet>( _fightingState );
//    _enemyFleet = boost::make_shared<CFleet>( _fightingState );
//
//
//
//    return true;
//}
//


//! Destructor
CGraphicalLevel::~CGraphicalLevel(){
	//std::for_each(mEntities.mElements.begin(),mEntities.mElements.end(),this);

	// TODO supprimer les pointeurs stockées dans CFleet ? sauf le
}


