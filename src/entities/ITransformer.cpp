#include "ITransformer.hpp"
#include <fusion/fusion.hpp>





ITransformer::ITransformer(irr::scene::IAnimatedMeshSceneNode* node)
{
//irr::scene::IAnimatedMeshSceneNode*
    // load node only if precised
    if(node)    load(node);
}


ITransformer::~ITransformer()
{

}


bool
ITransformer::isTransforming() const {

    //_INFO << "End frame [" << _animatedNode->getEndFrame () << "] -- Current frame [" << _animatedNode->getFrameNr() << "]";
    //bool test=  (_animatedNode->getEndFrame () != _animatedNode->getFrameNr());
    return _transforming;
//    return test;
    //return (_animatedNode->getEndFrame () != _animatedNode->getFrameNr()) ;
};


//const std::size_t& nbOfBoosters

void
ITransformer::load( irr::scene::IAnimatedMeshSceneNode* node)
{
    BOOST_ASSERT(node);
    _animatedNode = node;
    _transforming = false;


    _animatedNode->setLoopMode(false);
    //_animatedNode->setAnimationSpeed(3);
    //_animatedNode->setCurrentFrame(5);
    //_animatedNode->setFrameLoop(0,0);
    //_animatedNode->setDebugDataVisible(irr::scene::EDS_BBOX );
    //_animatedNode->setMaterialFlag(irr::video::EMF_SKE  ,true );

    //return true;
}



void
ITransformer::OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* node)
{

    _transforming = false;
    _animatedNode->setAnimationEndCallback( 0 );
    //onTransformationEnd();
    //_INFO << "ITransformer : End of Transformation" ;
}




//
//
//void
//ITransformer::update(){
//    irr::scene::IBoneSceneNode* bone = _animatedNode->getJointNode(boneName);
//}


float
ITransformer::getTransformationAdvancement(){

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

        //_LOG_DEBUG << "framesAlreadyDisplayed" << framesAlreadyDisplayed;

//        transformationProgress   = (_animatedNode->getFrameNr () - _animatedNode->getStartFrame());
//        transformationProgress  /= ( _animatedNode->getStartFrame() - _animatedNode->getEndFrame() );
//        transformationProgress   = irr::core::abs_(transformationProgress );
        transformationProgress = framesAlreadyDisplayed/ (irr::f32)nbOfFrames;
    }
    //_LOG_DEBUG << "transformationProgress" << transformationProgress;

    //getAnimationSpeed()*( -);
    return transformationProgress;
}






// TODO passer un IAnimateNode
// todo renomer en load
//void
//ITransformer::load(IAnimatedMeshSceneNode* node){
//
//    BOOST_ASSERT( node != 0);
//
//    _transforming = false;
////
////    if(_animatedNode){
////
////    }
//
//    _animatedNode = node;
//
//    //std::transform(_specs.begin() , _specs.end(), )
//
//}
//

// 2 ieme version plus optimisee
// permet d'indiquer si on veut augmenter ou baisser le mode
// mais ne change pas le mode actuel !!!
// TODO renommer en targetFrame
bool
ITransformer::setTargetedFrame(const int& targetedFrame){

    //irr::s32 endFrame = _animatedNode->getEndFrame ();
    irr::f32 currentFrame = _animatedNode->getFrameNr ();


    if(targetedFrame < currentFrame){
        _animatedNode->setAnimationSpeed(-5);
    }
    else if(targetedFrame > currentFrame ){
        _animatedNode->setAnimationSpeed(5);
    }
    // if targetedFrame == curentFrame
    else {
        _LOG_WARNING << "Frames are equal";
        return false;
    }

    // 18 to :18
//    _INFO << "starting frame " << currentFrame << " to :" << targetedFrame;
//    if(targetedFrame == currentFrame){
//
//        _INFO << "frames are equal";
//    }
//    else {
//        _INFO << "Frames are inequal";
//    }

    if( _animatedNode->setFrameLoop(currentFrame,targetedFrame) ){

        _animatedNode->setAnimationEndCallback(this);
        _transforming = true;
        return true;
    }
    else {

        _LOG_WARNING << "setFrameLoop returned false for animation" << currentFrame << "to " << targetedFrame;
        return false;
    }


}


