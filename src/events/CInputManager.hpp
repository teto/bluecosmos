#ifndef CInputManager_HPP
#define CInputManager_HPP

#include <irrlicht.h>
#include <array>
#include "CBindDescriptor.hpp"


// Fwd declaration
class CIrrlichtMouseDevice;
class CIrrlichtKeyboardDevice;
class CIrrlichtJoystickDevice;
class CBindDescriptor;

//enum class EInputType;

// Renommer en InputManager
class CInputManager
{

    CIrrlichtMouseDevice* _mouse;
    CIrrlichtKeyboardDevice* _keyboard;
    CIrrlichtJoystickDevice* _joystick; // En mettre un vector



public:
    inline CIrrlichtMouseDevice& getMouse(int const& numero = 0){ return *_mouse; };
    inline CIrrlichtKeyboardDevice& getKeyboard(int const& numero = 0){ return *_keyboard; };
    inline CIrrlichtJoystickDevice* getJoystick(int const& numero = 0){ return _joystick; };
//static irr::core::array<irr::SJoystickInfo> _joystickInfos;

    CInputManager();
    //static void initStaticMembers();

    //updateContext(CBindsCollection&);
    bool generateDescriptorFromIrrlichtEvent(const irr::SEvent&,CBindDescriptor&) const;

    //bool enableJoysticks(core::array<irr::SJoystickInfo>&);
    bool handleEvent(const irr::SEvent& );

    //template<>
    const int getState( irr::EKEY_CODE const& value);

    int retrieveStateFromDescriptor(const CBindDescriptor&);
    //const bool getState( const EInputType& device, int const& value) const;

    //bool check( CBindDescriptor& ,CBindMode&) const;

private:
    static irr::core::array<irr::SJoystickInfo> _joystickInfos;

};





#endif
