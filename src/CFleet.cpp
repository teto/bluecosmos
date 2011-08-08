#include "CFleet.hpp"
#include "game_engine.hpp"
#include "entities/player.hpp"
#include "CGraphicalLevel.hpp"
#include "fightingState/CSinglePlayerState.hpp"
#include <fusion/logging/ILogger.hpp>
#include <fusion/maths/macros.hpp>
#include <iostream>
#include "utils/CParticleManager.hpp"
#include "entities/CBullet.hpp"
#include "entities/CStaticBattery.hpp"
#include "entities/CMissile.hpp"
#include "audio/ISound.hpp"


using namespace irr;


CFleet::TDeadPool CFleet::_deadPool;




CFleet::CFleet(CSinglePlayerState* state) :
    _fleetRootNode(0),
    _fightingState(state)
{
    //ctor
    BOOST_ASSERT(_fightingState);
    _fleetRootNode = CGameEngine::instance().scene()->addEmptySceneNode();

}



CFleet::~CFleet()
{
    //dtor
    _fleetRootNode->remove();
    //clearDeadPool();
}




// get nearest missile
CStaticBattery*
CFleet::getNearestEnemy(const TVector3df& position)
{


    CStaticBattery *nextBattery = _activeBatteries.front(), *nearest = _activeBatteries.front();
    CStaticBattery* current = 0;

    //_INFO << "START \r\n";
    while(nextBattery){


        current = nextBattery;
        nextBattery = current->_next;

    }
//    while(j != j_end){
//
//        if(j->getPosition().getDistanceFromSQ( position) < nearestMissile->getPosition().getDistanceFromSQ( position)){
//            nearestMissile = j;
//        }
//        ++j;
//    }
//    return &(*nearestMissile);
    return nearest;
}



CStaticBattery*
CFleet::getNextTarget(const std::list<CStaticBattery*>& trackedBatteries){


    //auto

    /*CStaticBattery *nextBattery = _activeBatteries.front();
    //CStaticBattery* current = 0;

    //_INFO << "START \r\n";
    while(nextBattery){

        TTrackedBatteries::const_iterator it = std::find( trackedBatteries.begin(), trackedBatteries.end(), nextBattery );

        // if battery not already tracked
        if(it == trackedBatteries.end() ){

            return nextBattery;
        }


        nextBattery = nextBattery->_next;

    }*/

    return 0;
}

//void
//CFleet::killEntity(CStaticBattery* ){
//
//}
//




CStaticBattery*
CFleet::getDeadButAllocatedBattery(const NEntityType::EId& type){

    CStaticBattery* battery = 0;
  //  #error not existing
    if( !_deadPool[type].empty() ){

        battery = _deadPool[type].front();
        _deadPool[type].pop_front();
    }
    else {
//        _INFO << "creating from scratch";
        switch(type){

            case NEntityType::Bullet:
                battery = new CBullet();
                break;

            case NEntityType::Battery:
                battery = new CStaticBattery();
                break;

            case NEntityType::Missile:
                battery = new CMissile();
                break;

            default:
                break;
        }
    }

    return battery;
}


void
CFleet::addConfiguredEntityToAliveBatteries(CStaticBattery* battery){

//    battery->_next = _root;
//    _root = battery;

    //_aliveBatteries.push_front( battery );
    battery->setFleet(this);
    battery->_damageInflictedOnCollision = 0;
    _activeBatteries.push_front( battery );
}




void
CFleet::killAllAlive() {

    // TODO les mettre tous en deadPool
}



void
CFleet::destroyAll(){

//static void ();
    clearDeadPool();
    //std::for_each()
}



void
CFleet::clearDeadPool(){


    BOOST_FOREACH(auto& pool, _deadPool){

        pool.clear();
    }

    //std::for_each()
}



CMissile*
CFleet::createAndSetupMissile(const char* model,const TVector3df& forward,const TVector3df& position ) {

    CStaticBattery* battery = getDeadButAllocatedBattery(NEntityType::Missile);
    CMissile* missile = dynamic_cast<CMissile*>(battery);

    missile->setup(model,this,position, forward);

    addConfiguredEntityToAliveBatteries(missile);

    return missile;
}


//,CStaticBattery* creator
//const char* model
CStaticBattery*
CFleet::createAndConfigureStaticBattery()
{

    CStaticBattery* battery = getDeadButAllocatedBattery(NEntityType::Battery);

    BOOST_ASSERT(battery != 0);

    //addBattery(batt);
    addConfiguredEntityToAliveBatteries(battery);


    //_INFO << "auto updated battery created with range" << battery->getParameter(NParameters::Range);
    return battery;
}





