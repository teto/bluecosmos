#include "CBindDescriptor.hpp"
#include "CBindFromEventGenerator.hpp"
#include "../game_engine.hpp"
#include "CInputManager.hpp"
//#include <fusion/core/CStringBuilder.hpp>
//#include <fusion/core/CStringExtractor.hpp>
//#include <fusion/logging/ILogger.hpp>
#include <iostream>

using namespace irr;
using namespace core;


CBindFromEventGenerator::CBindFromEventGenerator (CInputManager& inputMgr) :
    _inputMgr(inputMgr),
    _timeOfDescriptorRetrieval(0)
{

}


boost::optional<CBindDescriptor>
CBindFromEventGenerator::check( irr::u32 const& time )  {

    boost::optional<CBindDescriptor> ret;

    //
    if(!processingBind()){
        return ret;
    }

    // else guess mode according to states
    //time-_timeOfDescriptorRetrieval  > 0
    // 200 est le temps qui permet de decider quel
    if(time-_timeOfDescriptorRetrieval < 200){
        _tempDescriptor.Mode = _cachedState.update(time, _inputMgr.retrieveStateFromDescriptor(_tempDescriptor) );
    }
    // Elapsed time for detection of a bind
    // User might destroy this class
    else {
        ret = _tempDescriptor;
    }

    return ret;
}



bool
CBindFromEventGenerator::processEvent( irr::u32 const& time,irr::SEvent const& e) {



    // If descriptor not defined yet
    if(_tempDescriptor.undefined() ){

        switch(e.EventType){

            case EET_KEY_INPUT_EVENT:

                // React on press only
                if(e.KeyInput.PressedDown ) {
                    _tempDescriptor.setup(e.KeyInput.Key);
                    _timeOfDescriptorRetrieval = time;
                    _cachedState.update(time,true);
                }
                return true;

            default: break;
        };

    }

    return false;
}


