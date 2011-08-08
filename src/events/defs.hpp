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
//enum class EInputType  {
enum EInputType  {
Keyboard,
JoystickButton,
JoystickAxis,
JoystickPov,
None,
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
, Pressed

, JustPressed
// On se fout de ceux la en fait
, JustReleased
, Released
};

#endif