CBullet*
CFleet::createAndSetupBullet(const char* model,
                  const float& angleDeg
                  //,
                  //const TVector3df& position
                )
{
//, position
    TVector3df forward(0,0,-0.01);
    getVectorFromAngle(angleDeg,forward);
    return createAndSetupBullet(model, forward);
}






//,const TVector3df& position
CBullet*
CFleet::createAndSetupBullet(const char* model,const TVector3df& forward )
{

    CStaticBattery* battery = getDeadButAllocatedBattery(NEntityType::Bullet);

    BOOST_ASSERT(battery != 0);
    CBullet* bullet = dynamic_cast<CBullet*>(battery);



//TODO remplacer par un init la ?
    bullet->setMesh(model);
    //bullet->setFleet(this);
    bullet->_forward = forward;

/*
    if(!bullet->setup(model,this,position,forward)){
        _LOG_WARNING << "Could not configure bullet";

        // TODO on devrait le remettre dans le pool
        delete bullet;

        return 0;
    }
*/
    // TODO HACK
    //bullet->_parameters

    addConfiguredEntityToAliveBatteries(bullet);

    return bullet;
}





void
CFleet::draw()
{
//    if(_fleetRootNode->isVisible()){
//        _INFO << "fleet nodes set invisible";
//        //_fleetRootNode->setVisible(false);
//    }

//draw2DPolygon (core::position2d< s32 > center, f32 radius, video::SColor color=SColor(100, 255, 255, 255), s32 vertexCount=10)=0
//
//    core::list<ISceneNode*>  const& children = _fleetRootNode->getChildren();
//    irr::scene::ISceneCollisionManager* temp =  _level->_state->scene()->getSceneCollisionManager();
//    core::position2di pos2d;
//
//    //TBulletPool::TElementIterator i(_bullets.begin()),i_end(_bullets.end());
//    //TBulletPool::TElementIterator i(_bullets.begin()),i_end(_bullets.end());
//    core::list<ISceneNode*>::ConstIterator i( children.begin() ),i_end( children.end() );
//    while(i != i_end){
//
//        _level->_state->engine()->driver->setTransform(video::ETS_WORLD,core::IdentityMatrix);
//
//        const core::vector3df& pos3d = (*i)->getAbsolutePosition();
//        //const core::vector3df& rpos3d = (*i)->getPosition();
//        pos2d = temp->getScreenCoordinatesFrom3DPosition ( pos3d );
//        //getCenter()
//        //i->getRange()
//        _level->_state->engine()->driver->draw2DPolygon(pos2d , 10);
//        _INFO << "hitbox displayed. Range .... at pos" << pos2d.X << "/" << pos2d.Y;// << i->getRange();
//        _INFO << "Pos 3D: " << pos3d.X << "/" << pos3d.Y<< "/" << pos3d.Z;// << i->getRange();
//        //_INFO << "Relative Pos 3D: " << rpos3d.X << "/" << rpos3d.Y<< "/" << rpos3d.Z;// << i->getRange();
//        ++i;
//    }

//    TMissilePool::TElementIterator j(_missiles.begin()),j_end(_missiles.end());
//    while(j != j_end){
//
//        ++j;
//    }
}












