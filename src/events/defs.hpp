/**
\file
*/
#ifndef _BC_EVENTS_DEF_HPP_INCLUDED
#define _BC_EVENTS_DEF_HPP_INCLUDED


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
enum class EInputType : int {
//enum EInputType  {
None,
Keyboard,
JoystickButton,
JoystickAxis,
JoystickPov,

Mouse
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


// Ca  c des events
enum class ETapMode {
DoublePressed
//, Pressed

, JustPressed
// On se fout de ceux la en fait
, JustReleased
//, Released
};

#endif
