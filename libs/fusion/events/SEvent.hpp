#ifndef _FUSION_SEVENT_HPP_INCLUDED
#define _FUSION_SEVENT_HPP_INCLUDED



namespace fus {

enum class EInputEventType {
onKeyPress = 1,  /**< keyboard type */
onKeyRelease,
//JOY_AXIS_PLUS   = 2,  /**< joystick axis type */
//JOY_AXIS_MINUS  = 4,  /**< joystick axis type */
onJoystickAxis,
onMouseMove,
onMouseWheel,
onMouseClick,
onJoystickButtonPress,
onJoystickButtonRelease,
onJoystickPov       //§< Movec POV
};





//struct SInputEvent

}


#endif
