#include "CEventMapping.hpp"
#include "CEventManager.hpp"
#include <fusion/core/CStringBuilder.hpp>
#include <fusion/core/CStringExtractor.hpp>
#include <fusion/logging/ILogger.hpp>
#include <iostream>

using namespace irr;
using namespace core;

CEventMapping::TBiMap CEventMapping::_keyMap;
CEventMapping::TBiMap CEventMapping::_inputTypes;

irr::core::stringw CEventMapping::_unknown = L"UNKNOWN";
// A completer pr verifier si cohérent ?
// remplacer name par id ?
// setup from description



void
CEventMapping::setName( const TWString& id) {

    _name = id;
}



bool
CEventMapping::checkState()
{
    switch(_type){

    case NInputType::KEY:
    {


        //const irr::u32& temp = CEventManager::keyDownTime(static_cast<irr::EKEY_CODE>(_value) );
        const irr::u32& timeOfKeyPress = CEventManager::keyDownTime( _value.KeyCode );

        // if key not pressed
        if(timeOfKeyPress == 0){

            return false;
        }
        // update time of _lastActivation
        if(_lastActivation == 0){

//            _INFO << "First activation";
            _lastActivation = timeOfKeyPress;
            return true;

        }
        // If repeat enabled
        else if( repeat() ){
            irr::u32 currentTime = CEventManager::_timer->getTime();

            //CEventManager::
            if( (_lastActivation + _normalizedRepeatDelay) < (currentTime)) {
//                _INFO << " ==> repeat => activated";
                _lastActivation = currentTime;
                return true;
            }

        }
        // Repeat disabled , we just want to check if the key has been released
        // and re-pressed
        else {
            if(_lastActivation < temp){
                _INFO << "CEventMapping.cpp => activated because re pressed";
                _lastActivation = temp;
                return true;
            }
        }
    }
//        break;
//        // if repeat enabled
//        else if(_lastActivation + _normalizedRepeatDelay > temp) {
//            _lastActivation = temp;
//            return true;
//        }
//        else {
//            _lastActivation = temp;
//            return true;
//        }
//    }
        //CEventManager::isKeyDown(_value);
        break;

    case NInputType::JOY_AXIS_PLUS:
    case NInputType::JOY_AXIS_MINUS:
    case NInputType::JOY_BTN:
    case NInputType::JOY_POV:
    default:
        break;
    }
    return false;
}


CEventMapping::CEventMapping(const std::wstring name,const EInputType& type,const irr::s32& value) :
_name(name),
_type(type),
_value(value),
_bRepeat(false),
_normalizedRepeatDelay(10),
_lastActivation(0)   // en ms
{

}


void
CEventMapping::toXmlString(fus::TWCharStringBuilder& str) const
{
    //std::wstring str("<>");
    std::wcout << _name.c_str() << std::endl;
    str("<input name=\"")( _name.c_str() );
    str("\" type=\"")(typeToString().c_str() );
    str("\" value=\"")(valueToString().c_str())("\" ");
    str(" repeat=\"")(_bRepeat)("\" ");
    str(" delay=\"")(_normalizedRepeatDelay)("\" />");
    //return str;
}


bool
CEventMapping::init(
const std::wstring& name,
const EInputType& type,
const irr::s32& value
)
{
    _name = name;
    return setup(type,value);
}


bool
CEventMapping::setup(const EInputType& type,const irr::s32& value)
{
    _type = type;
    _value = value;
    return true;
}



bool
CEventMapping::setup(const irr::core::stringw& strType,const irr::core::stringw& strValue)
//CEventMapping::setup(const wchar_t* strType,const wchar_t* strValue)
{
    try {
        //L"KEY_LEFT"
        //std::wcout << "type: " << strType.c_str();
        int iType = _inputTypes.right.at(strType );//strType
        irr::s32 value  = 0;
        switch (iType)
        {
        	case KEY:
                value = _keyMap.right.at(strValue );
                break;

        	default:
                {
                    fus::TWStringExtractor extractor(strValue.c_str());
                    extractor(value);
                }
                break;
        }


        setup(static_cast<EInputType>(iType),value);
    }
    catch(std::out_of_range &error){
        _LOG_ERROR << "Out of range";
        return false;
    }
    catch(...){
        _LOG_ERROR << "exception not catched > mettrre ici un truc pr attraper exception de l'extractor";
        return false;
    }
    return true;
}


