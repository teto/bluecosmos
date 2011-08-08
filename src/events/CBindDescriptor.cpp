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
    , Device(EInputType::None)
{

}

//
void
initializeKeycodes(){

    // TODO http://www.boost.org/doc/libs/1_47_0/libs/bimap/example/bimap_and_boost/assign.cpp
    //SBimap<std::wstring,irr::EKEY_CODE> &keycodeBimap = keycodeBimap;
    TKeyCodeMap& keycodeBimap = CBindDescriptor::keycodeBimap;

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


        ;

    //keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_LBUTTON,L"LBUTTON") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_RBUTTON,L"RBUTTON") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_CANCEL,L"CANCEL") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_MBUTTON,L"MBUTTON") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_XBUTTON1,L"XBUTTON1") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_XBUTTON2,L"XBUTTON2") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_BACK,L"BACK") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_TAB,L"TAB") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_CLEAR,L"CLEAR") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_RETURN,L"RETURN") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_SHIFT,L"SHIFT") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_CONTROL,L"CONTROL") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_MENU,L"MENU") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_PAUSE,L"PAUSE") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_CAPITAL,L"CAPITAL") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KANA,L"KANA") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_HANGUEL,L"HANGUEL") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_HANGUL,L"HANGUL") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_JUNJA,L"JUNJA") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_FINAL,L"FINAL") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KANJI,L"KANJI") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_ESCAPE,L"ESCAPE") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_CONVERT,L"CONVERT") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_NONCONVERT,L"NONCONVERT") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_ACCEPT,L"ACCEPT") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_MODECHANGE,L"MODECHANGE") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_SPACE,L"SPACE") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_PRIOR,L"PRIOR") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_NEXT,L"NEXT") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_END,L"END") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_HOME,L"HOME") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_LEFT,L"Left") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_UP,L"Up") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_RIGHT,L"Right") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_DOWN,L"Down") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_SELECT,L"SELECT") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_PRINT,L"PRINT") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_PRINT,L"DOWN") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_EXECUT,L"EXECUT") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_SNAPSHOT,L"SNAPSHOT") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_INSERT,L"INSERT") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_DELETE,L"DELETE") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_HELP,L"HELP") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_INSERT,L"INSERT") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_0,L"0") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_1,L"1") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_2,L"2") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_3,L"3") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_4,L"4") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_5,L"5") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_6,L"6") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_7,L"7") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_8,L"8") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_9,L"9") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_A,L"A") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_B,L"B") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_C,L"C") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_D,L"D") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_E,L"E") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_F,L"F") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_G,L"G") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_H,L"H") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_I,L"I") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_J,L"J") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_K,L"K") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_L,L"L") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_M,L"M") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_N,L"N") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_O,L"O") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_P,L"P") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_Q,L"Q") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_R,L"R") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_S,L"S") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_T,L"T") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_U,L"U") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_V,L"V") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_W,L"W") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_X,L"X") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_Y,L"Y") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_KEY_Z,L"Z") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_LWIN,L"LWIN") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_RWIN,L"RWIN") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_APPS,L"APPS") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_SLEEP,L"SLEEP") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_NUMPAD0,L"NUMPAD0") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_NUMPAD1,L"NUMPAD1") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_NUMPAD2,L"NUMPAD2") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_NUMPAD3,L"NUMPAD3") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_NUMPAD4,L"NUMPAD4") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_NUMPAD5,L"NUMPAD5") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_NUMPAD6,L"NUMPAD6") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_NUMPAD7,L"NUMPAD7") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_NUMPAD8,L"NUMPAD8") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_NUMPAD9,L"NUMPAD9") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_MULTIPLY,L"MULTIPLY") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_ADD,L"ADD") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_SEPARATOR,L"SEPARATOR") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_SUBTRACT,L"SUBTRACT") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_DECIMAL,L"DECIMAL") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_DIVIDE,L"DIVIDE") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F1,L"F1") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F2,L"F2") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F3,L"F3") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F4,L"F4") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F5,L"F5") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F6,L"F6") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F7,L"F7") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F8,L"F8") );
//    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F9,L"F9") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F10,L"F10") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F11,L"F11") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F12,L"F12") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F13,L"F13") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F14,L"F14") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F15,L"F15") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F16,L"F16") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F17,L"F17") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F18,L"F18") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F19,L"F19") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F20,L"F20") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F21,L"F21") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F22,L"F22") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F23,L"F23") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_F24,L"F24") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_NUMLOCK,L"NUMLOCK") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_SCROLL,L"SCROLL") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_LSHIFT,L"LSHIFT") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_RSHIFT,L"RSHIFT") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_LCONTROL,L"LCONTROL") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_RCONTROL,L"RCONTROL") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_LMENU,L"LMENU") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_RMENU,L"RMENU") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_PLUS,L"PLUS") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_COMMA,L"COMMA") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_MINUS,L"MINUS") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_PERIOD,L"PERIOD") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_ATTN,L"ATTN") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_CRSEL,L"CRSEL") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_CRSEL,L"CRSEL") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_EXSEL,L"EXSEL") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_EREOF,L"EREOF") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_PLAY,L"PLAY") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_ZOOM,L"ZOOM") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_PA1,L"PA1") );
    keycodeBimap.Bimap.insert( TKeyCodeMap::TAssociation(KEY_OEM_CLEAR,L"OEM_CLEAR") );
}


void
initializeDeviceCodes()
{
    TDeviceCodeMap& inputDevices = CBindDescriptor::deviceCodeMap;
    inputDevices.Bimap.insert( TDeviceCodeMap::TAssociation(EInputType::None,L"Unknown"));
    inputDevices.Bimap.insert( TDeviceCodeMap::TAssociation(EInputType::Mouse,L"Mou"));
    inputDevices.Bimap.insert( TDeviceCodeMap::TAssociation(EInputType::Keyboard,L"Key"));
    inputDevices.Bimap.insert( TDeviceCodeMap::TAssociation(EInputType::JoystickAxis,L"JoyAxis"));
    inputDevices.Bimap.insert( TDeviceCodeMap::TAssociation(EInputType::JoystickButton,L"JoyButton"));

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
        Device = EInputType::None;
        return false;
    }

    Device = EInputType::None;
    SJoyButton temp = {joyButton};
    Value = temp;
    //JoyButton.Button = joyButton;
    return true;
}


void
CBindDescriptor::setup(irr::EKEY_CODE const& keyCode) {
    Device  = EInputType::Keyboard;
    Value = keyCode;
}



bool
CBindDescriptor::setup(int const& axisNo,EAxisDirection const& direction){

    if( (axisNo < 0) || (axisNo >= irr::SEvent::SJoystickEvent::NUMBER_OF_AXES) ){
        EInputType::None;
        return false;
    }

    //SStickMotion temp;
    Device = EInputType::JoystickAxis;
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
        Device = EInputType::None;
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


bool
CBindDescriptor::undefined() const {
    return ( (Device == EInputType::None) );
    //return Value.empty() ;

};


// TODO a faire
bool
CBindDescriptor::operator==(const CBindDescriptor& d) const
{
    // Le device peut etre enregistre dans le variant !!
    // Value.which();
    if(Device != d.Device) return false;
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
        desc = deviceCodeMap.convert( Device);
        desc.append(L" ");

        // According to device, print specific thing
        switch (Device)
        {
        case EInputType::Keyboard:
            //static_cast<irr::EKEY_CODE>(Id)

            desc.append( keycodeBimap.convert( boost::get<irr::EKEY_CODE>(Value) ) );break;

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
