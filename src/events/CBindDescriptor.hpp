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




// forward declaration
class CBindDescriptor;


// enommer en SBind**
class CBindDescriptor
{
public:

    int DeviceId;   //!< Joystick No as seen by irrlicht for example
    ETapMode Mode;  //!<
    boost::optional<TTimeUnit> RepeatTime;  //!< If set, autorepeat is enabled


//    struct SJoystickParameters {
//    };
    struct SJoyButton {
        SJoyButton(const int& button = 0) : Button(button) {};
        bool operator==(SJoyButton const& b) const { return (b.Button == Button);};
        int Button;
    };



    struct SJoyPov {
        bool operator ==(SJoyPov const& pov) const { return (pov.Value == Value); };
        irr::E_JOYSTICK_POVHAT_VALUE Value;
    };

    struct SJoyAxis {
        bool operator ==(SJoyAxis const& p) const { return (p.Axis == Axis && p.Direction == Direction); };
        //SJoyAxis()
        irr::EJOYSTICK_AXIS Axis;
        EAxisDirection Direction;
    };

    struct SMouseWheel {
        SMouseWheel() : Up(false) {}
        bool operator ==(SMouseWheel const& p) const { return (p.Up == Up); };
        bool Up;    //!< False if down
    };

    struct SMouseButton {
        bool operator ==(SMouseButton const& p) const { return (p.Button == Button); };
        int Button;
    };

    // for variant.which EInputType::None
    //nullptr
    //struct SNullType;
    struct SNullType { bool operator==(const SNullType& t) const { return true;}; };

    // possede which, empty,type
    // doit respecter la numeroration de input type
    // == existe mais en free function
    // get<int>
    // get<0>
    /** \warning Structures must remain in the same order as EInputMode
    **/
    boost::variant<SNullType,irr::EKEY_CODE,SJoyAxis,SJoyButton,EPovDirection,SMouseWheel,SMouseButton> Value;


    static const wchar_t* StrUndefined;

    // TODO a deplacer
    static TKeyCodeMap keycodeBimap;
    static TDeviceCodeMap deviceCodeMap;


    // Check if Id exists for that device
    //bool isValid() const;

    bool undefined() const;
    bool isAutorepeatEnabled() const;
    void setRepeatDelay(irr::u32 const& );
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


    // proposer plein de constructeurs
    //bool setup(const EInputType&, int const&);
    bool setup(wchar_t* const& key);
    void setup(irr::EKEY_CODE const& keyCode);

    // Setup axis
    // TODO a terme pvr distinguer entre les joysticks
    //joystickName& joystick,
    bool setup(irr::EJOYSTICK_AXIS const&,EAxisDirection const&);


    void setup(EPovDirection const& povDirection);

    //void setup(E_JOYSTICK_AXIS const& povDirection);

//joystickName& joystick,
    // Setup joystick button
    bool setup(irr::u16 const& joyButton);


    //bool setup(char const& key);
    //bool setup(char* const strType);


    std::wstring generateDescription() const;
};



#endif
