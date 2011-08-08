/**
**/
#ifndef _BC_IKEYBOARDDEVICE_HPP_INCLUDED
#define _BC_IKEYBOARDDEVICE_HPP_INCLUDED


#include <irrlicht.h>  // header only
#include <string>
#include "IInputDevice.hpp"



//static std::array< irr::s16,irr::SEvent::SJoystickEvent::NUMBER_OF_AXES > _axisState;
class CIrrlichtKeyboardDevice : public IInputDevice<irr::KEY_KEY_CODES_COUNT ,int> {

};



#endif
