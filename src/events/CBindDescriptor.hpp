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


namespace input {


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
        SJoyButton() : Button(0) {};
        bool operator==(SJoyButton const& b) const { return (b.Button == Button);};
        int Button;
    };


    struct SJoyAxis {
        bool operator ==(SJoyAxis const& p) const { return (p.Axis == Axis && p.Direction == Direction); };
        //SJoyAxis()
        int Axis;
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


    std::wstring generateDescription() const;
};


}


#endif
