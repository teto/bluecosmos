/**
**/
#ifndef _BC_IKEYBOARDDEVICE_HPP_INCLUDED
#define _BC_IKEYBOARDDEVICE_HPP_INCLUDED


#include <irrlicht.h>  // header only
#include <string>
#include "IInputDevice.hpp"

namespace input {

//static std::array< irr::s16,irr::SEvent::SJoystickEvent::NUMBER_OF_AXES > _axisState;
class CIrrlichtKeyboardDevice
//:
//    public IEventReciever
{
    private:
        static Keys;

    public:
        static void handleEvent(irr::SEvent::SKeyInput const&);
};
    //: public IInputDevice<irr::KEY_KEY_CODES_COUNT ,int> {

}   //!< End of namespace



#endif
