#include "joystickDevice.hpp"


namespace input {
/*
bool
CEventManager::isAxisPositive(const irr::s16& axis){
    //const int& value = _axisState[axis].value;
    const int& value = _axisState[axis];
    return ( (value != 0) && (value > CEventManager::Threshold)   );
}

bool
CEventManager::isAxisNegative(const irr::s16& axis){
    const int& value = _axisState[axis];
    return ( (value != 0) && (value < -CEventManager::Threshold)   );
   // return ( (_axisState[axis].value < -CEventManager::Threshold) && (_axisState[axis].value != 0) );
}
*/

//
CIrrlichtJoystickDevice::CIrrlichtJoystickDevice(const irr::SJoystickInfo& infos) :
    _joystickInfo(infos)
{


}



void
CIrrlichtJoystickDevice::update(irr::SEvent::JoystickEvent const& e) {

}


}   //!< End of namespace
