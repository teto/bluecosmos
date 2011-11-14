/**
* \file entity_manager.cpp

* \todo utiliser des tableaux de pointeurs au lieu de switch/case




*/
#include "config.hpp"
#include "CFleet.hpp"
#include "entities/CStaticBattery.hpp"
//#include "enemy.hpp"
#include "entities/player.hpp"
#include "IGameConfig.hpp"
#include "game_engine.hpp"
#include "CLevel.hpp"
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
#include "audio/CFModExDriver.hpp"
#include "CSpeech.hpp"
#include <fusion/core/string.hpp>
#include "entities/CModel.hpp"


// Le rapetisser pr les tests
//#define _BC_MAX_ENTITIES 5

using namespace irr;


float
CLevel::getUpperProgression() const {
    //return smgr->getActiveCamera()->getPosition().Z;
    return _upperProgress;
}


float
CLevel::getLowerProgression() const {
    //return smgr->getActiveCamera()->getPosition().Z;
    return _lowerProgress;
}



CModel*
CLevel::createBatteryModel(const char* filename,const int& life,const int& bonus,const float& range)
{


}

CStaticBattery*
CLevel::getNextTarget()
{
    //
    //if(_enemyFleet.){
// TBulletPool::TElementIterator
    // TODO return 0 if liste empty
        return 0;
        //&(*_enemyFleet._staticBatteries.begin() );
    //}
    //return 0;
}


void
CLevel::addAlly(CStaticBattery* battery) {
    _alliedFleet->addConfiguredEntityToAliveBatteries(battery);
}


// TODO rename en addHills et passer l'adresse de texture ?
void
CLevel::addLayer() {


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
CLevel::setBackground( const char* pathToSkyDomeTexture) {

    //
    CGameEngine* engine = ENGINE;
    //CGameEngine* engine = engine();

    video::ITexture* texture = engine->driver()->getTexture(pathToSkyDomeTexture);
    _world = engine->scene()->addSkyDomeSceneNode( texture,16,8,0.95f,2.0f);
}



CSpeaker*
CLevel::createActor(const std::string& name,const std::string& file)
{
    //get texture
    video::ITexture* texture = ENGINE->driver()->getTexture(file.c_str());

    // convert it into wide charcter
    std::wstring wname;
    utf8::utf8to16(name.begin(),name.end(), std::back_inserter(wname) );
    _actors.push_back(new CSpeaker( wname,texture) );
    return _actors.back();
}


CSpeech*
CLevel::createSpeech(const std::string& message,const std::string& audioFilename){

    CSound* sound = 0;

    if( audioFilename.size() ){
        _LOG_DEBUG << "Loading audio filename [" << audioFilename << "]";
        sound = CGameEngine::getSoundManager()->getSound( audioFilename );
    }

    std::wstring temp;
    fus::convertIntoWideString(message, temp);

    CSpeech* speech = new CSpeech( temp, sound );
    return speech;
}




void
CLevel::getVectorFromAngle(const float& angle,irr::core::vector3df& vectorToRotate)
{
    vectorToRotate.rotateXZBy ( angle );
}





void
CLevel::updatePlayerProgress(const float& playerProgress) {

    _upperProgress += playerProgress;

    // TODO if layer
}


// TODO deplacer ca dans lua
//const float& playerAdv,
void
CLevel::update(const TTimer::TimeType& elapsedTime, CSinglePlayerState* _state){

    //_enemyFleet->update(elapsedTime, _state );
    //_alliedFleet->update(elapsedTime, _state );


    // COLLISION: Entre le joueur et la flotte adverse
    // (cas à part pr l'instant)
    _alliedFleet->checkCollisions( *_enemyFleet);
    //collided = _enemyFleet->checkCollisions(3,getPlayer()->getPosition());

    // IF terrain registered
    if(_terrain != 0){
        //_terrain->getMaterial(0).getTextureMatrix(0).setTextureTranslate(0.f,-percievedSpeed/10.f);
    }

//    _layer->getMaterial(0).getTextureMatrix(0).setTextureTranslate(0.f,-percievedSpeed);


/*
    if(collided){
        //_INFO << "COLLISION avec joueur !!";
        // TODO

        addExplosion( getPlayer()->getPosition() );

        getPlayer()->_stats.addKill(collided);
        getPlayer()->kill();
        //getPlayer()->updateStats(collided);
        updateState();
    }
*/

}



/*
void
CLevel::addSpriteExplosion(const core::vector3df &pos) const
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
CLevel::CLevel() :
    _terrain(0),
    _layer(0),
    _world(0)
{

    _upperProgress = 0;
    //_lowerProgress = 200000;

}

//CSinglePlayerState* state
//CGameEngine* engine
bool
CLevel::init( ){

    //_state = state;

    //BOOST_ASSERT(_state != 0);

    _alliedFleet = boost::make_shared<CFleet>( );
    _enemyFleet = boost::make_shared<CFleet>( );



    return true;
}



//! Destructor
CLevel::~CLevel(){
	//std::for_each(mEntities.mElements.begin(),mEntities.mElements.end(),this);

	// TODO supprimer les pointeurs stockées dans CFleet ? sauf le
}


