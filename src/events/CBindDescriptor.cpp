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

//
void
initializeKeycodes(){

    // TODO http://www.boost.org/doc/libs/1_47_0/libs/bimap/example/bimap_and_boost/assign.cpp
    //SBimap<std::wstring,irr::EKEY_CODE> &keycodeBimap = keycodeBimap;
    TKeyCodeMap& keycodeBimap = CBindDescriptor::keycodeBimap;

try {
    boost::assign::insert( keycodeBimap.Bimap.left )
        (KEY_LBUTTON,L"LBUTTON")
        (KEY_CANCEL,L"CANCEL")
        (KEY_MBUTTON,L"MBUTTON")
        (KEY_KEY_0,L"0")
        (KEY_KEY_1,L"1")
        (KEY_KEY_2,L"2")
        (KEY_KEY_3,L"3")
        (KEY_KEY_4,L"4")
        (KEY_KEY_5,L"5")
        (KEY_KEY_6,L"6")
        (KEY_KEY_7,L"7")
        (KEY_KEY_8,L"8")
        (KEY_KEY_9,L"9")
        (KEY_KEY_A,L"A")
        (KEY_KEY_B,L"B")
        (KEY_KEY_C,L"C")
        (KEY_KEY_D,L"D")
        (KEY_KEY_E,L"E")
        (KEY_KEY_F,L"F")
        (KEY_KEY_G,L"G")
        (KEY_KEY_H,L"H")
        (KEY_KEY_I,L"I")
        (KEY_KEY_J,L"J")
        (KEY_KEY_K,L"K")
        (KEY_KEY_L,L"L")
        (KEY_KEY_M,L"M")
        (KEY_KEY_N,L"N")
        (KEY_KEY_O,L"O")
        (KEY_KEY_P,L"P")
        (KEY_KEY_Q,L"Q")
        (KEY_KEY_R,L"R")
        (KEY_KEY_S,L"S")
        (KEY_KEY_T,L"T")
        (KEY_KEY_U,L"U")
        (KEY_KEY_V,L"V")
        (KEY_KEY_W,L"W")
        (KEY_KEY_X,L"X")
        (KEY_KEY_Y,L"Y")
        (KEY_KEY_Z,L"Z")
        (KEY_F1,L"F1")
        (KEY_F2,L"F2")
        (KEY_F3,L"F3")
        (KEY_F4,L"F4")
        (KEY_F5,L"F5")
        (KEY_F6,L"F6")
        (KEY_F7,L"F7")
        (KEY_F8,L"F8")
        (KEY_F9,L"F9")
(KEY_F10,L"F10")
(KEY_F11,L"F11")
(KEY_F12,L"F12")
(KEY_F13,L"F13")
(KEY_F14,L"F14")
(KEY_F15,L"F15")
(KEY_F16,L"F16")
(KEY_F17,L"F17")
(KEY_F18,L"F18")
(KEY_F19,L"F19")
(KEY_F20,L"F20")
(KEY_F21,L"F21")
(KEY_F22,L"F22")
(KEY_F23,L"F23")
(KEY_F24,L"F24")
(KEY_NUMPAD0,L"NUMPAD0")
(KEY_NUMPAD1,L"NUMPAD1")
(KEY_NUMPAD2,L"NUMPAD2")
(KEY_NUMPAD3,L"NUMPAD3")
(KEY_NUMPAD4,L"NUMPAD4")
(KEY_NUMPAD5,L"NUMPAD5")
(KEY_NUMPAD6,L"NUMPAD6")
(KEY_NUMPAD7,L"NUMPAD7")
(KEY_NUMPAD8,L"NUMPAD8")
(KEY_NUMPAD9,L"NUMPAD9")
(KEY_LWIN,L"LWIN")
(KEY_RWIN,L"RWIN")
(KEY_APPS,L"APPS")
(KEY_SLEEP,L"SLEEP")
(KEY_MBUTTON,L"MBUTTON")
(KEY_XBUTTON1,L"XBUTTON1")
(KEY_XBUTTON2,L"XBUTTON2")
(KEY_BACK,L"BACK")
(KEY_TAB,L"TAB")
(KEY_CLEAR,L"CLEAR")
(KEY_RETURN,L"RETURN")
(KEY_SHIFT,L"SHIFT")
(KEY_CONTROL,L"CONTROL")
(KEY_MENU,L"MENU")
(KEY_PAUSE,L"PAUSE")
(KEY_CAPITAL,L"CAPITAL")
(KEY_KANA,L"KANA")
(KEY_HANGUEL,L"HANGUEL")
(KEY_HANGUL,L"HANGUL")
(KEY_JUNJA,L"JUNJA")
(KEY_FINAL,L"FINAL")
(KEY_KANJI,L"KANJI")
(KEY_ESCAPE,L"ESCAPE")
(KEY_CONVERT,L"CONVERT")
(KEY_NONCONVERT,L"NONCONVERT")
(KEY_ACCEPT,L"ACCEPT")
(KEY_MODECHANGE,L"MODECHANGE")
(KEY_SPACE,L"SPACE")
(KEY_PRIOR,L"PRIOR")
(KEY_NEXT,L"NEXT")
(KEY_END,L"END")
(KEY_HOME,L"HOME")
(KEY_LEFT,L"Left")
(KEY_UP,L"Up")
(KEY_RIGHT,L"Right")
(KEY_DOWN,L"Down")
(KEY_SELECT,L"SELECT")
(KEY_PRINT,L"PRINT")
(KEY_PRINT,L"DOWN")
(KEY_EXECUT,L"EXECUT")
(KEY_SNAPSHOT,L"SNAPSHOT")
(KEY_INSERT,L"INSERT")
(KEY_DELETE,L"DELETE")
(KEY_HELP,L"HELP")
(KEY_INSERT,L"INSERT")

(KEY_MULTIPLY,L"MULTIPLY")
(KEY_ADD,L"ADD")
(KEY_SEPARATOR,L"SEPARATOR")
(KEY_SUBTRACT,L"SUBTRACT")
(KEY_DECIMAL,L"DECIMAL")
(KEY_DIVIDE,L"DIVIDE")
(KEY_NUMLOCK,L"NUMLOCK")
(KEY_SCROLL,L"SCROLL")
(KEY_LSHIFT,L"LSHIFT")
(KEY_RSHIFT,L"RSHIFT")
(KEY_LCONTROL,L"LCONTROL")
(KEY_RCONTROL,L"RCONTROL")
(KEY_LMENU,L"LMENU")
(KEY_RMENU,L"RMENU")
(KEY_PLUS,L"PLUS")
(KEY_COMMA,L"COMMA")
(KEY_MINUS,L"MINUS")
(KEY_PERIOD,L"PERIOD")
(KEY_ATTN,L"ATTN")
(KEY_CRSEL,L"CRSEL")
(KEY_CRSEL,L"CRSEL")
(KEY_EXSEL,L"EXSEL")
(KEY_EREOF,L"EREOF")
(KEY_PLAY,L"PLAY")
(KEY_ZOOM,L"ZOOM")
(KEY_PA1,L"PA1")
(KEY_OEM_CLEAR,L"OEM_CLEAR")
        ;
}
catch(...){
    _LOG_WARNING << "Error while initializing key bimap";
}

}


