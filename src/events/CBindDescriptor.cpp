#include "CBindDescriptor.hpp"
#include "CInputManager.hpp"
//#include <fusion/core/CStringBuilder.hpp>
//#include <fusion/core/CStringExtractor.hpp>
#include <fusion/logging/ILogger.hpp>
#include <iostream>
#include <boost/bimap.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/assign/list_inserter.hpp>


namespace bbi = boost::bimaps;
using namespace irr;
using namespace core;

namespace input {
//std::wstring _unknown = L"Unknown";
const wchar_t* CBindDescriptor::StrUndefined = L"Unknown";

TKeyCodeMap CBindDescriptor::keycodeBimap;
TDeviceCodeMap CBindDescriptor::deviceCodeMap;

// Static
//SKeyConverter::TBimap SKeyConverter::keycodeBimap;
//
//
//SKeyConverter::SKeyConverter(){
//    static bool initialized = false;
//    if(!initialized){
//        initialized = true;
//        initializeKeycodes();
//    }
//}


CBindDescriptor::CBindDescriptor() :
    Mode(ETapMode::JustPressed)
    , DeviceId(0)
//    , Device(EInputType::None)
{

}


bool
CBindDescriptor::setup(int const& joyButton) {

    if( (joyButton < 0) || (joyButton >= irr::SEvent::SJoystickEvent::NUMBER_OF_BUTTONS) ){
        //Device = EInputType::None;
        reset();
        return false;
    }

    //Device = EInputType::None;
    SJoyButton temp = {joyButton};
    Value = temp;
    //JoyButton.Button = joyButton;
    return true;
}


void
CBindDescriptor::setup(irr::EKEY_CODE const& keyCode) {
    //Device  = EInputType::Keyboard;
    Value = keyCode;
}

bool
CBindDescriptor::setRepeatDelay(irr::u32 const& t) {
    RepeatTime = t;
}

void
CBindDescriptor::disableAutoRepeat() {
    RepeatTime = boost::none;
}


bool
CBindDescriptor::isAutorepeatEnabled() const {
    return RepeatTime;
}

void
CBindDescriptor::reset() {
    //Device= EInputType::None;
    Value = SNullType();
};

bool
CBindDescriptor::setup(int const& axisNo,EAxisDirection const& direction){

    if( (axisNo < 0) || (axisNo >= irr::SEvent::SJoystickEvent::NUMBER_OF_AXES) ){
        //EInputType::None;

        reset();
        return false;
    }

    //SStickMotion temp;
    //Device = EInputType::JoystickAxis;
    // Verifier si le stick existe ?
    SJoyAxis temp = { axisNo,direction };
//    StickAxis.Axis = axisNo;
//    StickAxis.Direction = direction;
    Value = temp;
    return true;
}


void
CBindDescriptor::setup(EPovDirection const& povDirection){
    Value = povDirection;
}


//#include <IEventReciever.h>
//void
//CBindDescriptor::setup(irr::EKEY_CODE const& keyCode) {
//    Device  = EInputType::Joystick;
//    KeyCode = keyCode;
//}


CBindDescriptor::CBindDescriptor(wchar_t* const& key) {
    setup(key);
}

bool
CBindDescriptor::setup(wchar_t* const& key) {

    try {
        setup(keycodeBimap.convert(key) );
        return true;
    }
    catch(std::out_of_range& e){

        std::string temp;
        fus::convertIntoNarrowString(key, temp);
        //throw std::runtime_error( "No key " );
        _LOG_ERROR << "Could not find key [" << temp << "] in bimap";
        reset();//Device = EInputType::None;
        return false;
    }

    //throw std::exception
    //return setup(EInputType::Keyboard, ret );
}


EInputType
CBindDescriptor::getInputType() const {
    return static_cast<EInputType>( Value.which() );
}


bool
CBindDescriptor::undefined() const {
    return ( (getInputType() == EInputType::None) );
};


// TODO a faire
bool
CBindDescriptor::operator==(const CBindDescriptor& d) const
{
    // Le device peut etre enregistre dans le variant !!
    // Value.which();
    if(Mode != d.Mode) return false;
    return (Value == d.Value);
}




// Binder un operateur >>
std::wstring
CBindDescriptor::generateDescription() const
{
    std::wstring desc;
    try {
        //
        const EInputType Device = getInputType();
        desc = deviceCodeMap.convert( Device);
        desc.append(L" ");

        // According to device, print specific thing
        switch (Device)
        {
            case EInputType::Keyboard:
                //static_cast<irr::EKEY_CODE>(Id)

                desc.append( keycodeBimap.convert( boost::get<irr::EKEY_CODE>(Value) ) );break;

            case EInputType::JoystickButton: break;
            case EInputType::None:
                return CBindDescriptor::StrUndefined;
                default:
                    break;
        }

        // According to mode
        // TODO Utiliser le bimap apres
        switch(Mode){
            case ETapMode::JustPressed: desc.append(L" jp");break;
            case ETapMode::DoublePressed: desc.append(L" dp");break;
            //case ETapMode::Pressed: desc.append(L" p");break;
            //case ETapMode::Released: desc.append(L" r");break;
            //case ETapMode::JustReleased: desc.append(L" jr");break;
            default: break;
        }

    //std::wcout << desc.c_str();
    }
    catch( std::out_of_range& e ) {
        //device
        _LOG_ERROR << "Couldn't find associated type [" << "" << "] ";
        desc.append( StrUndefined );
    }
    return desc;
}


}


//    _povMap.insert( TDeviceCodeMap::TAssociation( CEventManager::POV_UP,  L"Up"));
//    _povMap.insert( TDeviceCodeMap::TAssociation( CEventManager::POV_DOWN,L"Down"));
//    _povMap.insert( TDeviceCodeMap::TAssociation( CEventManager::POV_RIGHT,L"Right"));
//    _povMap.insert( TDeviceCodeMap::TAssociation( CEventManager::POV_DOWN, L"Left"));

//
//void
//CBindDescriptor::reset(){
//    Device = EInputType::None;
//}
//