// STATIC FUNCTION
// TODO a deplacer dans InputManager ?
/*
// est genere a chaque tour du coup on sait pas si y a de changement .
        case EET_JOYSTICK_INPUT_EVENT:

            if( CBindDescriptor::matchesMask(mask, NInputType::JOY_BTN ) ){

                int noButton = 0;

                // retrieve first pressed button
                while( noButton < irr::SEvent::SJoystickEvent::NUMBER_OF_BUTTONS){
                    if( CEventManager::isJoystickButtonDown( noButton ) ){
                        return setup(NInputType::JOY_BTN,noButton);
                    }
                    ++noButton;
                }
            }

            if( CBindDescriptor::matchesMask(mask, NInputType::JOY_POV ) && CEventManager::povBeingUsed() ){

                return setup(NInputType::JOY_POV, CEventManager::getPOV() );
            }


//            if( CBindDescriptor::matchesMask(mask, NInputType::JOY_POV ) && CEventManager::povBeingUsed() ){
//
//            }

//| NInputType::JOY_AXIS_PLUS
            if( CBindDescriptor::matchesMask(mask, NInputType::JOY_AXIS_MINUS  ) ){

                for(irr::u16 i = 0; i < irr::SEvent::SJoystickEvent::NUMBER_OF_AXES;++i){

                    //_INFO << "aXIs" << event.Axis[i] << "seuil" << _threshold;
                    // TODO remplacer le Seuil ici
                    //if(e.JoystickEvent.Axis[i] > CEventManager::Threshold){
                    if( CEventManager::isAxisPositive(i) ){
                        //break;
                        return setup(NInputType::JOY_AXIS_PLUS,i);
                    }
                    //else if(e.JoystickEvent.Axis[i] < -CEventManager::Threshold) {
                    else if( CEventManager::isAxisNegative(i) ) {
                        return setup(NInputType::JOY_AXIS_MINUS,i);
                    }
                }
            }




            break;


        case EET_MOUSE_INPUT_EVENT:

//EMIE_MOUSE_MOVED
// Reste a distinguer mouvement du clic
                //EINPUT_MOU_MOVE
                //EINPUT_MOU_BTN

            if( CBindDescriptor::matchesMask(mask, NInputType::MOU_WHEEL ) && e.MouseInput.Wheel != 0 ){
                return setup(  NInputType::MOU_WHEEL, e.MouseInput.Wheel );
            }

            if( CBindDescriptor::matchesMask(mask, NInputType::MOU_BTN ) ){

                int noButton = 0;

                // retrieve first pressed button
                while( noButton < CEventManager::NUMBER_MOUSE_BUTTONS){

                    if( CEventManager::isMouseButtonDown( noButton ) ){
                        return setup(NInputType::MOU_BTN,noButton);
                    }
                    ++noButton;
                }
                //isMouseButtonDown
//                return setup(  NInputType::MOU_WHEEL, e.MouseInput.Wheel );
            }

            if( CBindDescriptor::matchesMask(mask, NInputType::MOU_WHEEL ) ){
                if(e.MouseInput.Wheel > 0){
                    return setup(EInputType::Mouse, 1);
                }
                else if(e.MouseInput.Wheel < 0){
                    return setup(NInputType::MOU_WHEEL, -1);
                }
            }
//            switch(){
//                processEvent(e.MouseInput);
//            }
            break;

        default:
            return false;


    };


    // checks if within masks
    return false;
}




/*
irr::core::stringw
CBindDescriptor::valueToString() const
{
    irr::core::stringw str;
    switch(_type) {

        //
        case NInputType::KEY:
            return keyCodeToString(static_cast<irr::EKEY_CODE>(_value) );

// mousemove too !
    case NInputType::MOU_WHEEL:
        //desc = L"Mouse";
        if( _value >= 0) return L"Up";
        if( _value <  0) return L"Down";
        //desc = L"Mouse %s %s",m_iMouseAxis==0?L"X":L"Y",m_iMouseDirection>0?L"+":L"-");
        break;

    case NInputType::MOU_BTN:
            switch(_value){

                case EMBSM_LEFT: return L"Left";
                case EMBSM_RIGHT: return L"Right";
                case EMBSM_MIDDLE: return L"Middle";
                case 5: return L"4";
                case 6: return L"5";
                default: return L"Unknown";
            };

        break;

        case NInputType::JOY_AXIS_PLUS:

            return L"Vertical";

        case NInputType::JOY_AXIS_MINUS:
            return L"Horizontal";

        case NInputType::JOY_BTN:
//            switch(_value){
//                case EMBSM_LEFT: return L"Left";
//                case EMBSM_RIGHT: return L"Right";
//                case EMBSM_MIDDLE: return L"Middle";
//            };
            str += _value;
            return str;
            //return L"Button N°";

        case NInputType::JOY_POV:
            // TODO les definir comme constante
            //povToString(_value);
            if( _value == CEventManager::POV_UP)        return L"Up";
            if( _value == CEventManager::POV_RIGHT)     return L"Right";
            if( _value == CEventManager::POV_DOWN)    return L"Down";
            if( _value == CEventManager::POV_LEFT)    return L"Left";

//
//            str += _value;
//            return str;


        default:
            break;
    }
// + _name + "\" type=\""+ _type + "\" value=\"" + _value "\">";
    //std::wstring res = fus::TWCharStringBuilder("<input name=\"")( _name.c_str() )("\" type=\"")(typeToString(_type).c_str())("\" value=\"")(generateDescription().c_str())( "\" />");
    //std::wstring res = fus::TWCharStringBuilder("<input name=\"")( _name.c_str() )("\" description=\"")(generateDescription().c_str())( "\" />");

    return _unknown;
}
*/

/*

// TODO _threshold en constante
bool
CBindDescriptor::matchesJoystickEvent(const irr::SEvent::SJoystickEvent& event) const {

    switch(_type){
        case NInputType::JOY_BTN:
            return CEventManager::isJoystickButtonDown(_value);
            //return event.IsButtonPressed(_value);

        case NInputType::JOY_POV:
            return CEventManager::povBeingUsed();

        case NInputType::JOY_AXIS_MINUS:

            return(event.Axis[_value] < - CEventManager::Threshold);

        case NInputType::JOY_AXIS_PLUS:
            return(event.Axis[_value] > CEventManager::Threshold);

        default:
            break;
    };


    return false;
}


*/