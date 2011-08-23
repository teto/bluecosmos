/**
**/
#ifndef _BC_IINPUTDEVICE_HPP_INCLUDED
#define _BC_IINPUTDEVICE_HPP_INCLUDED


#include <irrlicht.h>  // header only
#include <string>
#include <array>

//template<class VALUE>
struct SButton {

    SButton() : Active(false),Changed(false) {}

    const bool& pressed() const {return Active;};
    const bool pressed() const {return (!Active);};
    bool justPressed() const {return Active;};
    bool justReleased() const {return Active;};


    bool Changed;
    bool Active;

};



//class EVENTTYPE,
template<int NB_BUTTONS,class BUTTON_ID>
class IInputDevice {
    std::array< SButton,NB_BUTTONS> _buttons;
public:
    static const int buttonsNumber = NB_BUTTONS;

//    std::map<TTimes,NB_BUTTONS> _buttons;
//

//.pressed()
    SButton& getButton(BUTTON_ID const& buttonId)  { return _buttons[buttonId];};

    //virtual void processEvent(EVENTTYPE const &) = 0;
};





#endif
