/**
* \file entity_bullet.cpp
* Fichier dans dossier "engine"


mEnemy.Init(CRunner::GetInstance()->GetBatteryModel(mModelIterator->first),0);


*/
#include "CStatiCBattery.hpp"
#include <fusion/logging/ILogger.hpp>
#include "../CGraphicalLevel.hpp"
#include "../config.hpp"
#include "../game_engine.hpp"
#include "CMissile.hpp"
#include "CBullet.hpp"
#include "../CFleet.hpp"
#include <cmath>


//onPeacefulDeath()
//
//onCombatDeath()
using namespace irr;


// TO allow override of "tostring" lua operator
//TODO je pourrai mm ajouter un const
std::ostream&
operator<<(std::ostream& os, const CStaticBattery& battery) {
//&battery <<
    os << &battery;
    return os;
}



/// Constructor   _lvlMgr(0),CFleet* fleet
CStaticBattery::CStaticBattery() :
//_timer( conf::_BC_BULLET_LIFETIME_MS ),
_node(0),
_fleet(0),
_next(0),
_numberOfFramesSinceOutOfScreen(0),
_damageInflictedOnCollision(0),
_previous(0),
_range(0),
_bonus(0),
_life(0),
_rotationSpeed(conf::DEFAULT_ROTATION_SPEED),
_target(0),
_withinScreen(true)
//: _collision(false),_id(0),_node(0),_range(0),_destroyed(false)
{



    irr::scene::ISceneManager* smgr = ENGINE->scene();


    //if(!_node){

    // Add node even if no mesh loaded
    _node = smgr->addAnimatedMeshSceneNode( 0,  // fleet
                                            0,   // parent
                                            -1, //id
                                            core::vector3df(0, 0, 0),   //position
                                            core::vector3df(0, 0, 0), //rotation
                                            core::vector3df(1.0f, 1.0f, 1.0f), // scale
                                            true        // add node even without mesh
                                            );


    //reset();
    // Par defaut
}




//destructor
CStaticBattery::~CStaticBattery(){

    // Remove from a list
    //removeFromList();
}


void
//CStaticBattery::
    getVectorFromAngle(const float& angle,irr::core::vector3df& vectorToRotate)
{
    //angle = normalizeAngle(angle);
    vectorToRotate.rotateXZBy ( angle );
}






CBullet*
//CStaticBattery*
CStaticBattery::shootBullet(const char* model,const float& deviation) {


    CBullet* bullet = getFleet()->createAndSetupBullet(model, this->getRotation().Y + deviation);
    bullet->setPosition( this->getPosition() );
    //bullet->
    return bullet;
}


void
CStaticBattery::setup(
            //const char* model,
            const float& range,
            const int& life,
            const int& damage,
            const int& bonus
        )
{

    //setMesh(model);

    _range = range;
    _life = life;
    _damageInflictedOnCollision = damage;
    _bonus = bonus;

    setWithinScreen(false);
    _numberOfFramesSinceOutOfScreen = 0;

}




//
void
CStaticBattery::updateRotation() {

    //const float maxDelta = 5.f;

    //
    TVector3df rotationDelta = computeAnglesToFaceBattery( this->_target );

    //_LOG_WARNING << rotationDelta;
//maxDelta
    rotationDelta.Y = irr::core::clamp(rotationDelta.Y, - _rotationSpeed , _rotationSpeed );
    //rotationDelta.Y = 5;
  //      _INFO << "rotation delta after clamp : " << rotationDelta.Y;
    TVector3df newRotation = rotationDelta + getRotation() ;
    //newRotation.Y = fmodf(newRotation.Y,360.f);
    setRotation( newRotation );

    //_INFO << "rotation" << getRotation().Y;
        //rotationToDirection (const vector3d< T > &forwards=vector3d< T >(0, 0, 1)) const
    //_forward = getRotation().rotationToDirection ();

}




