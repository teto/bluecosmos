/*
*
* \file entity_player.cpp
*/
#include "player.hpp"
#include "../CGraphicalLevel.hpp"
#include "../config.hpp"
#include "../CFleet.hpp"
#include "CMissile.hpp"
#include "CBullet.hpp"
#include <fusion/logging/CConsoleLogger.hpp>
#include <fusion/maths/macros.hpp>
#include <fusion/macros.hpp>
#include <algorithm> // for min/max
#include "../game_engine.hpp"
#include "../events/CBindCollection.hpp"
#include "../utils/CParticleManager.hpp"
#include <utf8.h>
#include <boost/circular_buffer.hpp>
#include "IMultiModeTransformer.hpp"
#include "../events/CBindCollection.hpp"
#include "../events/CPlayerInputCache.hpp"

//#define _PLAYER_DEFAULT_MODE Fighter

using namespace irr;
using namespace core;
using namespace scene;
using namespace NPlayerInput;


#define IS_ACTIVE(x) _cachedInput->isActive(x)

const NWalkyrieModes::ERealMode CPlayer::_virtualModes[2][3] =
{
    {
        NWalkyrieModes::yf19_Fighter,
        NWalkyrieModes::yf19_Gerwalk,
        NWalkyrieModes::yf19_Battloid
    }
    ,
    {
        NWalkyrieModes::yf21_Fighter,
        NWalkyrieModes::yf21_Gerwalk,
        NWalkyrieModes::yf21_Battloid
    }
};

//fus::CMD5Object* object,const irr::core::vector3df& pos
/// Constructor mTargetedPitch(0),
//CGameEngine* engine,boost::shared_ptr<
CPlayer::CPlayer( ) :
_livesLeft( conf::_DEFAULT_LIVES ),
_cannonHeat(0),
_blinksCounter(0),
_coolingDown(false),
_leftBooster(0),
_rightBooster(0),
_missilesLeft( conf::_DEFAULT_STOCK_OF_MISSILES),
_trackedMissile(0)
, _fightingState(0)
, CStaticBattery::CStaticBattery()
//, _mappingSet(mapping)
, CSpeaker::CSpeaker(L"Player",0)
, _engine( CGameEngine::instance() )
//, static_cast<TModeId>(CPlayer::Fighter)
//IMultiModeTransformer::IMultiModeTransformer(node )

{
    _LOG_DEBUG << "construction du joueur";
    //BOOST_ASSERT(_engine);

    // -- set mapping
    //setMapping(mapping);
    _mappingSet = new TMappingSet();
    //_cachedInput = _mappingSet->generateCache();
    _cachedInput = new TPlayerInputCache();

    irr::scene::ISceneManager* smgr = _engine.scene();

    // -- set representation
    IAnimatedMesh* mesh = smgr->getMesh( conf::_YF19_MESH_FILENAME);
    BOOST_ASSERT(mesh);


    //_walkyrieModel = NWalkyrieModel::YF19;
    IAnimatedMeshSceneNode * animatedNode = smgr->addAnimatedMeshSceneNode( mesh );
    _walkyrie.reset( new IMultiModeTransformer( animatedNode, NWalkyrieModes::yf19_Fighter ) );

    // -- to be compatible with CStaticBattery
    this->_node =  _walkyrie->_animatedNode;

    //_binds.reset( new CBindCollection() );

    // setup binds
/*    _mappingSet.setup( NPlayerInput::MoveRight, ETapMode::Pressed );

            .addBind(NPlayerInput::MoveLeft,ETapMode::Repeat,10)
            .addBind(NPlayerInput::MoveForward,ETapMode::Repeat,10)
            .addBind(NPlayerInput::MoveBackward,ETapMode::Repeat,10)
            .addBind(NPlayerInput::MainShoot)
            .addBind(NPlayerInput::SecondShoot)
            .addBind(NPlayerInput::QuickMainShoot,ETapMode::DoubleTap,100)
            .addBind(NPlayerInput::QuickSecondShoot,ETapMode::DoubleTap,100)
            .addBind(NPlayerInput::ModeUp)
            .addBind(NPlayerInput::ModeDown)
            */
            ;

    // Wil setup mode
    setupAsModel( NWalkyrieModel::YF19 );



//    getSpecs(Fighter).processMoveFunction = &CPlayer::processFighterMoves;
//    getSpecs(Gerwalk).processMoveFunction = &CPlayer::processGerwalkMoves;
//    getSpecs(Battloid).processMoveFunction = &CPlayer::processBattloidMoves;


    // assign elapsed times
    _elapsedTimes.fill(0);
}