irr::core::stringw
CEventMapping::valueToString() const
{
    irr::core::stringw str;
    switch(_type) {

        //
        case KEY:
            return keyCodeToString(static_cast<irr::EKEY_CODE>(_value) );

// mousemove too !
// case EINPUT_MOU_:
//    case EINPUT_MOU_WHEEL:
//        desc = L"Mouse";
//        //desc = L"Mouse %s %s",m_iMouseAxis==0?L"X":L"Y",m_iMouseDirection>0?L"+":L"-");
//        break;

//    case EINPUT_MOU_BTN:
//        desc = L"Mouse Button";
//        desc += _value;
//        break;

    case JOY_AXIS_PLUS:
    case JOY_AXIS_MINUS:
    case JOY_BTN:
    case JOY_POV:
        str += _value;
        return str;


    default:
        break;
    }
// + _name + "\" type=\""+ _type + "\" value=\"" + _value "\">";
    //std::wstring res = fus::TWCharStringBuilder("<input name=\"")( _name.c_str() )("\" type=\"")(typeToString(_type).c_str())("\" value=\"")(generateDescription().c_str())( "\" />");
    //std::wstring res = fus::TWCharStringBuilder("<input name=\"")( _name.c_str() )("\" description=\"")(generateDescription().c_str())( "\" />");

    return _unknown;
}



bool
CEventMapping::operator==(const CEventMapping& map)
{
    if(_value != map._value) return false;
    if(_type != map._type) return false;
    return true;
}


//bool
//CEventMapping::axisBeingUsed(const irr::SEvent::SJoystickEvent& event,const std::size_t& noAxis){
//
//
//}

//bool
//CEventMapping::updateState(const irr::SEvent& e)
//{
//    //
//
//
//    if(matchesEvent()){
//
//        if(!Repeat){
//            _state = false;
//        }
//
//        _state = true;
////        switch(e.EventType){
////            case EET_KEY_INPUT_EVENT:
//        if( (e.EventType == EET_KEY_INPUT_EVENT)&& (_value == e.KeyInput.Key) ){
//
//           // Met a jour l'etat de la touche
//            _state = e.KeyInput.PressedDown;
//        }
//    }
//    return _state;
//}


bool
CEventMapping::matchesEvent(const irr::SEvent& e) const
{

    switch(e.EventType){

        case EET_JOYSTICK_INPUT_EVENT:
            return matchesJoystickEvent(e.JoystickEvent);
//
//        case EET_KEY_INPUT_EVENT:
//            if( (_value == e.KeyInput.Key){
//               // Met a jour l'etat de la touche
//                _state = e.KeyInput.PressedDown;
//                return true;
//            }
//            return false;

        default:
        {


            CEventMapping tMap;
            if(tMap.processEvent(e,false,true)){

                if(tMap == (*this)){
                    return true;
                }
            }
        }
    }// fin du switch
//  if( (_value == e.KeyInput.Key) && (e.KeyInput.PressedDown == true)){
//      return true;
//  }
//  break;




    return false;
}


bool
CEventMapping::matchesJoystickEvent(const irr::SEvent::SJoystickEvent& event) const {

    switch(_type){
        case JOY_BTN:
            return event.IsButtonPressed(_value);

        case JOY_POV:
            return povBeingUsed(event);

        case JOY_AXIS_MINUS:
            return(event.Axis[_value] < -_threshold);

        case JOY_AXIS_PLUS:
            return(event.Axis[_value] > _threshold);
        default:
            break;
    };


    return false;
}




// TODO fct a supprimer
stringw
CEventMapping::generateDescription() const
{

    stringw desc = typeToString();
    desc.append(" ");
    desc.append(valueToString());
    //std::wcout << desc.c_str();
    return desc;
}





// utiliser un bimap
//TBimap::left_map
//const stringw&
const stringw&
CEventMapping::keyCodeToString(const irr::EKEY_CODE& keyCode)
{

    try {
        //TMappings::left_mconst_iterator _keyMap.left.find(keyCode);
        return _keyMap.left.at(keyCode);
    }
    catch( std::out_of_range & e ) {
        _LOG_ERROR << "Couldn't find keyCode associated with" << keyCode << "in keyCodeToString";
        return _unknown;
    }
}


