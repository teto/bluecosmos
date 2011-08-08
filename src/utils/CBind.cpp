#include "CBind.hpp"

CBind::CBind() :
    _lastActivation(0),
    CBindDescriptor()
{

}

bool
CBindDescriptor::updateLastActivationTime(const irr::u32& registeredActivationTime, const irr::u32& currentTime) {

    // If event inactive
    if(registeredActivationTime == 0){
        _lastActivation = 0;
        return false;
    }
    // if event
    else if(_lastActivation == 0){
        _lastActivation = registeredActivationTime;
        return true;
    }
    //able
    else if( repeat() ){

            // check if we waited repeat time
           if( (_lastActivation + _normalizedRepeatDelay) < (currentTime)) {
               // then it's activated
               _lastActivation = currentTime;
               return true;
           }

           return false;
    }

    return false;
}



bool
CBindDescriptor::checkState(const irr::u32& currentTime)
{

    irr::u32 registeredActivationTime = 0;
    bool state = false;

    switch(_type){

    case NInputType::KEY:
        registeredActivationTime = CEventManager::keyDownTime(static_cast<irr::EKEY_CODE>(_value) );
        break;

    case NInputType::JOY_AXIS_PLUS:
        registeredActivationTime = CEventManager::joystickAxisDownTime(_value);
        break;

    case NInputType::JOY_AXIS_MINUS:

        registeredActivationTime = CEventManager::joystickAxisDownTime(_value);
        break;

    case NInputType::JOY_BTN:
        registeredActivationTime = CEventManager::joystickButtonDownTime(_value);
        break;

    case NInputType::JOY_POV:
        //registeredActivationTime = CEventManager::joystickButtonDownTime(_value);
//        if( ){
//        }
        break;

    //case NInputType::UN
    default:
        break;
    }


    state = updateLastActivationTime(registeredActivationTime,currentTime);
//    if(state){
//
//        _INFO << "checking keyboard mapping" <<registeredActivationTime ;
//    }

    return state;
}
