#ifndef CInputManager_HPP
#define CInputManager_HPP


#include <irrlicht.h>
#include <array>



enum class EInputDevice {
//Mouse0,
Mouse,
Keyboard,
Joystick
};

namespace NTapMode {
enum EId {
SingleTap = 0,
Repeat,
DoubleTap,

Count   //!w internal use
};
}


IMouseComponent


typedef TDescriptor;

//irr::u32
typedef std::array<irr::u32,3> TTimes;

//,int IDTYPE
template<int DEVICE_TYPE>
BindDescriptor(const int& DEVICE_TYPE,const int& eventId);

template<>


// On peut en avoir plusieurs
class CInputManager
{
    //
    std::vector< std::vector<> >

    //std::array< mode>

    /// Each vector contains sequences of TaMode::EId size
    /// DoubleTap will oontain ranges of 3 times in a row
    /// SingleTap sequences of 1 time in a row
    std::vector<TTimes> _times;   //!< Te register times


public:
    setMode(BindDescriptor, const NTapMode::EId&);





    // irr::s32
    static irr::s32 POV_DISABLED_POSITION;
    static irr::s32 POV_UP;
    static irr::s32 POV_DOWN;
    static irr::s32 POV_LEFT;
    static irr::s32 POV_RIGHT;
// TODO pouvoir exporter/importer au format XML
    //toXmlString()

// TODO: pouvoir interdire certains evenements lors du parsingEvent
    ///std::list<CBindDescriptor*> _forbiddenMappings;

    //bool isMappingForbidden(const irr::SEvent&);




    CInputManager();

    static void initStaticMembers();


    /**
    \return true if joystick event
    **/
    bool processEvent(const irr::u32& currentTime,const irr::SEvent& );


    static bool isAxisPositive(const irr::s16& axis);

    static bool isAxisNegative(const irr::s16& axis);

    //
    static bool isMouseButtonDown(const int& noButton)  {
        //BOOST_ASSERT( noButton < 6);
        return (_mouseButtons[noButton] != 0);
    };

    static irr::u32 mouseButtonDownTime(const int& noButton) {
        return _mouseButtons[noButton];
    }

    static bool isKeyDown(const irr::EKEY_CODE& key)  {
        return (_keyboardState[key] != 0);
    };

    /**
    * \param
    * \return Time of keypress, 0 if not pressed
    **/
    static const irr::u32& keyDownTime(const irr::EKEY_CODE& key)  {
        return _keyboardState[key];
            //return (_timer->getTime() - _keyboardState[key]);
        //return 0; // si pas touche
    }

    static bool isJoystickButtonDown(const int& button)  {
        return (_joystickButtonsState[button] != 0);
    };

//irr::u32& last
    static irr::u32 joystickButtonDownTime(const int& button) {

     //todo
     //   int tButton = irr::core::clamp(button,0,irr::SEvent::SJoystickEvent::NUMBER_OF_BUTTONS-1);
//        if(_joystickState[key] != 0)
//            return (_timer->getTime() - _joystickState[key]);
//        return 0; // si pas touche
        return (_joystickButtonsState[button]);
    };



    static bool povBeingUsed() {
        return (_pov.value != POV_DISABLED_POSITION);
    }

    static irr::u32 getPOVActivationTime() {
        return _pov.time;
    }


    static irr::u32 joystickAxisDownTime(const int& axis) {

        int tAxis = irr::core::clamp(axis,0,irr::SEvent::SJoystickEvent::NUMBER_OF_AXES-1);
        // takes into account the offset of the table
        //tAxis    += irr::SEvent::SJoystickEvent::NUMBER_OF_BUTTONS;
        return _axisState[ tAxis ];
    }

    //static void
    static irr::s32 getPOV() { return _pov.value; };

    //static bool enableJoysticks();

    static irr::u16 Threshold;

    static const int NUMBER_MOUSE_BUTTONS = 6;


private:

    // Value/time
    //typedef std::pair <irr::u32,irr::s16> TAxisTuple;
    //typedef irr::s32 TAxisTuple;
    typedef STuple TAxisTuple;


    static irr::core::array<irr::SJoystickInfo> _joystickInfos;

    //static setEventReceiver
    //irr::core::std::array<irr::IEventReceiver*>   mEventReceivers;

    static std::array<irr::u32,irr::KEY_KEY_CODES_COUNT> _keyboardState;
    static std::array<irr::u32,NUMBER_MOUSE_BUTTONS> _mouseButtons;
    static TAxisTuple _pov;

    //static irr::SEvent::SJoystickEvent _joystickState;
    static std::array<irr::u32,irr::SEvent::SJoystickEvent::NUMBER_OF_BUTTONS > _joystickButtonsState;

    //static std::array<irr::u32,irr::SEvent::SJoystickEvent::NUMBER_OF_AXES > _axisState;


    static std::array< irr::s16,irr::SEvent::SJoystickEvent::NUMBER_OF_AXES > _axisState;
    // On peut y acceder via getCursorControl
    //static irr::SEvent::SMouseInput _mouseState;
    /////using the first 3 bits for flags
    //core::position2d<s32> mMousePos;
};





#endif