//void
//CPlayer::addAlly(CStaticBattery* battery) {
//    _alliedFleet->addConfiguredEntityToAliveBatteries(battery);
//}



void
CPlayer::updateInput(){

    //CEventManager::_timer->getTime()
    //_mappingSet.updateSnapshot( _cachedInput );
    //_mappingSet->updateCache( CGameEngine::instance().device()->getTimer()->getTime(), CGameEngine::instance().getInputManager(), _cachedInput );

}


//CFleet* enemyFleet
bool
CPlayer::trackNewBattery() {

    //CStaticBattery* battery = ->getNearestEnemy( this->getPosition() );
// TODO
/*
    //
    CStaticBattery* battery = _level->_enemyFleet->getNextTarget( _trackedBatteries );

    if(battery == 0){
        _LOG_WARNING << "could not find a battery to shoot missile to";

        return false;
    }
    else {

//            // TODO fonction, get Upward direction Forward vector
            TVector3df forward = CGraphicalLevel::getPlayerForwardVector();
            //forward.X = 0.2;
            const TVector3df position = this->getPosition();

            CMissile* missile = _fleet->createAndSetupMissile("models/missile.obj", forward, position);

            missile->setTarget( battery );
//            _INFO << "Missile created";

        // Launch missile !
        _trackedBatteries.push_back(battery);
        return true;
    }
    */

}


bool
CPlayer::startTrackingEnemies() {

    _INFO << "starts tracking enemies";

    // sort batteries by their
    _targeting = true;
    _trackedBatteries.clear();

    return trackNewBattery();
}


bool
CPlayer::stopTrackingEnemies() {


    _INFO << "stop tracking enemies";
    _targeting = false;
    //_trackedBatteries.clear();
    //return false;
}

    ////////////////////////////////////////////////////////////////////////////
    /// IF button is pressed
    ////////////////////////////////////////////////////////////////////////////
//        _INFO << "ends targeting enemy, prepare to fire";
//
//        // HAck
//        CStaticBattery* battery = _level->_enemyFleet->getNearestEnemy( this->getPosition() );
//
//        if(battery){
//
//            // TODO fonction, get Upward direction Forward vector
//            TVector3df forward = CGraphicalLevel::getPlayerForwardVector();
//            //forward.X = 0.2;
//            const TVector3df position = this->getPosition();
//
//            CMissile* missile = _fleet->createAndSetupMissile("models/missile.obj", forward, position);
//
//            missile->setTarget( battery );
//            _INFO << "Missile created";
//        }
//        else {
//
//            _INFO << "No battery to fire missiles at !";
//        }
//    }
    //
// CEventManager::_timer->getTime()
// _cachedInput.getMapping( SecondShoot ).checkState()
//