//const EInputType& type
//const stringw&
const stringw&
CEventMapping::typeToString() const
{

    try {
        //TMappings::left_mconst_iterator _keyMap.left.find(keyCode);
        return _inputTypes.left.at(_type);
    }
    catch( std::out_of_range& e ) {
        _LOG_ERROR << "Couldn't find associated type in typeToString()";
        return _unknown;
    }
}

void
CEventMapping::initializeBimaps()
{

    _inputTypes.insert( TKeyAssociation(JOY_AXIS_PLUS,L"JOY_AXIS_PLUS"));
    _inputTypes.insert( TKeyAssociation(JOY_AXIS_MINUS,L"JOY_AXIS_MINUS"));
    _inputTypes.insert( TKeyAssociation(KEY,L"KEY"));
    _inputTypes.insert( TKeyAssociation(JOY_BTN,L"JOY_BTN"));
    _inputTypes.insert( TKeyAssociation(JOY_POV,L"JOY_POV"));


    _keyMap.insert( TKeyAssociation(KEY_LBUTTON,L"KEY_LBUTTON") );
    _keyMap.insert( TKeyAssociation(KEY_RBUTTON,L"KEY_RBUTTON") );
    _keyMap.insert( TKeyAssociation(KEY_CANCEL,L"KEY_CANCEL") );
    _keyMap.insert( TKeyAssociation(KEY_MBUTTON,L"KEY_MBUTTON") );
    _keyMap.insert( TKeyAssociation(KEY_XBUTTON1,L"KEY_XBUTTON1") );
    _keyMap.insert( TKeyAssociation(KEY_XBUTTON2,L"KEY_XBUTTON2") );
    _keyMap.insert( TKeyAssociation(KEY_BACK,L"KEY_BACK") );
    _keyMap.insert( TKeyAssociation(KEY_TAB,L"KEY_TAB") );
    _keyMap.insert( TKeyAssociation(KEY_CLEAR,L"KEY_CLEAR") );
    _keyMap.insert( TKeyAssociation(KEY_RETURN,L"KEY_RETURN") );
    _keyMap.insert( TKeyAssociation(KEY_SHIFT,L"KEY_SHIFT") );
    _keyMap.insert( TKeyAssociation(KEY_CONTROL,L"KEY_CONTROL") );
    _keyMap.insert( TKeyAssociation(KEY_MENU,L"KEY_MENU") );
    _keyMap.insert( TKeyAssociation(KEY_PAUSE,L"KEY_PAUSE") );
    _keyMap.insert( TKeyAssociation(KEY_CAPITAL,L"KEY_CAPITAL") );
    _keyMap.insert( TKeyAssociation(KEY_KANA,L"KEY_KANA") );
    _keyMap.insert( TKeyAssociation(KEY_HANGUEL,L"KEY_HANGUEL") );
    _keyMap.insert( TKeyAssociation(KEY_HANGUL,L"KEY_HANGUL") );
    _keyMap.insert( TKeyAssociation(KEY_JUNJA,L"KEY_JUNJA") );
    _keyMap.insert( TKeyAssociation(KEY_FINAL,L"KEY_FINAL") );
    _keyMap.insert( TKeyAssociation(KEY_KANJI,L"KEY_KANJI") );
    _keyMap.insert( TKeyAssociation(KEY_ESCAPE,L"KEY_ESCAPE") );
    _keyMap.insert( TKeyAssociation(KEY_CONVERT,L"KEY_CONVERT") );
    _keyMap.insert( TKeyAssociation(KEY_NONCONVERT,L"KEY_NONCONVERT") );
    _keyMap.insert( TKeyAssociation(KEY_ACCEPT,L"KEY_ACCEPT") );
    _keyMap.insert( TKeyAssociation(KEY_MODECHANGE,L"KEY_MODECHANGE") );
    _keyMap.insert( TKeyAssociation(KEY_SPACE,L"KEY_SPACE") );
    _keyMap.insert( TKeyAssociation(KEY_PRIOR,L"KEY_PRIOR") );
    _keyMap.insert( TKeyAssociation(KEY_NEXT,L"KEY_NEXT") );
    _keyMap.insert( TKeyAssociation(KEY_END,L"KEY_END") );
    _keyMap.insert( TKeyAssociation(KEY_HOME,L"KEY_HOME") );
    _keyMap.insert( TKeyAssociation(KEY_LEFT,L"KEY_LEFT") );
    _keyMap.insert( TKeyAssociation(KEY_UP,L"KEY_UP") );
    _keyMap.insert( TKeyAssociation(KEY_RIGHT,L"KEY_RIGHT") );
    _keyMap.insert( TKeyAssociation(KEY_DOWN,L"KEY_DOWN") );
    _keyMap.insert( TKeyAssociation(KEY_SELECT,L"KEY_SELECT") );
    _keyMap.insert( TKeyAssociation(KEY_PRINT,L"KEY_PRINT") );
    _keyMap.insert( TKeyAssociation(KEY_PRINT,L"KEY_DOWN") );
    _keyMap.insert( TKeyAssociation(KEY_EXECUT,L"KEY_EXECUT") );
    _keyMap.insert( TKeyAssociation(KEY_SNAPSHOT,L"KEY_SNAPSHOT") );
    _keyMap.insert( TKeyAssociation(KEY_INSERT,L"KEY_INSERT") );
    _keyMap.insert( TKeyAssociation(KEY_DELETE,L"KEY_DELETE") );
    _keyMap.insert( TKeyAssociation(KEY_HELP,L"KEY_HELP") );
    _keyMap.insert( TKeyAssociation(KEY_INSERT,L"KEY_INSERT") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_0,L"KEY_KEY_0") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_1,L"KEY_KEY_1") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_2,L"KEY_KEY_2") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_3,L"KEY_KEY_3") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_4,L"KEY_KEY_4") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_5,L"KEY_KEY_5") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_6,L"KEY_KEY_6") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_7,L"KEY_KEY_7") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_8,L"KEY_KEY_8") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_9,L"KEY_KEY_9") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_A,L"KEY_KEY_A") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_B,L"KEY_KEY_B") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_C,L"KEY_KEY_C") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_D,L"KEY_KEY_D") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_E,L"KEY_KEY_E") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_F,L"KEY_KEY_F") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_G,L"KEY_KEY_G") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_H,L"KEY_KEY_H") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_I,L"KEY_KEY_I") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_J,L"KEY_KEY_J") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_K,L"KEY_KEY_K") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_L,L"KEY_KEY_L") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_M,L"KEY_KEY_M") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_N,L"KEY_KEY_N") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_O,L"KEY_KEY_O") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_P,L"KEY_KEY_P") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_Q,L"KEY_KEY_Q") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_R,L"KEY_KEY_R") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_S,L"KEY_KEY_S") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_T,L"KEY_KEY_T") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_U,L"KEY_KEY_U") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_V,L"KEY_KEY_V") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_W,L"KEY_KEY_W") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_X,L"KEY_KEY_X") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_Y,L"KEY_KEY_Y") );
    _keyMap.insert( TKeyAssociation(KEY_KEY_Z,L"KEY_KEY_Z") );
    _keyMap.insert( TKeyAssociation(KEY_LWIN,L"KEY_LWIN") );
    _keyMap.insert( TKeyAssociation(KEY_RWIN,L"KEY_RWIN") );
    _keyMap.insert( TKeyAssociation(KEY_APPS,L"KEY_APPS") );
    _keyMap.insert( TKeyAssociation(KEY_SLEEP,L"KEY_SLEEP") );
    _keyMap.insert( TKeyAssociation(KEY_NUMPAD0,L"KEY_NUMPAD0") );
    _keyMap.insert( TKeyAssociation(KEY_NUMPAD1,L"KEY_NUMPAD1") );
    _keyMap.insert( TKeyAssociation(KEY_NUMPAD2,L"KEY_NUMPAD2") );
    _keyMap.insert( TKeyAssociation(KEY_NUMPAD3,L"KEY_NUMPAD3") );
    _keyMap.insert( TKeyAssociation(KEY_NUMPAD4,L"KEY_NUMPAD4") );
    _keyMap.insert( TKeyAssociation(KEY_NUMPAD5,L"KEY_NUMPAD5") );
    _keyMap.insert( TKeyAssociation(KEY_NUMPAD6,L"KEY_NUMPAD6") );
    _keyMap.insert( TKeyAssociation(KEY_NUMPAD7,L"KEY_NUMPAD7") );
    _keyMap.insert( TKeyAssociation(KEY_NUMPAD8,L"KEY_NUMPAD8") );
    _keyMap.insert( TKeyAssociation(KEY_NUMPAD9,L"KEY_NUMPAD9") );
    _keyMap.insert( TKeyAssociation(KEY_MULTIPLY,L"KEY_MULTIPLY") );
    _keyMap.insert( TKeyAssociation(KEY_ADD,L"KEY_ADD") );
    _keyMap.insert( TKeyAssociation(KEY_SEPARATOR,L"KEY_SEPARATOR") );
    _keyMap.insert( TKeyAssociation(KEY_SUBTRACT,L"KEY_SUBTRACT") );
    _keyMap.insert( TKeyAssociation(KEY_DECIMAL,L"KEY_DECIMAL") );
    _keyMap.insert( TKeyAssociation(KEY_DIVIDE,L"KEY_DIVIDE") );
    _keyMap.insert( TKeyAssociation(KEY_F1,L"KEY_F1") );
    _keyMap.insert( TKeyAssociation(KEY_F2,L"KEY_F2") );
    _keyMap.insert( TKeyAssociation(KEY_F3,L"KEY_F3") );
    _keyMap.insert( TKeyAssociation(KEY_F4,L"KEY_F4") );
    _keyMap.insert( TKeyAssociation(KEY_F5,L"KEY_F5") );
    _keyMap.insert( TKeyAssociation(KEY_F6,L"KEY_F6") );
    _keyMap.insert( TKeyAssociation(KEY_F7,L"KEY_F7") );
    _keyMap.insert( TKeyAssociation(KEY_F8,L"KEY_F8") );
    _keyMap.insert( TKeyAssociation(KEY_F9,L"KEY_F9") );
    _keyMap.insert( TKeyAssociation(KEY_F10,L"KEY_F10") );
    _keyMap.insert( TKeyAssociation(KEY_F11,L"KEY_F11") );
    _keyMap.insert( TKeyAssociation(KEY_F12,L"KEY_F12") );
    _keyMap.insert( TKeyAssociation(KEY_F13,L"KEY_F13") );
    _keyMap.insert( TKeyAssociation(KEY_F14,L"KEY_F14") );
    _keyMap.insert( TKeyAssociation(KEY_F15,L"KEY_F15") );
    _keyMap.insert( TKeyAssociation(KEY_F16,L"KEY_F16") );
    _keyMap.insert( TKeyAssociation(KEY_F17,L"KEY_F17") );
    _keyMap.insert( TKeyAssociation(KEY_F18,L"KEY_F18") );
    _keyMap.insert( TKeyAssociation(KEY_F19,L"KEY_F19") );
    _keyMap.insert( TKeyAssociation(KEY_F20,L"KEY_F20") );
    _keyMap.insert( TKeyAssociation(KEY_F21,L"KEY_F21") );
    _keyMap.insert( TKeyAssociation(KEY_F22,L"KEY_F22") );
    _keyMap.insert( TKeyAssociation(KEY_F23,L"KEY_F23") );
    _keyMap.insert( TKeyAssociation(KEY_F24,L"KEY_F24") );
    _keyMap.insert( TKeyAssociation(KEY_NUMLOCK,L"KEY_NUMLOCK") );
    _keyMap.insert( TKeyAssociation(KEY_SCROLL,L"KEY_SCROLL") );
    _keyMap.insert( TKeyAssociation(KEY_LSHIFT,L"KEY_LSHIFT") );
    _keyMap.insert( TKeyAssociation(KEY_RSHIFT,L"KEY_RSHIFT") );
    _keyMap.insert( TKeyAssociation(KEY_LCONTROL,L"KEY_LCONTROL") );
    _keyMap.insert( TKeyAssociation(KEY_RCONTROL,L"KEY_RCONTROL") );
    _keyMap.insert( TKeyAssociation(KEY_LMENU,L"KEY_LMENU") );
    _keyMap.insert( TKeyAssociation(KEY_RMENU,L"KEY_RMENU") );
    _keyMap.insert( TKeyAssociation(KEY_PLUS,L"KEY_PLUS") );
    _keyMap.insert( TKeyAssociation(KEY_COMMA,L"KEY_COMMA") );
    _keyMap.insert( TKeyAssociation(KEY_MINUS,L"KEY_MINUS") );
    _keyMap.insert( TKeyAssociation(KEY_PERIOD,L"KEY_PERIOD") );
    _keyMap.insert( TKeyAssociation(KEY_ATTN,L"KEY_ATTN") );
    _keyMap.insert( TKeyAssociation(KEY_CRSEL,L"KEY_CRSEL") );
    _keyMap.insert( TKeyAssociation(KEY_CRSEL,L"KEY_CRSEL") );
    _keyMap.insert( TKeyAssociation(KEY_EXSEL,L"KEY_EXSEL") );
    _keyMap.insert( TKeyAssociation(KEY_EREOF,L"KEY_EREOF") );
    _keyMap.insert( TKeyAssociation(KEY_PLAY,L"KEY_PLAY") );
    _keyMap.insert( TKeyAssociation(KEY_ZOOM,L"KEY_ZOOM") );
    _keyMap.insert( TKeyAssociation(KEY_PA1,L"KEY_PA1") );
    _keyMap.insert( TKeyAssociation(KEY_OEM_CLEAR,L"KEY_OEM_CLEAR") );
}