// apparemment le bug vient pas de cette fct
//,CSinglePlayerState* state
void
CFleet::update(const TTimer::TimeType& time)
{
    //BOOST_ASSERT(state);
/*
    //BOOST_FOR
//    CStaticBattery* nextBattery = front();
//    CStaticBattery* current = 0;

    //CBattery* battery = _activ
    //_INFO << "START \r\n";
    while(nextBattery){


        current = nextBattery;
        nextBattery = current->_next;

        // check conditions of death
        //getDamage ?
        if( current->getRemainingLife() < 0 ){

//          engine()->addExplosion();
//          engine()->addSound();
            current->onDeath();

            killEntity( current );

            _fightingState->addSimpleExplosion( current->getPosition() );
            //CGameEngine::getAudioManager()->Play("sounds/explosion.wav");
//            CSound* sound = new CSound("sounds/explosion.wav");
//            sound->play();
            //state->shakeCamera();

            _INFO << "onDeath : battery damage > 0 => EXPLOSION";
        }
        //battery->timerExpired()
        //_timer.reached
        else if( current->outOfScreenTimeout() ){
         //return true;
            current->onTimeoutDisparition();
            //_INFO << "time out death";
            killEntity( current );

        }
        else {
            //_INFO << "Update \r\n";
            current->update(time);
        }
    }
    */


    bool erasePreviousBattery = false;

    // runs from the end to the beginning



    auto beginBattery( _activeBatteries.begin() );
    auto beforebeginBattery( _activeBatteries.before_begin());
    auto lastBattery( _activeBatteries.end() );



    //auto previousBattery = lastBattery;
    //auto currentBattery = lastBattery;
    auto it = lastBattery;
    //auto battery
    //for ( auto battery( _activeBatteries.begin() ), ; battery != firstBattery; --battery){
    //for ( ; battery != lastBattery;){
     //previousBattery = battery
     // Pas de -- sur les iterators de cette classe
    for( ;it != lastBattery; ++it ){

        auto battery = *it;
        if(erasePreviousBattery){

            //bug potentiel ici
            killEntityNextTo(it);
        }





        // check conditions of death
        if( battery->getRemainingLife() < 0 ){

            battery->onDeath();
            erasePreviousBattery = true;
            //killEntityNextTo( previousBattery );

            _fightingState->addSimpleExplosion( battery->getPosition() );
            //CGameEngine::getAudioManager()->Play("sounds/explosion.wav");
//            CSound* sound = new CSound("sounds/explosion.wav");
//            sound->play();
            //state->shakeCamera();

            _INFO << "onDeath : battery damage > 0 => EXPLOSION";
        }
        //battery->timerExpired()
        //_timer.reached
        else if( battery->outOfScreenTimeout() ){
         //return true;
            battery->onTimeoutDisparition();
            //_INFO << "time out death";
            //killEntity( battery );
            erasePreviousBattery = true;

        }
        else {
            //_INFO << "Update \r\n";
            battery->update(time);
        }



    }


    //_INFO << "END \r\n";
}



void
//CFleet::killEntityNextTo(CStaticBattery* battery) {
CFleet::killEntityNextTo(TBatteryContainer::iterator& it) {

    //BOOST_ASSERT(battery != 0);

//    CStaticBattery* previous = battery->_previous;
    CStaticBattery* battery = *it;

    const NEntityType::EId type = battery->getType();

    if(type == NEntityType::Player ){

        dynamic_cast<CPlayer*>(battery)->kill();
        _INFO << "killing player";
    }
    else {


        _activeBatteries.erase_after(it);
        _deadPool[ type ].push_front(battery);

        // If static battery then
        if( type == NEntityType::Battery){
            // call lua function

            //lua_State* L = ;
            try {
                _INFO << "Killing static battery [" << battery << "]";
                luabind::call_function<void>( _fightingState->_script->getVM(), "killBattery", battery);
            }
            catch(std::exception& e){
                //appellà manager:Killtask()
                //_LOG_ERROR << "call_function from C++ launched an exception" << e.what();
                std::string errorMsg;
                if(!_fightingState->_script->retrieveStringFromStack(errorMsg)){
                    errorMsg = "No string on top of stack";
                }

               // _fightingState->engine()->popupMessage(L"call_function => error " , errorMsg );
            }
        }
    }



}




// TODO  passer un shared_ptr ? ne rien renvoyer
bool
CFleet::checkCollisions(CFleet& fleet){

    //BOOST_ASSERT(fleet != 0);



    auto ally = _activeBatteries.begin();
    auto lastAlly  = _activeBatteries.end();

    // foreach unit from this fleet
    for( ;ally != lastAlly ; ++ally){

        auto enemy = fleet._activeBatteries.begin();
        auto lastEnemy = fleet._activeBatteries.end();

        // foreach unit from adverse fleet
        for(;enemy != lastEnemy; ++ enemy){

            // if both collide
            if( (*enemy)->checkCollision(*ally) ){

                // TODO renommer en ...With
                //_INFO << "collision >> enemy damage before collision [" << enemy->getDamage() << "]";

                (*enemy)->onCollision( *ally );
                (*ally)->onCollision( *enemy );

                //_INFO << "enemy damage after collision [" << enemy->getDamage() << "]";
                return true;
            }

            //enemy = enemy->_next;
        }
        //ally = ally->_next;
    }

/*
    CStaticBattery* ally = front();
    // foreach unit from this fleet
    while(ally){

        CStaticBattery* enemy = fleet.front();

        // foreach unit from adverse fleet
        while(enemy){

            // if both collide
            if( enemy->checkCollision(ally) ){

                // TODO renommer en ...With
                //_INFO << "collision >> enemy damage before collision [" << enemy->getDamage() << "]";

                enemy->onCollision( ally );
                ally->onCollision( enemy );

                //_INFO << "enemy damage after collision [" << enemy->getDamage() << "]";
                return true;
            }

            enemy = enemy->_next;
        }
        ally = ally->_next;
    }
*/
    return false;
}