void
CPlayer::processShootings()
{

//
 //&& (_elapsedTimes[SinceLastShot] > 10 )
    if( IS_ACTIVE(MainShoot) ) {

        // selon le modeshoot()
        _INFO << "mainShoot : cooling down" << coolingDown();
        if(!coolingDown()){
            FirePrimaryShot();
        }

        //bind->isDown()

    }

/// ENORME HACK !! TODO faut mettre un repeat de 0
//.isDown()
    if( IS_ACTIVE(SecondShoot) ) {

        _INFO << "Missile bind activated";

        // Means key was already pressed the precedent frame
        if( !isTrackingEnemies() ){

            //
            startTrackingEnemies();
        }
        // Player starts targeting enemies
        else {
            const bool effect = trackNewBattery();
            // If no battery left to aim at, stop firing missiles
            if(!effect){
                stopTrackingEnemies();
            }

        }
    }
    else if( isTrackingEnemies() ){
        stopTrackingEnemies();
    }
//
//
//    // end targeting enemy
//   else if( isTrackingEnemies() ){
//        // Do nothing
//
//
//        // HAc
//        //stopTrackingEnemies();
//    }
//    // bind not activated and not tracking enemies
//    else {
//
//        // nothing to do
//        //_INFO << "ends targeting enemy, prepare to fire";
//        stopTrackingEnemies();
//    }
    //&& (_elapsedTimes[SinceLastMissile] > 50)){


}



CGameEngine&
CPlayer::engine() const {
    return _engine;
}



bool
//CPlayer::setTransformerModel( IMultiModeTransformer* transformer ){
// Passer les boosters name,nom du mesh
//CPlayer::setTransformerModel(irr::scene::ISceneManager* smgr, const NWalkyrieModel::EId& id) {
CPlayer::setTransformerModel(const char* meshFilename, const char* leftBoosterName,const char* rightBoosterName) {


    scene::IAnimatedMesh* mesh = 0;

    mesh = engine().scene()->getMesh( meshFilename );

    if(!mesh){
        _LOG_ERROR << "could not load mesh [" << meshFilename << "]" ;
        return false;
    }

    _node->setMesh( mesh );
    _node->getMaterial(0).Lighting = false;

    irr::scene::IBoneSceneNode* leftBoosterBone = 0;
    irr::scene::IBoneSceneNode* rightBoosterBone = 0;

    // Ca bug ici
    //leftBoosterBone = _node->getJointNode( leftBoosterName );
    //rightBoosterBone = _node->getJointNode( rightBoosterName );


    if(leftBoosterBone){
        _leftBooster->setParent( leftBoosterBone );
    }
    else {
        _LOG_WARNING << "Bone [" << leftBoosterName << "] not found ";
    }


    if(rightBoosterBone){
        _rightBooster->setParent( rightBoosterBone );
    }
    else {
        _LOG_WARNING << "Bone [" << rightBoosterName << "] not found ";
    }


    return true;
}



void
CPlayer::setupAsModel( const NWalkyrieModel::EId& id ){

    // TODO
    //_walkyrie->clearModes();


//    if(id == _walkyrieType){
//        _LOG_WARNING << "Trying to set identical player model" << _walkyrieType;
//        return;
//    }


    _LOG_DEBUG << "setup model as [" << id << "]";

    if(id == NWalkyrieModel::YF19){

        //
        setTransformerModel( conf::_YF19_MESH_FILENAME, conf::_YF19_BOOSTER_LEFT_NAME, conf::_YF19_BOOSTER_RIGHT_NAME);
    }
    else {

        setTransformerModel( conf::_YF21_MESH_FILENAME, conf::_YF21_BOOSTER_LEFT_NAME, conf::_YF21_BOOSTER_RIGHT_NAME);
    }

    _walkyrieType = id;


// Clear Mode aller chercher le mode actuel
    clearModes(NWalkyrieModes::Fighter);

    allowMode(NWalkyrieModes::Fighter );
    allowMode(NWalkyrieModes::Gerwalk);
    allowMode(NWalkyrieModes::Battloid);




    // -- can always transform
    _walkyrie->enableCyclicTransformation(true);
}


//void
//CPlayer::setupAsYF21(){
//
//}


void
CPlayer::clearModes(const NWalkyrieModes::EVirtualMode& mode){

    _walkyrie->clearModes( _virtualModes[ _walkyrieType ][ mode ] );
}




// TODO renommer en addMode
void
CPlayer::allowMode(const NWalkyrieModes::EVirtualMode& mode){

    _walkyrie->allowMode( _virtualModes [ _walkyrieType ][ mode ] );
}




