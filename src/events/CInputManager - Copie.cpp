#include "CInputManager.hpp"
#include <fusion/logging/CConsoleLogger.hpp>

using namespace irr;
using namespace core;

//irr::u32
irr::core::array<SJoystickInfo> CInputManager::_joystickInfos;
std::array<irr::u32,irr::KEY_KEY_CODES_COUNT> CInputManager::_keyboardState;
std::array<irr::u32,irr::SEvent::SJoystickEvent::NUMBER_OF_BUTTONS > CInputManager::_joystickButtonsState;
//std::array< CInputManager::TAxisTuple ,irr::SEvent::SJoystickEvent::NUMBER_OF_AXES > CInputManager::_axisState;
std::array< irr::s16 ,irr::SEvent::SJoystickEvent::NUMBER_OF_AXES > CInputManager::_axisState;

//u32
irr::s32 CInputManager::POV_DISABLED_POSITION = 65535;

CInputManager::TAxisTuple CInputManager::_pov;
std::array<irr::u32,6> CInputManager::_mouseButtons;

irr::u16 CInputManager::Threshold = 16000;
//irr::ITimer* CInputManager::_timer = 0;
//irr::IrrlichtDevice* CInputManager::_device = 0;


irr::s32 CInputManager::POV_UP      = 0;
irr::s32 CInputManager::POV_RIGHT   = 9000;
irr::s32 CInputManager::POV_DOWN    = 18000;
irr::s32 CInputManager::POV_LEFT    = 27000;


CInputManager::CInputManager()
{

}

//irr::IrrlichtDevice* device
void
CInputManager::initStaticMembers() {

    _mouseButtons.fill(0);
    _keyboardState.fill(0);
    _joystickButtonsState.fill(0);
    _axisState.fill(0);

    _pov.value = 0;
    _pov.time = 0;

    Threshold = 16000;

    //setDevice( device );
    //_device = device;

}

bool
CInputManager::isAxisPositive(const irr::s16& axis){
    //const int& value = _axisState[axis].value;
    const int& value = _axisState[axis];
    return ( (value != 0) && (value > CInputManager::Threshold)   );
}

bool
CInputManager::isAxisNegative(const irr::s16& axis){
    const int& value = _axisState[axis];
    return ( (value != 0) && (value < -CInputManager::Threshold)   );
   // return ( (_axisState[axis].value < -CInputManager::Threshold) && (_axisState[axis].value != 0) );
}


//void
//CInputManager::setDevice(irr::IrrlichtDevice* device)
//{
//    //
//    _device = device;
////    if(_device){
////        _device->setEventReceiver( this );
////    }
//}



bool
CInputManager::processEvent(const irr::u32& currentTime, const SEvent& event){

    //const irr::u32 currentTime = _device->getTimer()->getTime();
    //const irr::u32 currentTime = os::Timer::getTime()

    switch(event.EventType){



    case EET_KEY_INPUT_EVENT:

// TODO si tt etait dans un seul et mm tableau
// on pourrait creer une fonction qui met a jour tel element du tab = factorisation de code
// Cette ligne pourrait remplacer tt ce qui suit
//        _keyboardState[event.KeyInput.Key] = std::min(
//                    _keyboardState[event.KeyInput.Key]*event.KeyInput.PressedDown,
//                    event.KeyInput.PressedDown*_timer->getTime()
//                    );

        // if pressed down
        if(event.KeyInput.PressedDown){

            // it key just pressed
            if(_keyboardState[event.KeyInput.Key] == 0){

                //  Record time of keypress
                _keyboardState[event.KeyInput.Key] = currentTime;
            }
            // otherwise we do nothing
        }
        // if key released
        else {
            _keyboardState[event.KeyInput.Key] = 0;
        }
        break;


    case EET_JOYSTICK_INPUT_EVENT:
        {
            int i = 0;
            // Check each
            while( i < irr::SEvent::SJoystickEvent::NUMBER_OF_BUTTONS){

                // if button pressed
                if(event.JoystickEvent.IsButtonPressed(i)){

                    // and if it's a new button pressed
                    if( !isJoystickButtonDown(i) ){
                        // record time of button pressed
                        _joystickButtonsState[i] = currentTime;
                    }
                }
                // else we record it as a
                else {
                    _joystickButtonsState[i] = 0;
                }

                // check next button
                ++i;
            }

            // Do the same for each axis
            i = 0;
            while(i < irr::SEvent::SJoystickEvent::NUMBER_OF_AXES){

                // If


                _axisState[ i ] = event.JoystickEvent.Axis[i];
//                if(event.JoystickEvent.Axis[i])
//                {
//                    //
//
//                    if(_axisState[ i ].second != event.JoystickEvent.Axis[i]){
//                        _axisState[ i ].first = currentTime;
//                    }
//                }
//                else {
//                    _axisState[ i ] = 0;
//                }

                // Check next axis
                ++i;
            }

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

        }
        //break;
        return true;


    case EET_MOUSE_INPUT_EVENT:
        //_mouseState = event.MouseInput
        for(int i = 0; i < NUMBER_MOUSE_BUTTONS; ++i){

            if( 0 != (event.MouseInput.ButtonStates & i)) {

                if( _mouseButtons[ i ] == 0){
                    _mouseButtons[ i ] = currentTime;
                }
            }
            else {
                //
                _mouseButtons[ i ] = 0;
            }
        }
        break;


    default :
        break;


    }


//    if(_eventReceiver != 0){
//        _eventReceiver->OnEvent(event);
//    }
    // Relay the event
//    for ( std::size_t i(0),size(mEventReceivers.size()); i < size; ++i ){
//
//        if ( mEventReceivers[i]->OnEvent(event) ){
//            return true;
//        }
//    }
   return false;
}

//
//void
//CInputManager::setEventReceiver(irr::IEventReceiver * receiver)
//{
//
//   _eventReceiver = receiver;
//}
//
//void
//CInputManager::AddEventReceiver(irr::IEventReceiver * receiver_)
//{
//   mEventReceivers.push_back(receiver_);
//}
//
//bool
//CInputManager::RemoveEventReceiver(irr::IEventReceiver * receiver_)
//{
//   for ( unsigned int i=0; i<mEventReceivers.size(); ++i ){
//
//        if ( mEventReceivers[i] == receiver_ ){
//
//            mEventReceivers.erase(i);
//            return true;
//        }
//   }
//   return false;
//}



