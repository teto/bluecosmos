#include "IMultiModeTransformer.hpp"
#include "SModeDescription.hpp"
#include <fusion/fusion.hpp>


IMultiModeTransformer::TAvailableModes IMultiModeTransformer::_availablesModes;


// initStaticMembers()

void
IMultiModeTransformer::initialize() {

    SModeDescription& yf19fighter = _availablesModes[NWalkyrieModes::yf19_Fighter];
    yf19fighter.defineAnimation(3,5);
    //yf19fighter.setCameraRecul(0,20,-50);

    SModeDescription& yf19gerwalk = _availablesModes[NWalkyrieModes::yf19_Gerwalk];
    yf19gerwalk.defineAnimation(12,5);

    SModeDescription& yf19battloid = _availablesModes[NWalkyrieModes::yf19_Battloid];
    yf19battloid.defineAnimation(18,5);
}



void
IMultiModeTransformer::update(){

    //
    if( this->isTransforming() ){

        // update spec
        interpolate( this->getTransformationAdvancement(), getModeFromModeId(_activeSpecs[_currentMode]), getModeFromModeId(_activeSpecs[_targetedMode]) );
        //_cameraRecul = getSpecs(*_currentMode)._cameraRecul.getInterpolated(getSpecs(*_targetedMode)._cameraRecul, thisWeight );
        //_INFO << "transformation advancement" << this->getTransformationAdvancement();

         //_parameters[o3::NParameters::Range] = this->Range;
    }
    // otherwise
    else {
        // do nothing
    }

}

//,const TModeId& enforcedMode
IMultiModeTransformer::IMultiModeTransformer(irr::scene::IAnimatedMeshSceneNode* node, const TModeId& id) :
ITransformer(node),
_cyclic(false),
_currentMode(0),
_targetedMode(0)
{
    //clearModes();
    //forceMode(enforcedMode);
    this->load(node,id);
}


void
IMultiModeTransformer::load(irr::scene::IAnimatedMeshSceneNode* node,const TModeId& id){
//enforcedMode
    ITransformer::load(node);
    //forceMode(id);
    _animatedNode->setAnimationEndCallback(this);

    // -- clear modes
    clearModes(id);
}


//
//void
//IMultiModeTransformer::onTransformationEnd() {
//    //_animatedNode->setFrameLoop(1,20);
//    _currentMode = _targetedMode;
//    //getCurrentMode();
//}



void
IMultiModeTransformer::transformIntoFirstMode(){

    BOOST_ASSERT( _activeSpecs.size() > 0);

    transformInto(  _activeSpecs.front() );
    //transformInto( 0 );
}


void
IMultiModeTransformer::transformIntoLastMode(){

    //BOOST_ASSERT( _activeSpecs.size() > 0);

    transformInto( _activeSpecs.back() );
    //transformInto( _activeSpecs.size() - 1 );
}


bool
IMultiModeTransformer::transformIntoNextMode() {

    int targetedMode = _currentMode + 1;

    if(targetedMode >= _activeSpecs.size() ){

        if(isCyclic()){
            targetedMode = 0;
        }
        else {
            return false;
        }
    }



    return transformInto( _activeSpecs[targetedMode]);
}


bool
IMultiModeTransformer::transformIntoPreviousMode() {

    int targetedMode = _currentMode - 1;

    if(targetedMode < 0 ){

        if(!isCyclic()){
            return false;
        }
//        else {
//        }
        targetedMode = _activeSpecs.size() - 1;
    }


    return transformInto( _activeSpecs[targetedMode] );
}



bool
IMultiModeTransformer::transformInto(const TModeId& modeId){
    //BOOST_ASSERT( index > 0 && index < _availablesModes.size() );

    // If no transformation mode available
    if( _activeSpecs.empty() ){
        _INFO << "No mode available for transformation";
        return false;
    }

    if(modeId == _currentMode){
        _INFO << "cannot transform to mode [" << modeId << "] : this is already active mode";
        return false;
    }



    const SModeDescription& mode = getModeFromModeId(modeId);


    if( setTargetedFrame( mode.getFrame() ) ){

        _INFO << "Targetting mode [" << modeId << "] -- Frame [" << mode.getFrame() << "]" ;// << *targetedMode;
        _targetedMode = modeId;
        return true;
    }
    else {


    }



    return false;


}

//IMode* enforcedMode


IMultiModeTransformer::~IMultiModeTransformer()
{

}



void
IMultiModeTransformer::OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* node)
{

    //
    ITransformer::OnAnimationEnd(node);

    //forceMode( static_cast<NWalkyrieModes::EId>(_targetedMode) );

    //_LOG_DEBUG
    //setFrameLoop
    //setLoopMode

    //interpolate(1.f ,  getModeFromModeId(_currentMode) , getModeFromModeId(_targetedMode) );
    interpolate( 1.f, getModeFromModeId(_activeSpecs[_currentMode]), getModeFromModeId(_activeSpecs[_targetedMode]) );
    _currentMode = _targetedMode;
    printMode();
    _INFO << "IMultiMode transformation finished. Current mode [" << _currentMode << "]";
    //onTransformationEnd();
    //_INFO << "End of Transformation" ;
}



void
IMultiModeTransformer::forceMode(const TModeId& modeId){


    //BOOST_ASSERT(mode);

    _INFO << "Enforcing mode [" << modeId << "] !!";

    //const int& noFrame
    const SModeDescription& mode = getModeFromModeId(modeId);


    _animatedNode->setCurrentFrame ( mode.getFrame() );

    //
    interpolate(1.f , *this, mode);
    _transforming = false;
    // TODO
    //onTransformationEnd();

    // TODO THIS IS A HACK (should use something like a  = operator)
//    this->interpolate(1.f,getSpecs(mode) );
    //_INFO << "Camera recul" << ;
}




//const TModeId& id
void
IMultiModeTransformer::clearModes(const TModeId& id){

    _activeSpecs.clear();
    //allowMode(id);
    forceMode(id);

    //_currentMode
    _currentMode  = 0;
    _targetedMode = 0;

}


SModeDescription&
IMultiModeTransformer::getModeFromModeId(const TModeId& id) {
    return _availablesModes[id];
}


// TODO faudrait verifier que le mode y est unique ?
bool
IMultiModeTransformer::allowMode(const TModeId& id)
{

    // check frame is ok
    SModeDescription& mode = getModeFromModeId(id);
    if(mode.getFrame() > _animatedNode->getMesh()->getFrameCount() ){
        _LOG_WARNING << "mode frame > end frame of node";
    }

    _LOG_DEBUG << "Mode [" << id << "] allowed ";
    _activeSpecs.push_back(  id );
    //return *this;
    return true;
}