void
CPlayer::onCollision(CStaticBattery* battery) {
    CStaticBattery::onCollision(battery);
    _INFO << "Player collided";
}




void
CPlayer::onTimeoutDisparition(){

    // todo ne rien faire ?
}



void
CPlayer::onDeath(){

    _INFO << "Player died from collision";

}



// TODO revoir cette fonction qui devrait normalement marcher out of the box
// l'adpater existe deja pour std::string
/*
void
CPlayer::getMappingDescription(lua_State* L,const int& id)
{
    int correctedId = id;//std::min(10, std::max(0,id));
//
//    LIMIT_RANGE(correctedId,NPlayerInput::MoveLeft,NPlayerInput::Count);
//    std::string temp;
//    std::wstring wtemp( _cachedInput.getMapping(correctedId).generateDescription().c_str() );
//    utf8::utf16to8(wtemp.begin(),wtemp.end(), std::back_inserter(temp) );

    //lua_pushstring(L,temp.c_str());
}
*/


SStats::SStats() :
Destroyed(0),
Score(0),
Deaths(0),
NbOfTransformations(0)
{
    //PlayedTimes.assign(0);
}



void
SStats::addKill(CStaticBattery* battery)
{
    //
    Score += battery->getBonus();
    ++Destroyed;
}



//SStats::update
//bool
//CPlayer::addDamage(const int&)
//{
////    // can harm player only if alive
////    if(_state == NState::Alive){
////        //add damages
////    }
//
//    kill();
//    return false;
//}



// TODO a renommer en kill
void
CPlayer::kill()
{
    --_livesLeft;
    //++_stats.Deaths;
    _damageInflictedOnCollision = 0;

    if(_livesLeft >= 0){
        // triggers blinking mechanism
        _blinksCounter = conf::_PLAYER_BLINKS;
    }
    //return _livesLeft;
}







// TODO getCruiseSpeed
float
CPlayer::getCruiseSpeed()
{

    float speed = _walkyrie->getSpeed(SModeDescription::DefaultForward);
    // Ne tient pas compte du modifier
    speed -= IS_ACTIVE(NPlayerInput::MoveBackward) * _walkyrie->getSpeed(SModeDescription::Backward);
    speed += IS_ACTIVE(NPlayerInput::MoveForward) * _walkyrie->getSpeed(SModeDescription::Forward);
    return ( speed );
}



// TODO pr l'instant on se concentre sur le
// Passer en parametre le modificator ?
void
CPlayer::processFighterMoves(){

//    _INFO << "processing fighter moves";
    float modifier = 1;
    // todo Ca devra etre defini ailleurs ca
    float yAngleLimit = 0.f,zAngleLimit = 0.f;
    //getCurrentSpecs().ZAngle;
    _walkyrie->getAngleLimits(yAngleLimit,zAngleLimit);


    // If moving to the left
    if( IS_ACTIVE(NPlayerInput::MoveLeft) ){
        //_INFO  << "spin left" << _rotation.Y << "\nPith Yaw speed" <<getCurrentSpecs().Speed[SModeDescription::Yaw];
        _rotation.Z += _walkyrie->getSpeed(SModeDescription::Roll);
        _rotation.Z = std::min( zAngleLimit, _rotation.Z);

        _currentPos.X -=  modifier*_walkyrie->getSpeed(SModeDescription::Lateral);
        _currentPos.X =  std::max(_currentPos.X,-conf::_X_MAX);
    }
    // If moving to the right
    else if( IS_ACTIVE(NPlayerInput::MoveRight ) ){


        _rotation.Z -= _walkyrie->getSpeed(SModeDescription::Roll);
        _rotation.Z = std::max( -zAngleLimit, _rotation.Z);

        _currentPos.X +=  modifier*_walkyrie->getSpeed(SModeDescription::Lateral);
        _currentPos.X =  std::min(_currentPos.X, conf::_X_MAX);
//        _INFO  << "spin right" << _rotation.Y;// << "\nPith Yaw speed" <<getCurrentSpecs().Speed[SModeDescription::Yaw];
    }
    // if rotated to the left but without moving
    else if( _rotation.Z < 0 ){
        _rotation.Z += conf::_BACKSPEED_MODIFICATOR * _walkyrie->getSpeed(SModeDescription::Roll);
        _rotation.Z = std::min(0.f, _rotation.Z);

    }
    else if( _rotation.Z > 0 ){
        _rotation.Z -= conf::_BACKSPEED_MODIFICATOR * _walkyrie->getSpeed(SModeDescription::Roll);
        _rotation.Z = std::max(0.f, _rotation.Z);

    }

    if ( IS_ACTIVE( MoveForward) ){
        _currentPos.Z += modifier * _walkyrie->getSpeed(SModeDescription::Forward);
        _currentPos.Z = std::min(_currentPos.Z, conf::_Z_MAX);
    }
    else if( IS_ACTIVE( MoveBackward ) ) {
        _currentPos.Z -= modifier * _walkyrie->getSpeed(SModeDescription::Forward);
        _currentPos.Z = std::max(_currentPos.Z, conf::_Z_MIN);
    }

}