TVector3df
//float
CStaticBattery::computeAnglesToFaceBattery(CStaticBattery* target) const {

    BOOST_ASSERT(target);

//    // If no target returns
//    if(target == 0) {
//        return 0;
//    }


//rotation.Y = fmodf(rotation.Y,360.f);
    //else compute new rotation
    const TVector3df toTarget( target->getPosition() - this->getPosition() );

    //Get the rotations that would make a (0,0,1) direction vector point
    //in the same direction as this direction vector.
    TVector3df horizontalAngle = toTarget.getHorizontalAngle();

    // HACK TO suppress once model finished
    horizontalAngle.X = 0;

    //getRotation().Y = fmodf(getRotation().Y, 360.f);

    //_INFO << "toTarget angle" << horizontalAngle.Y << "/ship getRotation" <<this->getRotation();
    // clamp values

//
//TVector3df temp =
    //fmodf(this->getRotation().Y,360)
    // en fait y a juste le Y qui nous intéresse ?
    TVector3df rotationDelta = horizontalAngle - this->getRotation() ;

   // _INFO << "Y delta " << rotationDelta;
    if(rotationDelta.Y > 180.f){

        rotationDelta.Y -= 360.f;
    }
    else if(rotationDelta.Y < -180.f){
        rotationDelta.Y += 360.f;
    }
    return ( rotationDelta );
//        _INFO << "rotation delta: " << rotationDelta.Y ;

}


//bool
//CStaticBattery::operator==(const CStaticBattery& other) const {
//    _LOG_WARNING << "OPERATOR CALLED";
//    return true;
//}




void
CStaticBattery::exportPositionToLua(lua_State* L) const {

    const TVector3df& pos = getPosition();
    lua_pushnumber(L, pos.X);
    lua_pushnumber(L, pos.Y);
    lua_pushnumber(L, pos.Z);
}



//std::string
//CStaticBattery::concat(std::string& str1,std::string& str2) const {
//    return "Battery test";
//}


float normalizeAngle(const float& angle)
{
    float newAngle = angle;
    while (newAngle < 0) {
        newAngle += 360.f;
    }
    while (newAngle > 360) {
        newAngle -= 360.f;
    }
    return newAngle;
}





void
CStaticBattery::setRotation( const TVector3df& rotation ) {

    TVector3df temp = rotation;
    //_INFO << "Avant fmodf" << temp.Y;
    //temp.Y = fmodf(rotation.Y,360.f);
    temp.Y =  normalizeAngle(rotation.Y);
    //_INFO << "Apres fmodf" << temp.Y;

    _node->setRotation( temp );
}




TVector3df
CStaticBattery::predictPositionIn(const TTimeUnit& futureDelay) const {

    return getPosition() + computeLastFrameSpeedVector()*futureDelay;
}




/// Update position
/// return true quand il doit etre tue
bool
CStaticBattery::update(const TTimer::TimeType& elapsedTime){


    if(! _withinScreen){
        // TODO alors on lance un timer !
//        _timer += elapsedTime;
        ++_numberOfFramesSinceOutOfScreen;
    }



 // TODO mettre ca ailleurss dans une autre fonction
    // check if it's still within screen
    const TVector3df& pos = getPosition();

    // TODO Ne pas le faire  faire a ttes les frames
    if( (pos.X > conf::_X_MAX) || (pos.X < conf::_X_MIN) ) {
        setWithinScreen(false);
    }
    else if( (pos.Z > conf::_Z_MAX) || (pos.Z < conf::_Z_MIN) ){
        //_withinScreen = false;
        setWithinScreen(false);
    }
    else {
        setWithinScreen(true);
        _numberOfFramesSinceOutOfScreen=0;
    }


    return false;
}




void
CStaticBattery::onCollision(CStaticBattery* battery) {
//battery->getRange()
    /// TODO HACK Plus le range est grand plus il inflige de degats
    addDamage( 3 );
}




bool
CStaticBattery::checkCollision(CStaticBattery* battery){

    float distance = battery->getPosition().getDistanceFromSQ(this->getPosition() );

//    _INFO << "this range:" << this->getRange();
//    _INFO << "battery range:" << battery->getRange();

    return (distance < _FUSION_POW2(this->getRange() + battery->getRange()));
}



