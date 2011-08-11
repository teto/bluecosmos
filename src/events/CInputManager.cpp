#include "CInputManager.hpp"
#include "CBindDescriptor.hpp"
#include "CBind.hpp"
#include <fusion/logging/CConsoleLogger.hpp>
#include "mouseDevice.hpp"
#include "joystickDevice.hpp"
#include "keyboardDevice.hpp"

using namespace irr;
using namespace core;

int
CInputManager::retrieveStateFromDescriptor(CBindDescriptor const& d) {

    // TODO a revoir
    switch( d.getInputType() ){
        case EInputType::Keyboard:
            return getKeyboard().getButton( boost::get<irr::EKEY_CODE>(d.Value ) ).Value;

//        case EInputType::Joystick:
//            return getJoystick().getButton(value);
        default: break;
    };
    return 0;
}


CInputManager::CInputManager() :
    _mouse(new CIrrlichtMouseDevice()),
    _keyboard(new CIrrlichtKeyboardDevice()),
    _joystick(new CIrrlichtJoystickDevice())
{

}




//TODO
// might throw an exception
//, ETapMode& mode, irr::u32 const& delay
const int
CInputManager::getState( irr::EKEY_CODE const& value)
{

            return getKeyboard().getButton(value).Value;

//        case EInputType::Joystick:
//            return getJoystick().getButton(value);
};


//const irr::u32& currentTime,
bool
CInputManager::handleEvent(const SEvent& event){

    //const irr::u32 currentTime = _device->getTimer()->getTime();
    //const irr::u32 currentTime = os::Timer::getTime()

    switch(event.EventType){

        case EET_KEY_INPUT_EVENT:
            getKeyboard().getButton(event.KeyInput.Key).Value = (int)event.KeyInput.PressedDown;

        break;


    case EET_JOYSTICK_INPUT_EVENT:
        {
            int i = 0;
            // Check each
            //irr::SEvent::SJoystickEvent::NUMBER_OF_BUTTONS
            while( i < CIrrlichtJoystickDevice::buttonsNumber){

                getJoystick()->getButton(i).Value = ( event.JoystickEvent.IsButtonPressed(i) );

                // check next button
                ++i;
            }

            // Do the same for each axis
            /*i = 0;
            while(i < irr::SEvent::SJoystickEvent::NUMBER_OF_AXES){

                // If
                getJoystick()->getButton(i).update( currentTime , isAxisEnabled(i,event.JoystickEvent.Axis[i]) );

                _axisState[ i ] = event.JoystickEvent.Axis[i];
//                if(event.JoystickEvent.Axis[i])
//                {
//                    //
//
//                    if(_axisState[ i ].second != event.JoystickEvent.Axis[i]){
//                        _axisState[ i ].first = currentTime;
                // Check next axis
                ++i;
            }
*/
/*
            /// Update POV
            if( event.JoystickEvent.POV == POV_DISABLED_POSITION){

                _pov.time = 0;
                //_pov.value = POV_DISABLED_POSITION;
            }
            else if( event.JoystickEvent.POV != _pov.value){

                _pov.time = currentTime;
                _pov.value = event.JoystickEvent.POV;

            }
            _pov.value = event.JoystickEvent.POV;

            //_pov = event.JoystickEvent.POV;
*/
        }
        //break;
        return true;


    case EET_MOUSE_INPUT_EVENT:

        //_mouseState = event.MouseInput
        //NUMBER_MOUSE_BUTTONS
        for(int i = 0; i < CIrrlichtMouseDevice::buttonsNumber; ++i){

            getMouse().getButton(i).Value =  ( 0 != (event.MouseInput.ButtonStates & i) );

        }
        break;


    default :
        break;


    }


   return false;
}