void
CPlayer::processGerwalkMoves(){

    //_INFO << "processing gerwalk moves";
    float modifier = 1;
    float zAngleLimit = _walkyrie->getYawLimit();


    // If moving to the left
    if( IS_ACTIVE( NPlayerInput::MoveLeft ) ){
        //_INFO  << "spin left" << _rotation.Y << "\nPith Yaw speed" <<getCurrentSpecs().Speed[SModeDescription::Yaw];
        _rotation.Y -= _walkyrie->getSpeed(SModeDescription::Yaw);
        _rotation.Y = std::max( -zAngleLimit, _rotation.Y);

        _currentPos.X -=  modifier*_walkyrie->getSpeed(SModeDescription::Lateral);
        _currentPos.X =  std::max(_currentPos.X,-conf::_X_MAX);
    }
    // If moving to the right
    else if( IS_ACTIVE(NPlayerInput::MoveRight ) ){


        _rotation.Y += _walkyrie->getSpeed(SModeDescription::Yaw);
        _rotation.Y = std::min( zAngleLimit, _rotation.Y);

        _currentPos.X +=  modifier*_walkyrie->getSpeed(SModeDescription::Lateral);
        _currentPos.X =  std::min(_currentPos.X, conf::_X_MAX);
//        _INFO  << "spin right" << _rotation.Y;// << "\nPith Yaw speed" <<getCurrentSpecs().Speed[SModeDescription::Yaw];
    }
    // if rotated to the left but without moving
    else if( _rotation.Y < 0 ){
        _rotation.Y += conf::_BACKSPEED_MODIFICATOR * _walkyrie->getSpeed(SModeDescription::Yaw);
        _rotation.Y = std::min(0.f, _rotation.Y);

    }
    else if( _rotation.Y > 0 ){
        _rotation.Y -= conf::_BACKSPEED_MODIFICATOR * _walkyrie->getSpeed(SModeDescription::Yaw);
        _rotation.Y = std::max(0.f, _rotation.Y);

    }


    if ( IS_ACTIVE(NPlayerInput::MoveForward) ){
        _currentPos.Z += modifier * _walkyrie->getSpeed(SModeDescription::Forward);
        _currentPos.Z = std::min(_currentPos.Z, conf::_Z_MAX);
    }
    else if( IS_ACTIVE(NPlayerInput::MoveBackward) ){
        _currentPos.Z -= modifier * _walkyrie->getSpeed(SModeDescription::Forward);
        _currentPos.Z = std::max(_currentPos.Z, conf::_Z_MIN);
    }
}



