#include "CBullet.hpp"
#include "../game_engine.hpp"
#include "../config.hpp"

CBullet::CBullet() : CStaticBattery()
{
    //ctor
    //irr::scene::ISceneManager* smgr = CGameEngine::getInstance()->smgr;
    //_mesh = smgr->addAnimatedMeshSceneNode( smgr->getMesh("models/missile.obj") );

}

CBullet::~CBullet()
{
    //dtor
}




bool
CBullet::update(const TTimer::TimeType& elapsedTime){

    //_position += elapsedTime*_forward;

    //_INFO << "update" << _node->getPosition().Z;
    setPosition( getPosition() + elapsedTime*_forward);

    return CStaticBattery::update(elapsedTime);
}