void
initializeDeviceCodes()
{
    TDeviceCodeMap& inputDevices = CBindDescriptor::deviceCodeMap;

    boost::assign::insert(inputDevices.Bimap.left )
        (EInputType::None,L"Unknown")
        (EInputType::Mouse,L"Mou")
        (EInputType::Keyboard,L"Key")
        (EInputType::JoystickAxis,L"JoyAxis")
        (EInputType::JoystickButton,L"JoyButton")
;

//    inputDevices.Bimap.insert( TDeviceCodeMap::TAssociation(EInputType::None,L"Unknown"));
//    inputDevices.Bimap.insert( TDeviceCodeMap::TAssociation(EInputType::Mouse,L"Mou"));
//    inputDevices.Bimap.insert( TDeviceCodeMap::TAssociation(EInputType::Keyboard,L"Key"));
//    inputDevices.Bimap.insert( TDeviceCodeMap::TAssociation(EInputType::JoystickAxis,L"JoyAxis"));
//    inputDevices.Bimap.insert( TDeviceCodeMap::TAssociation(EInputType::JoystickButton,L"JoyButton"));

}

/*bool setup(const NInputDevice::EId&, int const&);
bool setup(wchar_t const& key);
bool setup(char const& key);
bool setup(char* const strType);
*/

// Returns false, if not possible
// Void lander des exceptions a a place
//bool
//CBindDescriptor::setup(const EInputType& device,const int& value)
//{
//    Device = device;
//    Id = value;
//    return true;
//}

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

//bool setup(char* const strType);

//const std::wstring name,
//CBindDescriptor::CBindDescriptor(const EInputType& device,const int& id)
//{
//    //return
//    setup(device,id);
//}

EInputType
CBindDescriptor::getInputType() const {
    return static_cast<EInputType>( Value.which() );
}


bool
CBindDescriptor::undefined() const {
    return ( (getInputType() == EInputType::None) );
    //return Value.empty() ;

};


// TODO a faire
bool
CBindDescriptor::operator==(const CBindDescriptor& d) const
{
    // Le device peut etre enregistre dans le variant !!
    // Value.which();
    //if(Device != d.Device) return false;
    if(Mode != d.Mode) return false;
    //switch(Device)(Id != map.Id) return false;
    return (Value == d.Value);
    //return true;
}

//bool
//CBindDescriptor::operator<(const CBindDescriptor& descriptor) const {
////    return (Device != descriptor.Device);
////    if(Device != descriptor.Device ){
////        return
////    }
//    return KeyCode < descriptor.KeyCode;
//}


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
            return false;
            default:
                break;
        }

        // According to mode
        // TODO Utiliser le bimap apres
        switch(Mode){
            case ETapMode::JustPressed: desc.append(L" jp");break;
            case ETapMode::DoublePressed: desc.append(L" dp");break;
            case ETapMode::Pressed: desc.append(L" p");break;
            case ETapMode::Released: desc.append(L" r");break;
            case ETapMode::JustReleased: desc.append(L" jr");break;
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