void
CStaticBattery::addTrackingBattery(CStaticBattery* missile)
{
    //
    _INFO << "Battery [" << this << "tracked by [" << missile << "]";
    _trackingMissiles.push_back(missile);
}





void
CStaticBattery::removeTrackingBattery(CStaticBattery* missile)
{
    //
    _INFO << "Missile [" << missile << "] removed";
    _trackingMissiles.remove(missile);
}




void
CStaticBattery::kill(){

    //
    //unlink();

    // inform tracking missiles that this battery doesn't exist anymore
    if(_trackingMissiles.size() ){

        TMissileList::iterator i(_trackingMissiles.begin()),end(_trackingMissiles.begin());
        for(;i != end;++i)
        {
            (*i)->setTarget(0);
            //_targetedBy->setTarget(0);
        }

    }

    // remove itself from tracking batteries
    if(_target){
        _target->removeTrackingBattery(this);
    }

    // met a jour le reste
    _node->setVisible(false);
}






void
CStaticBattery::setTarget(CStaticBattery* battery){

    _INFO << "Missile tracking battery [" << battery << "]";
// mettre un animator followsplien
    if(battery){

        // If already tracking an entity
        if(_target){
            _LOG_WARNING << "Already has a target [" << _target << "]";
            // Tells this entity it is not tracked anymore by this missile
            _target->removeTrackingBattery(this);
        }

        _target = battery;
        //_vitesse.set(50,0,-50);
        battery->addTrackingBattery(this);
    }
    else {
        _LOG_WARNING << "Target battery == null";
    }
}





void
CStaticBattery::translate(const float& x,const float& y ,const float& z) {

    /*BOOST_ASSERT(_node);

    // A mettre en mode DEBUG seulement
    if(!_node){
        _LOG_ERROR << "No node registered for this object";
        //_previousPos = getPosition();
    }
    else {
        */
    _previousPos = getPosition();
    _node->setPosition( _previousPos + TVector3df(x,y,z) );
    //}
}


//
bool
CStaticBattery::outOfScreenTimeout() const {
    return false;
}



void
CStaticBattery::setFleet( CFleet* fleet ) {
    _fleet = fleet;
    //_node->setParent( fleet->_fleetRootNode );
}




// TODO a optimiser
void
CStaticBattery::setMesh( const char* pathToModel) {

    //BOOST_ASSERT(pathToModel);

    irr::scene::IAnimatedMesh* mesh = ENGINE->scene()->getMesh( pathToModel );

    if(!mesh){
        _LOG_ERROR << "could not load mesh [" << pathToModel << "]";
        return;
    }
    else {
        _node->setMesh(  mesh );
    }


    _node->setVisible(true);
}



void
CStaticBattery::setPosition(const TVector3df& newPos) {

    //_node->.set(x,y,z);
    BOOST_ASSERT(_node);

    // A mettre en mode DEBUG seulement
    if(!_node){
        _LOG_ERROR << "No node registered for this object";
        //_previousPos = getPosition();
    }
    else {
        _previousPos = getPosition();
        _node->setPosition( newPos );
    }
}




void
CStaticBattery::addDamage(const int& damage) {

    _life -= damage;
};


//TODO supprimer et remplacer par setup ?
//void
//CStaticBattery::reset(){
//
//
//    _damageInflictedOnCollision = 0;
//    //_timer.setTimer( conf::_BC_BULLET_LIFETIME_MS );
//
//    if(_node){
//        //_node->drop(); // TODO do a remove avant
//        //_node->remove();
//        //_node = 0;
//    }
//
//}




void
CStaticBattery::setWithinScreen(const bool& value){
    _withinScreen = value;

}


void
CStaticBattery::onTimeoutDisparition(){

    _node->setVisible(false);
}



void
CStaticBattery::onDeath(){
    //_fleet->killEntity(this);
    _node->setVisible(false);
}