bool
processEvent(const irr::SEvent::SMouseInput & event)
{
//EMIE_MOUSE_MOVED
// Reste a distinguer mouvement du clic
                //EINPUT_MOU_MOVE
                //EINPUT_MOU_BTN
//                switch(_event){
//
//                                    default: return false;
//                };
//
//            }
//            break;
    return false;
}


//axisEnabled(std::size_t& axis){
//
//    return (event.Axis[i] > _threshold);
//}
//if( > )
// a inliner
//bool
//CEventMapping::povBeingUsed(const irr::SEvent::SJoystickEvent& event){
//
//}


// N'activer qu'un des parametres du joystick a la fois !!
bool
CEventMapping::processEvent(const irr::SEvent::SJoystickEvent& event){

    // Si jamais un des boutons est appuye
    // Champ de bit en fait
    // faire gaffe si plusieurs boutons appuye car renvoie le bouton appuyé avec le plus petit ID
    if(event.ButtonStates != 0){

        int noButton = 0;
        while( noButton < irr::SEvent::SJoystickEvent::NUMBER_OF_BUTTONS){
            if(event.IsButtonPressed(noButton)){
                break;
            }
            ++noButton;
        }
        return setup(JOY_BTN,noButton);
    }
    // POV c'est la croix directionnelle
    else if(povBeingUsed(event)){

        return setup(JOY_POV,event.POV);
    }
    // Axis c'est les sticks

    else {
        // en fait ici faudrait savoir si on va vers la droite ou vers la gauche
        for(irr::u16 i = 0; i < irr::SEvent::SJoystickEvent::NUMBER_OF_AXES;++i){

            //_INFO << "aXIs" << event.Axis[i] << "seuil" << _threshold;
            // TODO remplacer le Seuil ici
            if(event.Axis[i] > _threshold){
                //break;
                return setup(JOY_AXIS_PLUS,i);
            }
            else if(event.Axis[i] < -_threshold){
                return setup(JOY_AXIS_MINUS,i);
            }
        }

    }
    return false;
}





bool
CEventMapping::processEvent(const irr::SEvent& e,const bool& enableMouse,const bool& enableJoystick)
{


    //EInputType type = EINPUT_NULL;

    switch(e.EventType){

        case EET_KEY_INPUT_EVENT:
            if(e.KeyInput.PressedDown){
                return setup(KEY,e.KeyInput.Key);
            }
            return false;

// est genere a chaque tour du coup on sait pas si y a de changement .
        case EET_JOYSTICK_INPUT_EVENT:
            if(enableJoystick){
                return processEvent(e.JoystickEvent);
            }

            return false;


        case EET_MOUSE_INPUT_EVENT:
            if(enableMouse){
                //return processEvent(e.MouseInput);
            }

        default:
            return false;


    };

    return false;
}

