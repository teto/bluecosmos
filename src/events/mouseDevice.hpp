/**
**/
#ifndef _BC_IMOUSEDEVICE_HPP_INCLUDED
#define _BC_IMOUSEDEVICE_HPP_INCLUDED


#include <irrlicht.h>  // header only
#include <string>
#include "IInputDevice.hpp"


namespace input {

// TODO s'inspirer de la sfml
class CIrrlichtMouseDevice
    //: public IInputDevice<6,int>
{
    // TODO 6 a tout hasard
    static std::array< EButtonState, 6> _buttons;

public:
    irr::s32 X;
    irr::s32 Y;

    static bool isButtonDown(const int& button) const;

    //static bool getX();
};


}

#endif
