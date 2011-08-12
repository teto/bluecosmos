/**
\file config_manager.h

Refaire pour l'adapter avec le systeme de boost::program_options
*/
#ifndef _BC_CBindDescriptor_HPP_INCLUDED
#define _BC_CBindDescriptor_HPP_INCLUDED


#include <irrlicht.h>  // header only
#include <string>
#include <list>
#include <boost/variant.hpp>
#include <boost/optional.hpp>

#include <fusion/core/CStringBuilder.hpp>
#include <fusion/utilities/SBimap.hpp>
#include "defs.hpp"



typedef SBimap< irr::EKEY_CODE,std::wstring> TKeyCodeMap;
typedef SBimap< EInputType,std::wstring> TDeviceCodeMap;
typedef SBimap< ETapMode,std::wstring> TDescriptorModesMap;



// forward declaration
class CBindDescriptor;

//bool generateDescriptorFromIrrlichtEvent(const irr::SEvent&,CBindDescriptor&);

// Todo creer un namespace event

void initializeKeycodes();
void initializeDeviceCodes();

// enommer en SBind**
class CBindDescriptor
{
public:
//    NInputType::EId _type;
    //EInputType Device;
    //int Id;
    int DeviceId;   //!< Joystick No as seen by irrlicht for example
    ETapMode Mode;
    boost::optional<irr::u32> RepeatTime;
//    struct SJoystickParameters {
//    };
    struct SJoyButton {
        bool operator==(SJoyButton const& b) const { return (b.Button == Button);};
        int Button;
    };

    struct SJoyAxis {
        bool operator ==(SJoyAxis const& p) const { return (p.Axis == Axis && p.Direction == Direction); };
        //SJoyAxis()
        int Axis;
        EAxisDirection Direction;
    };

    // for variant.which EInputType::None
    //nullptr
    struct SNullType;
    struct SNullType { bool operator==(const SNullType& t) const { return true;}; };

    // possede which, empty,type
    // doit respecter la numeroration de input type
    // == existe mais en free function
    // get<int>
    // get<0>
    boost::variant<SNullType,irr::EKEY_CODE,SJoyAxis,SJoyButton,EPovDirection> Value;
    /*
    union {
    irr::EKEY_CODE KeyCode;
    //struct Joystick
    SJoyAxis StickAxis;
    SJoyButton JoyButton;
    EPovDirection PovDirection;

    };
*/
    static const wchar_t* StrUndefined;

    static TKeyCodeMap keycodeBimap;
    static TDeviceCodeMap deviceCodeMap;
    //static TDescriptorModesMap deviceCodeMap;

    //static void initializeKeycodes();
    //static void initializeDevicesCodes();

    // Check if Id exists for that device
    //bool isValid() const;

    bool undefined() const;
    bool isAutorepeatEnabled() const;
    bool setRepeatDelay(irr::u32 const& );
    void disableAutoRepeat();

    EInputType getInputType() const;

    //CBindDescriptor(const EInputType& = EInputType::None,int const& = -1);
    CBindDescriptor(wchar_t* const& key);
    CBindDescriptor();
    //CBindDescriptor(char const&);
    //CBindDescriptor(wchar_t const&);

    void reset();
    bool operator==(const CBindDescriptor&) const;
//    bool operator!=(const CBindDescriptor& descriptor) const {
//        return !( (*this) == descriptor);
//    }

    // Pr les classer dans les map
    //bool operator<(const CBindDescriptor& descriptor) const ;

    // proposer plein de constructeurs
    //bool setup(const EInputType&, int const&);
    bool setup(wchar_t* const& key);
    void setup(irr::EKEY_CODE const& keyCode);

    // Setup axis
    bool setup(int const&,EAxisDirection const&);
    void setup(EPovDirection const& povDirection);
    // Setup joystick button
    bool setup(int const& joyButton);


    //bool setup(char const& key);
    //bool setup(char* const strType);

    //void mode(ETapMode const&)

//    bool matchesEvent(const irr::SEvent&) const;
//    bool matchesJoystickEvent(const irr::SEvent::SJoystickEvent&) const;



    std::wstring generateDescription() const;
};

#endif
