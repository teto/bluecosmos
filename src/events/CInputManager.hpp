#ifndef CInputManager_HPP
#define CInputManager_HPP

#include <irrlicht.h>
#include <array>
#include "CBindDescriptor.hpp"

class CIrrlichtMouseDevice;
class CIrrlichtKeyboardDevice;
class CIrrlichtJoystickDevice;


namespace input {
// Fwd declaration

class CBindDescriptor;

//enum class EInputType;

// Faire deriver de IEventReciever,
// comme ca on peut faire setEventReciever(&inputManager);
// passer en parametre un IEventReciever de backup, backupEventReceiver
// Renommer en InputManager
class CInputManager
: public irr::IEventReceiver
{

    CIrrlichtMouseDevice* _mouse;
    CIrrlichtKeyboardDevice* _keyboard;

    //boost::ptr_vector ?
    std::vector<CIrrlichtJoystickDevice*> _joysticks;



public:

    inline CIrrlichtMouseDevice& getMouse(int const& numero = 0){ return *_mouse; };
    inline CIrrlichtKeyboardDevice& getKeyboard(int const& numero = 0){ return *_keyboard; };
    inline CIrrlichtJoystickDevice* getJoystick(int const& numero = 0){ return _joysticks.at[numero]; };
//static irr::core::array<irr::SJoystickInfo> _joystickInfos;

    CInputManager();
    ~CInputManager();
    //static void initStaticMembers();

    //updateContext(CBindsCollection&);
    bool generateDescriptorFromIrrlichtEvent(const irr::SEvent&,CBindDescriptor&) const;

    //bool enableJoysticks(core::array<irr::SJoystickInfo>&);
    bool handleEvent(const irr::SEvent& );

    bool activateJoysticks();
    //template<>
    //const int getState( irr::EKEY_CODE const& value);

    int retrieveStateFromDescriptor(const CBindDescriptor&);
    //const bool getState( const EInputType& device, int const& value) const;

    //bool check( CBindDescriptor& ,CBindMode&) const;

private:
    //static irr::core::array<irr::SJoystickInfo> _joystickInfos;

};


}


#endif
