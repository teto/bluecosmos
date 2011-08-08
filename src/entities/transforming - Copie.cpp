#include "transforming.hpp"
//

//_animatedNode->setFrameLoop(1,20);


void
CTransformingShip::transformIntoFirstMode(){

    BOOST_ASSERT( _activeSpecs.size() > 0);

    transformInto();
}




bool
CTransformingShip::transformInto(const EMode& targetedMode){


//targetedMode
    TAvailableModes::iterator result = std::find(_activeSpecs.begin(),_activeSpecs.end(), targetedMode);

    // if not available or already enabled
    // || (result == _currentMode)

    return transformInto(result);

}

// EMode
// TODO renommer en transformInto(Emode)
// et garder transformInto(TMode)
bool
CPlayer::transformInto(const TMode& targetedMode){

    //return transformInto(Gerwalk);
    if( (targetedMode == _activeSpecs.end() )  ){
        return false;
    }
    else {


        if( TWalkyrie::setTargetedFrame( getSpecs(*targetedMode).getFrame() ) ){

            _INFO << "New mode ";// << *targetedMode;
            _targetedMode =  targetedMode;
            return true;
        }
    }

    /*
    const EMode& correctedMode = targetedMode;

    if(correctedMode != _currentMode){

        if( TWalkyrie::setTargetedFrame( getSpecs(correctedMode).getFrame() ) ){

            _INFO << "New mode " << correctedMode;
            _targetedMode =  (correctedMode);
            return true;
        }
    }
    */
    return false;


}


CTransformingShip::CTransformingShip() :
_animatedNode(0)
{

    Reset();
}


CTransformingShip::~CTransformingShip()
{

}

//const std::size_t& nbOfBoosters

bool
CTransformingShip::init( irr::scene::IAnimatedMeshSceneNode* node)
{
    BOOST_ASSERT(node);
    _animatedNode = node;

    _animatedNode->setAnimationEndCallback(this);
    _animatedNode->setLoopMode(false);
    //_animatedNode->setAnimationSpeed(3);
    //_animatedNode->setCurrentFrame(5);
    _animatedNode->setFrameLoop(0,0);
    //_animatedNode->setDebugDataVisible(irr::scene::EDS_BBOX );
    //_animatedNode->setMaterialFlag(irr::video::EMF_SKE  ,true );

    return true;
}



void
CTransformingShip::OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* node)
{

    _transforming = false;
    _currentMode = _targetedMode;
    //_INFO << "End of Transformation" ;
}




//
//
//void
//CTransformingShip::update(){
//    irr::scene::IBoneSceneNode* bone = _animatedNode->getJointNode(boneName);
//}


float
CTransformingShip::getTransformationAdvancement(){

    irr::f32 transformationProgress = 0.f;

    if(isTransforming()) {

        // Pourcentage
        //getFrameNr returns current frame (f32)
        // getEndFrame() current end frame number (s32)
        // getStartFrame() Returns the current start frame number (s32).
        irr::f32 framesAlreadyDisplayed = 0;
        // Ca devrait etre tjrs positif ?!
        irr::s32 nbOfFrames = ( _animatedNode->getEndFrame() - _animatedNode->getStartFrame() ) + 1;


        // Selon la vitesse
        if(_animatedNode->getAnimationSpeed () > 0){
            framesAlreadyDisplayed = _animatedNode->getFrameNr () - _animatedNode->getStartFrame() + 1;
        }
        else if(_animatedNode->getAnimationSpeed () < 0){
            framesAlreadyDisplayed = _animatedNode->getEndFrame() - _animatedNode->getFrameNr () + 1;
        }

        _INFO << "framesAlreadyDisplayed" << framesAlreadyDisplayed;

//        transformationProgress   = (_animatedNode->getFrameNr () - _animatedNode->getStartFrame());
//        transformationProgress  /= ( _animatedNode->getStartFrame() - _animatedNode->getEndFrame() );
//        transformationProgress   = irr::core::abs_(transformationProgress );
        transformationProgress = framesAlreadyDisplayed/ (irr::f32)nbOfFrames;
    }
    _INFO << "transformationProgress" << transformationProgress;

    //getAnimationSpeed()*( -);
    return transformationProgress;
}


