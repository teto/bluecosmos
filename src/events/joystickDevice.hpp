/**
**/
#ifndef _BC_IJOYSTICKDEVICE_HPP_INCLUDED
#define _BC_IJOYSTICKDEVICE_HPP_INCLUDED


#include <irrlicht.h>  // header only
#include <string>
#include "IInputDevice.hpp"


namespace NPov {
enum EId {
Up = 0,
Right,
Down,
Left

};
}


class CIrrlichtJoystickDevice : public IInputDevice<irr::SEvent::SJoystickEvent::NUMBER_OF_BUTTONS, int>
                        //public IInputDevice<irr::SEvent::SJoystickEvent::NUMBER_OF_AXES, NPov::EId>

{

    //static std::array< irr::s16,irr::SEvent::SJoystickEvent::NUMBER_OF_AXES > _axisState;

public:
/*    const irr::s32 CEventManager::POV_DISABLED_POSITION = 65535;
    const irr::u16 CEventManager::Threshold = 16000;


irr::s32 CEventManager::POV_UP      = 0;
irr::s32 CEventManager::POV_RIGHT   = 9000;
irr::s32 CEventManager::POV_DOWN    = 18000;
irr::s32 CEventManager::POV_LEFT    = 27000;


    static bool povBeingUsed() {
        return (_pov.value != POV_DISABLED_POSITION);
    }

    static irr::u32 getPOVActivationTime() {
        return _pov.time;
    }


    static irr::u32 joystickAxisDownTime(const int& axis) {

        int tAxis = irr::core::clamp(axis,0,irr::SEvent::SJoystickEvent::NUMBER_OF_AXES-1);
        // takes into account the offset of the table
        //tAxis    += irr::SEvent::SJoystickEvent::NUMBER_OF_BUTTONS;
        return _axisState[ tAxis ];
    }

    //static void
    static irr::s32 getPOV() { return _pov.value; };

    //static bool enableJoysticks();

    static irr::u16 Threshold;



    typedef irr::s32 TAxisTuple;
    static TAxisTuple _pov;

    //static std::array<irr::u32,irr::SEvent::SJoystickEvent::NUMBER_OF_AXES > _axisState;
    static std::array< irr::s16,irr::SEvent::SJoystickEvent::NUMBER_OF_AXES > _axisState;

    bool isAxisPositive(const irr::s16& axis);
    bool isAxisNegative(const irr::s16& axis);
    irr::s32 POV_DISABLED_POSITION;;
    irr::s32 POV_UP;
    irr::s32 POV_DOWN;
    irr::s32 POV_LEFT;
    irr::s32 POV_RIGHT;
    */
};

#endif
