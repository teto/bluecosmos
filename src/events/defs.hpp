/**
\file
*/
#ifndef _BC_EVENTS_DEF_HPP_INCLUDED
#define _BC_EVENTS_DEF_HPP_INCLUDED

#include <irrlicht.h>
#include <fusion/utilities/SBimap.hpp>


/*
    enum InputType
    {
        IT_NONE = 0,
        IT_KEYBOARD,
        IT_STICKMOTION,
        IT_STICKBUTTON,
        //IT_STICKHAT,
        IT_MOUSEMOTION,
        IT_MOUSEBUTTON
    };
*/

/**
*
**/
enum class EInputType : int
{
//enum EInputType  {
None,
Keyboard,
JoystickButton,
JoystickAxis,
JoystickPov,
MouseWheel,
MouseButton
//Emulation,

};


enum class EPovDirection {
Up,
Right,
Down,
Left
};

enum class EAxisDirection
{
Negative,
Positive,
Neutral
};



// Possible ?
enum class EButtonState
{
JustPressed,
Pressed,
Released,
JustReleased
};


// Pourrait renommer ca en EBindTrigger
// Ca  c des events
enum class ETapMode  : int
{
Released = 0
, JustPressed = 1
, Pressed = 5
, DoublePressed = 7

// On se fout de ceux la en fait
//, JustReleased
//, Released
};


typedef SBimap< irr::EKEY_CODE,std::wstring> TKeyCodeMap;
typedef SBimap< EInputType,std::wstring> TDeviceCodeMap;
typedef SBimap< ETapMode,std::wstring> TDescriptorModesMap;



typedef irr::u32 TTimeUnit;

extern TTimeUnit QuickTapDelay;

void initializeKeycodes();
void initializeDeviceCodes();



#endif