void
CPlayer::forceMode(const EMode& mode){

// TODO
    _INFO << "MODE ENFORCED !!";
    _node->setCurrentFrame (this->getFrame());

    //this->processMoveFunction = &CPlayer::processFighterMoves;
    this->processMoveFunction = getSpecs(mode).processMoveFunction;

    // TODO THIS IS A HACK (should use something like a  = operator)
    this->interpolate(1.f,getSpecs(mode) );
    //_INFO << "Camera recul" << ;
}



// TODO renommer en next / prior Mode
CPlayer::TMode
CPlayer::modeUp(const CPlayer::TMode& mode){
    //_currentMode
    CPlayer::TMode nextMode = mode;

    //boost::prior(list.end());

    if(nextMode >= _activeSpecs.size()){
        nextMode = 0;//boost::next( _activeSpecs.begin() );
    }
    else {
        ++nextMode;
    }

    return nextMode;
}

// TODO utiliser un vecteur avec des index ?

CPlayer::TMode
CPlayer::modeDown(const TMode& mode){

    CPlayer::TMode nextMode = mode;


    if(nextMode <= _activeSpecs.begin()){
        nextMode = _activeSpecs.size();// boost::prior( _activeSpecs.end() );
    }
    else {
        --nextMode;
    }
    return nextMode;
}

void
CTransformingShip::update()
{

}



void
CTransformingShip::Reset(){

    //_specs.clear();
    _transforming = false;

    if(_animatedNode){

    }

    _animatedNode = 0;

    //std::transform(_specs.begin() , _specs.end(), )

}


// 2 ieme version plus optimisee
// permet d'indiquer si on veut augmenter ou baisser le mode
// mais ne change pas le mode actuel !!!

bool
CTransformingShip::setTargetedFrame(const int& targetedFrame){

    //irr::s32 endFrame = _animatedNode->getEndFrame ();
    irr::f32 currentFrame = _animatedNode->getFrameNr ();
    if(isTransforming()) return false;

    if(targetedFrame < currentFrame){
        _animatedNode->setAnimationSpeed(-5);
    }
    else if(targetedFrame >= currentFrame ){
        _animatedNode->setAnimationSpeed(5);
    }
    else {
        _INFO << "not updating";
        return false;
    }

    _INFO << "starting frame " << currentFrame<< " to :" << targetedFrame;
    _animatedNode->setFrameLoop(currentFrame,targetedFrame);
    _transforming = true;
    return true;
}



void
CPlayer::forceMode(const EMode& mode){

// TODO
    _INFO << "MODE ENFORCED !!";
    _animatedNode->setCurrentFrame (this->getFrame());

    //this->processMoveFunction = &CPlayer::processFighterMoves;
    //this->processMoveFunction = getSpecs(mode).processMoveFunction;

    // TODO THIS IS A HACK (should use something like a  = operator)
    this->interpolate(1.f,getSpecs(mode) );
    //_INFO << "Camera recul" << ;
}



// TODO renommer en next / prior Mode
CPlayer::TMode
CPlayer::modeUp(const CPlayer::TMode& mode){
    //_currentMode
    CPlayer::TMode nextMode = mode;

    //boost::prior(list.end());

    if(nextMode >= _activeSpecs.size()){
        nextMode = 0;//boost::next( _activeSpecs.begin() );
    }
    else {
        ++nextMode;
    }

    return nextMode;
}

// TODO utiliser un vecteur avec des index ?

CPlayer::TMode
CPlayer::modeDown(const TMode& mode){

    CPlayer::TMode nextMode = mode;


    if(nextMode <= _activeSpecs.begin()){
        nextMode = _activeSpecs.size();// boost::prior( _activeSpecs.end() );
    }
    else {
        --nextMode;
    }
    return nextMode;
}


void
CPlayer::clearModes(){
    _activeSpecs.clear();

    _currentMode  = _activeSpecs.begin();
    _targetedMode = _activeSpecs.begin();

}


// TODO faudrait verifier que le mode y est unique ?
CPlayer&
CPlayer::allowMode(const EMode& mode)
{

    // TODO check que ca existe
    /*std::find(_specs.begin(),_specs.end() );
    if()
    */
    _activeSpecs.push_back(mode);
    return *this;
}