// TODO est-ce qu'il doit etre en train d'appuyer pr que ca marche ?
void
CPlayer::processBattloidMoves(){

    float zAngleLimit = _walkyrie->getYawLimit();
    float trackedAngle = 0;
    float modifier = 1;
    float delta = _walkyrie->getSpeed(SModeDescription::Yaw);

    // Si le vaisseau est en train de tracker un missile
    // alors faut l'orienter vers ce missile
    if(_trackedMissile){

//vector3d< T >
        TVector3df direction = _trackedMissile->getPosition() - this->getPosition();;
        TVector3df trackedAngles = direction.getHorizontalAngle () ;

        _INFO << "horizontal angle" << "/" << (90-trackedAngles.Y);
            //<< "/" << temp.Z;
        trackedAngle = trackedAngles.Y;
        delta *= sign(trackedAngle);
        _INFO << "delta" << delta;
        // trackedAngle compris entre - et + YANgle
        //LIMIT_RANGE(trackedAngle, -getCurrentSpecs().YAngle,getCurrentSpecs().YAngle);
//
//        _rotation = _previousRotation;
        _rotation.Y += delta;
    }



    // If moving to the left
    if( IS_ACTIVE( NPlayerInput::MoveLeft ) ){
        //_INFO  << "spin left" << _rotation.Y << "\nPith Yaw speed" <<getCurrentSpecs().Speed[SModeDescription::Yaw];
        if(_trackedMissile == 0){
            _rotation.Y -= delta;//getCurrentSpecs().Speed[SModeDescription::Yaw];
            _rotation.Y = std::max( -zAngleLimit, _rotation.Y);
        }

        _currentPos.X -=  modifier*_walkyrie->getSpeed(SModeDescription::Lateral);
        _currentPos.X =  std::max(_currentPos.X,-conf::_X_MAX);
    }
    // If moving to the right
    else if( IS_ACTIVE( NPlayerInput::MoveRight ) ){

        if(_trackedMissile == 0){
            _rotation.Y += delta;
            _rotation.Y = std::min( zAngleLimit, _rotation.Y);
        }


        _currentPos.X +=  modifier*_walkyrie->getSpeed(SModeDescription::Lateral);
        _currentPos.X =  std::min(_currentPos.X, conf::_X_MAX);
//        _INFO  << "spin right" << _rotation.Y;// << "\nPith Yaw speed" <<getCurrentSpecs().Speed[SModeDescription::Yaw];
    }
    // if rotated to the left but without moving
    else if( _rotation.Y < trackedAngle ){
        _rotation.Y += conf::_BACKSPEED_MODIFICATOR * _walkyrie->getSpeed(SModeDescription::Yaw);
        _rotation.Y = std::min(trackedAngle, _rotation.Y);

    }
    else if( _rotation.Y > trackedAngle ){
        _rotation.Y -= conf::_BACKSPEED_MODIFICATOR * _walkyrie->getSpeed(SModeDescription::Yaw);
        _rotation.Y = std::max(trackedAngle, _rotation.Y);

    }


    if ( IS_ACTIVE(NPlayerInput::MoveForward) ){
        _currentPos.Z += modifier * _walkyrie->getSpeed(SModeDescription::Forward);
        _currentPos.Z = std::min(_currentPos.Z, conf::_Z_MAX);
    }
    else if( IS_ACTIVE(NPlayerInput::MoveBackward) ){
        _currentPos.Z -= modifier * _walkyrie->getSpeed(SModeDescription::Forward);
        _currentPos.Z = std::max(_currentPos.Z, conf::_Z_MIN);
    }

    LIMIT_RANGE(_rotation.Y,-zAngleLimit,zAngleLimit);
}



