#include "CInputManager.hpp"
#include "CBindDescriptor.hpp"
#include "CBind.hpp"
#include <fusion/logging/CConsoleLogger.hpp>
#include "mouseDevice.hpp"
#include "joystickDevice.hpp"
#include "keyboardDevice.hpp"

using namespace irr;
using namespace core;

namespace input {

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


CInputManager::CInputManager()
//:
  //  _mouse(new CIrrlichtMouseDevice()),
    //_keyboard(new CIrrlichtKeyboardDevice()),
//    _joystick(new CIrrlichtJoystickDevice())
{

}


CInputManager::~CInputManager() {
    // TODO vider joystick s'il y en a
    //BOOST_FOREACH

}




bool
CInputManager::activateJoysticks() {

    #ifndef _IRR_COMPILE_WITH_JOYSTICK_EVENTS_
        #error Your version of irrlicht may not generate joystick events
    #endif

    //static_assert()
   core::array<SJoystickInfo> joystickInfos;
   // BUG ici
   //_device->activateJoysticks(_joystickInfos);
   //_LOG_WARNING << "test 2";
   if( _device->activateJoysticks(joystickInfos) )
   {
        _device->getLogger()->log("Joystick support enabled ");
      for(u32 joystick = 0; joystick < joystickInfo.size(); ++joystick)
      {
          // TODO mettre le nom du fichier
          _device->getLogger()->log("Joystick plugged in");
          _joysticks.push_back(new CIrrlichtJoystickDevice(joystickInfos[joystick]));
//         std::cout << "\tName: '" << joystickInfo[joystick].Name.c_str() << "'" << std::endl;

      }
      return true;
   }

    //_device->getLogger()->log("Couldn't enable Joystick ");
    return false;


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
            _joysticks[event.JoystickEvent.Joystick]->update(event.JoystickEvent);
            /*int i = 0;
            // Check each
            //irr::SEvent::SJoystickEvent::NUMBER_OF_BUTTONS
            while( i < CIrrlichtJoystickDevice::buttonsNumber){

                getJoystick()->getButton(i).Value = ( event.JoystickEvent.IsButtonPressed(i) );

                // check next button
                ++i;
            }*/

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
        // Pour la souris tout devrait etre en static
        CIrrlichtMouseDevice::update(event.MouseInput);
        //_mouseState = event.MouseInput
        //NUMBER_MOUSE_BUTTONS
        /*for(int i = 0; i < CIrrlichtMouseDevice::buttonsNumber; ++i){

            getMouse().getButton(i).Value =  ( 0 != (event.MouseInput.ButtonStates & i) );

        }
        */
        break;


    default :
        break;


    }


   return false;
}

}   //!< end of namespace


