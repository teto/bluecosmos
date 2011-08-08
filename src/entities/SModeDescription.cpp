#include "SModeDescription.hpp"
#include <fusion/fusion.hpp>

SModeDescription::SModeDescription() :
Range(0),
//TransitionDelay(0),
Frame(0)
{
    Speed.fill(0);
    AnimationSpeed = 0;
    YAngle = 0;
    ZAngle = 0;
}

void
SModeDescription::printMode() const {

    _INFO << "Camera recul " << _cameraRecul;
    _INFO << "Range [" << getRange() << "]";
    _INFO << "Forward speed [" << getRange() << "]";
}

//
//SModeDescription&
//SModeDescription::operator=(const SModeDescription& mode){
//
//    this->Range             = mode.Range;
//    this->Speed             = mode.Speed;
//    this->Frame             = mode.Frame;
//    this->_cameraRecul      = mode._cameraRecul;
//
//    return *this;
//}


//SModeDescription
//SModeDescription::interpolate(const float& progress,const SModeDescription& start,const SModeDescription& objective)
//{
//    //SModeDescription temp;// = start;
//    return start.getInterpolated(progress,objective);
//    //return temp;
//}

void
SModeDescription::interpolate(const float& progress,const SModeDescription& start,const SModeDescription& objective) {
//TODO
    const float& objectiveWeight = progress;
    const float startWeight      = 1.f  - progress;

    // interpolate speeds
    for(int i = 0; i< SpeedsCount; ++i){
    //BOOST_FOREACH()
        //std::for_each( Speed.begin)
        this->Speed[i] = startWeight * start.Speed[i] + objectiveWeight *objective.Speed[i];
    }

    // Interpolate range
    this->Range = start.Range*startWeight + objectiveWeight * objective.Range;

    //this->processMoveFunction = this->processMoveFunction;
    // I think the irrlicht convention is weird
    // 2nd parameter at 1 => _cameraRecul = all 1
    //this->_cameraRecul,

/////////////////////////////////////////
    _cameraRecul = _cameraRecul.interpolate(start._cameraRecul, objective._cameraRecul, startWeight );

}


// TODO interpolate angles too (use a vector)
SModeDescription&
SModeDescription::interpolate(const float& progress,const SModeDescription& objective){

    interpolate(progress,*this,objective);
//    float objectiveWeight = progress;
//    float startWeight      = 1.f  - progress;
//
//    // interpolate speeds
//    for(int i = 0; i< SpeedsCount; ++i){
//    //BOOST_FOREACH()
//        //std::for_each( Speed.begin)
//        this->Speed[i] = startWeight * this->Speed[i] + progress *objective.Speed[i];
//    }
//
//    // Interpolate range
//    this->Range = this->Range*startWeight + objectiveWeight * objective.Range;
//
//    //this->processMoveFunction = this->processMoveFunction;
//    // I think the irrlicht convention is weird
//    // 2nd parameter at 1 => _cameraRecul = all 1
//    //this->_cameraRecul,
//
///////////////////////////////////////////
/////// TODO la y a un bug la camera bouge trop vite car on interpole pas la mm camera a chaque fois
////////////////////////////////////////////
//    _cameraRecul = _cameraRecul.getInterpolated(objective._cameraRecul, startWeight );
//
//    setupSpeeds(const float& lateralSpeed,
//                const float& forwardSpeed,const float& defaultForward,
//                const float& backwardSpeed,const float& rollingSpeed,
//                const float& yawSpeed);
//    mode.setupAngleBounds();
    return *this;
}



SModeDescription&
SModeDescription::setupSpeeds(
const float& lateralSpeed,
const float& forwardSpeed,
const float& defaultForward,
const float& backwardSpeed,
const float& rollingSpeed,
const float& yawSpeed
)
{


    Speed[Lateral]        = lateralSpeed;
    Speed[Forward]        = forwardSpeed;
    Speed[DefaultForward] = defaultForward;
    Speed[Backward]       = backwardSpeed;
    Speed[Roll]           = rollingSpeed;
    Speed[Yaw]            = yawSpeed;

    return (*this);
}



SModeDescription&
SModeDescription::setAngleBounds(
const float& rollingLimit,
const float& yawLimit
)
{
    //
    YAngle = rollingLimit;
    ZAngle = yawLimit;
    return (*this);
}


SModeDescription&
SModeDescription::setRange(const float& range)
{
    Range = range;
    return (*this);
}

SModeDescription&
SModeDescription::defineAnimation(const int& noFrame,const irr::f32& animationSpeed)
{
    Frame           = noFrame;
    AnimationSpeed  = animationSpeed;
    return (*this);
}