// Passer en inline
void
CPlayer::processMoves(){


    //float modifier = 1.f;
//    if( (_cachedInput[MoveLeft] || _cachedInput[MoveRight]) && (_cachedInput[MoveBackward] || _cachedInput[MoveForward])){
//        modifier = 1.f/std::sqrt(2.f);
//    }
    // Can't move if transforming
    /*if(isTransforming()){
        _INFO << "is transforming";
        return;
    }
    */
    // TODO
    TVector3df rotation,translation;
    //(*_specs[*_currentMode].

       /*
    getSpec(*_currentMode).processMoveFunction)(rotation,translation);
    if(translation.getLengthSQ() > 1){
        // alors on le normalise
        translation.normalize();
        // garde le vaisseau a l'interieur des limites
    }

    //
    translation.X *= getSpeed(SModeDescription::Lateral);

    // Multiply
    if(translation.Y > 0){
        translation.Y *= getSpeed(SModeDescription::Forward);
    }
    else {
        translation.Y *= getSpeed(SModeDescription::Backward);
    }

    _currentPos.X = irr::core::clamp( _currentPos.X,-conf::_X_MAX,conf::_X_MAX);
*/

    //if( SQnorme(translation) > 1 alors on divise par Racine de 2 puis on multiplie par speed

    //FUSION_MEMBER_FUNCTION( _specs[_currentMode] , this->processMoveFunction)();
    //(_specs[_currentMode].processMoveFunction)();
    //(*this)
    //(this->*processMoveFunction)();

    processFighterMoves();

 //#define callMemberFunction(object,ptrToMember)  ((object).*(ptrToMember))

//    constrainedIncrement();
//    constrainedDecrement();
//// TODO mettre a jour la camera en cas d'acceleration

}


float
CPlayer::getRange() const {

    return _walkyrie->getRange();
};



//Player
bool
CPlayer::update(const TTimer::TimeType& elapsedTime){

/// TODO empecher la mise a jour si console active
// _level->_engine->device->getTimer()->getTime()

    updateInput();

    _walkyrie->update();

    //_INFO << "mode up value" << _cachedInput.getState(NPlayerInput::ModeUp);

    _elapsedTimes[SinceLastShot]           += elapsedTime;
    _elapsedTimes[SinceLastTransformation] += elapsedTime;
    _elapsedTimes[SinceLastMissile]        += elapsedTime;


    // _parameters[o3::NParameters::Range] = _walkyrie->getRange();



    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ///// If player recently died, blink the ship
    ////////////////////////////////////////////////////
    if(_blinksCounter > 0){

        //_elapsedTimes[SinceBeingKilled] += elapsedTime;

        _elapsedTimes[SinceLastBlinkRevival] += elapsedTime;

        if(_elapsedTimes[SinceLastBlinkRevival] > conf::_PLAYER_BLINK_LENGTH){

            --_blinksCounter;
            _elapsedTimes[SinceLastBlinkRevival] = 0;

            // renders or not the node
            if(_blinksCounter <= 0){
                setupNewLife();
            }
            else {
                _node->setVisible(! _node->isVisible() );
            }
        }
    }

    // cools primary weapon if overheated
    _cannonHeat -= conf::_COOLING_DELTA;
    if(_cannonHeat <= 0){
        _cannonHeat = 0;
        _coolingDown = false;
    }

//isKeyDown()


    //_walkyrie.
    _node->setRotation(_rotation);
    _node->setPosition(_currentPos);

    return true;
}





// TODO renommer en createBoosters
void
CPlayer::createBoosters(){

    // static CGameEngine::getParticleManager()->createBooster( );
    _leftBooster = CGameEngine::getParticleManager()->createBooster(  );

    //_leftBooster->setParent( leftBoosterBone );

}







