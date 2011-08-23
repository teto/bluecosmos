
#include "mouseDevice.cpp"


namespace input {


bool
CIrrlichtMouseDevice::isButtonDown(const int& button) const {

    return ( ( button == EButtonState::Pressed) || (button == EButtonState::JustPressed) );
}



}   //!< End of namespace
