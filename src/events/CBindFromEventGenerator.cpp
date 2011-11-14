#include "CBindDescriptor.hpp"
#include "CBindFromEventGenerator.hpp"
#include "../game_engine.hpp"
//#include "CInputManager.hpp"
//#include <fusion/core/CStringBuilder.hpp>
//#include <fusion/core/CStringExtractor.hpp>
//#include <fusion/logging/ILogger.hpp>
#include <iostream>

using namespace irr;
using namespace core;



CBindFromEventGenerator::CBindFromEventGenerator () :
    //_inputMgr(inputMgr),
    _timeOfProcessingEnd(0)
{

}

//bool
//CBindFromEventGenerator::processEvent( TTimeUnit const& time,irr::SEvent const& e) {
//
//    bool state = false;
//
//    //! if could generate
//    if( generateDescriptor( e, Descriptor ,state) )
//    {
//        //
//        _timeOfProcessingEnd = time + 200;
//        //! on devrait mettre en cache l'evenement
//        //_cachedState.
//        //_pastStates.push_back
//        return true;
//    }
//    return false;
//}


bool
CBindFromEventGenerator::check(TTimeUnit const& currentTime,CBindDescriptor& result)
{
    //|| (_pastStates.size() > 5)
    if( !Descriptor.undefined() && (currentTime > _timeOfProcessingEnd) )
    {
        result = Descriptor;
        return true;
    }
    return false;
}


// TODO renommer en processEvent
//boost::optional<CBindDescriptor>
//, CBindDescriptor& result
bool
CBindFromEventGenerator::processEvent( TTimeUnit const& time, irr::SEvent const& e )
{

    bool state = false;
    CBindDescriptor temp;

    if( generateDescriptor( e, Descriptor,state) )
    {

        if(Descriptor.undefined() ){

            Descriptor = temp;
            _timeOfProcessingEnd = time + 200;
            // TODO update cache
            return true;
        }
        else if( temp == Descriptor ){
            // TODO update cache
            return true;
        }
        else {
            return false;
        }

    }


/*
    //!baseliningBind
    //! if no bind found
    // if ( !baseliningBind() )
    if(Descriptor.undefined() )
    {

        //CBindDescriptor temp;
        //! if could generate
        if( generateDescriptor( e, Descriptor,state) )
        {
            // descriptor
            _timeOfProcessingEnd = time + 200;
            //! on devrait mettre en cache l'evenement
            //_cachedState.
            //_pastStates.push_back
        }
//        return false;
    }
    //! stop processing
    else
    else
    {

        //bool state = false;
        CBindDescriptor temp;
        //! if could generate
        if( generateDescriptor( e, temp,state) && (temp == Descriptor ) )
        {
            //!
            // update state
        }
    }*/

    //BOOST_ASSERT( !_pastStates.empty() );

/*
    ETapMode mode = ETapMode::JustPressed;

    // else guess mode according to states
    //time-_timeOfDescriptorRetrieval  > 0
    // 200 est le temps qui permet de decider quel
    //// Si la taille est sup à 2 et si duration > 100 => arret premature
    if( (time > _timeOfProcessingEnd) || (_pastStates.size() > 5)){

        // Process bind mode
        _INFO <<  "Recorded states size " << _pastStates.size();

        switch(_pastStates.size())
        {
            case 1:
                mode = (_pastStates.top().first) ? ETapMode::JustPressed : ETapMode::JustReleased;
                break;

            case 2:
                mode = ETapMode::JustPressed;
                break;

            case 3:
                mode = ETapMode::JustPressed;
                break;

            case 4:
                mode = ETapMode::DoublePressed;
                break;

            case 5: // double pressed
                mode = ETapMode::DoublePressed;
                break;
            // ce cas ne devrait jamais arriver
            default: break;
        }


        // TODO a implementer !!
        Descriptor.Mode = mode;

        // Analyze past
        ret = Descriptor;
    }
    // Elapsed time for detection of a bind
    // User might destroy this class
    else
    {
*/
//        bool bRet = _cachedState.update(time,Descriptor, _inputMgr.retrieveStateFromDescriptor(Descriptor) );
//        if( bRet )
//        {
//
//
//            // Register old state_cachedState.OldDuration
//            _pastStates.push( std::make_pair( !_cachedState.State, _cachedState.QuickDelayRespected) );
//        }

  //  }


return false;
//    return ret;
}



bool CBindFromEventGenerator::generateDescriptor(irr::SEvent const& e,CBindDescriptor& descriptor, bool& state)
{
    bool generated = false;
    //
    switch(e.EventType)
    {

        case EET_KEY_INPUT_EVENT:
            descriptor.setup(e.KeyInput.Key);
            state = e.KeyInput.PressedDown;
            return true;

        case EET_MOUSE_INPUT_EVENT:
            break;

        case EET_JOYSTICK_INPUT_EVENT:
            switch (e.JoystickEvent.Type)
            {
                //
                case EJE_POV_MOVED:
                case EJE_AXIS_MOVED:
                    // ENeutral, EAxisDirection::Positive
                    //descriptor.setup( e.JoystickEvent.MovedAxis,);
                    break;

                //!
                case EJE_BUTTON_PRESSED:
                case EJE_BUTTON_RELEASED:
                    descriptor.setup( (irr::u16) e.JoystickEvent.Button);
                    state = ( e.JoystickEvent.Type == EJE_BUTTON_RELEASED) ? false : true;
                    return true;
                default:
                    break;
            }

            break;

        default: break;
    };

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