void
CPlayer::FirePrimaryShot(){

    // Can't shoot while transforming
    if(_walkyrie->isTransforming()){
        _LOG_WARNING << "Cannot shoot beacause model transforming";
        return;
    }

//    _INFO << "SHOOT";
    _elapsedTimes[SinceLastShot] = 0;

    // TODO prendre heat comme timer
    _cannonHeat += conf::_SHOT_HEAT_VALUE;
    //_INFO << "heat" << _cannonHeat;
    if(_cannonHeat >= conf::_BC_PLAYER_MAX_HEAT){

        _cannonHeat = conf::_BC_PLAYER_MAX_HEAT;
        _coolingDown = true;
    }


    const TVector3df forward = getPlayerForwardVector();

// TODO remplacer par _fleet
// This shoot->bullet
// POSSIBLE BUG ICI
    //CBullet* bullet = _level->_alliedFleet->createAndSetupBullet("models/missile.obj",
    CBullet* bullet = getFleet()->createAndSetupBullet("models/missile.obj",
                                                      forward
                                                      );
    // Then configure bullet
    bullet->setPosition( this->getPosition() );

    //bullet->setRange();
    //bullet->setRange(conf::_PLAYER_BULLET_RANGE);
    bullet->setup(conf::_PLAYER_BULLET_RANGE,
                  0,        //!< life
                  5,        //!< damage
                  0         //!< Bonus
                  );

    //bullet->setWithinScreen(true);

    _INFO << "bullet shot" << bullet->getPosition() <<  " isVisible " << bullet->_node->isVisible();
}


void
CPlayer::FireMissiles(){

    _INFO << "Missile";
//    _elapsedTimes[SinceLastMissile] = 0;
//
//// TODO verifier qu'il reste des missiles
//    --_missilesLeft;
//
//    if(_level){
//        CStaticBattery* target = 0;
//        target = _level->getNextTarget();
//        if(target){
//            _level->_alliedFleet.addMissile(
//                        "player_bullet",
//                        getPosition(),
//                        target,
//                        core::vector3df(0.1,0,-0.03)
//                    );
////            _INFO << "player Missile created";
//            //,180,getPosition());
//        }
//    }

}

//numberOfAllowedModes()

//Ici on pourrait enlever de l'energie etc.. a chaque transformation
//dequecircular dispo dans boost
bool
CPlayer::processTransformations()
{
    //++_stats.NbOfTransformations;



    // If only one mode enabled then it can't transform
    if(_walkyrie->isTransforming()  || (_rotation.Y != 0)|| (_rotation.Z != 0) ){
        return false;
    }

    // otherwise we update stats

    //_INFO << "Processing moves";

    //_INFO << "Mode up" << _cachedInput.getState(ModeUp);
    if(IS_ACTIVE(ModeUp) ) {

        _INFO << "Mode up";

        return _walkyrie->transformIntoNextMode();
        //return true;

    }
    else if(IS_ACTIVE(ModeDown)  ) {

        _INFO << "Mode down";
        return _walkyrie->transformIntoPreviousMode();
    }
    return false;
}



//
//// TODO Plusieurs updates position selon le type du vaisseau
//// Renommer en process Move
//void
//CPlayer::processShootingsAsFighter(){
//
////processShootingsAsFighter();
//    // Todo en fait faudrait faire ca pour les shoots plutot
////    switch (_currentMode)
////    {
////    	case NMode::Battloid:
////            processShootingsAsBattloid();
////    		break;
////
////    	case NMode::Gerwalk:
////            processShootingsAsGerwalk();
////    		break;
////
////    	case NMode::Fighter:
////            processShootingsAsFighter();
////    		break;
////
////    	default:
////    		break;
////    }
//
//}
//
//


const bool&
CPlayer::coolingDown() const
{

    //return (_elapsedTimes[Cooldown] == 0);
    return _coolingDown;
}




void
CPlayer::setupNewLife(){
    // Refill missile stock
    _missilesLeft = conf::_DEFAULT_STOCK_OF_MISSILES;
    _blinksCounter = 0;
    _node->setVisible(true);
}


void
CPlayer::setupForNewGame(){

    //_trackedMissile(0),
    _livesLeft = conf::_DEFAULT_LIVES;
    _walkyrie->forceMode( NWalkyrieModes::yf19_Fighter);
    setupNewLife();
}

//void setupForNewLevel()



/// Destructor
CPlayer::~CPlayer(){

    /// Delete space allocated to each particle system associated with a booster
    /*for(std::vector<SBooster>::iterator i = mShip->mBoosters.begin();i != mShip->mBoosters.end();i++){
        delete i->system;
    }*/
}

#undef IS_ACTIVE
