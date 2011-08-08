/**
\file config_manager.h

Refaire pour l'adapter avec le systeme de boost::program_options
*/
#ifndef _BC_CEVENTMAPPING_HPP_INCLUDED
#define _BC_CEVENTMAPPING_HPP_INCLUDED


#include <irrlicht.h>  // header only
#include <string>
#include <list>
#include <boost/bimap.hpp>
#include <fusion/core/CStringBuilder.hpp>

namespace bbi = boost::bimaps;

const irr::u16 _threshold = 16000;


namespace NInputType {

enum EId {
//NULL,  /**< NULL type ... not used */
UNDEFINED,
KEY,  /**< keyboard type */
JOY_AXIS_PLUS,  /**< joystick axis type */
JOY_AXIS_MINUS,  /**< joystick axis type */
MOU_MOVE,  /**< mouse movement type */
MOU_WHEEL,  /**< mouse wheel type */
MOU_BTN,  //< mouse button type
JOY_BTN,  //< joystick button type
JOY_POV   //< joystick POV type
};
}

// forward declaration
class CEventMapping;

class CEventMapping
{

    typedef std::wstring TWString;
    TWString _name;


    NInputType::EId _type;
public:
    typedef irr::u32 TimeUnit;


    void toXmlString(fus::TWCharStringBuilder& str) const;




    bool processEvent(const irr::SEvent&,const bool& enableMouse,const bool& enableJoystick);

protected:
    bool processEvent(const irr::SEvent::SMouseInput&);
    bool processEvent(const irr::SEvent::SJoystickEvent&);

public:

    bool undefined() const { return ( (_type == NInputType::UNDEFINED) ); };

    CEventMapping(const TWString name = L"Unknown",const NInputType::EId& = NInputType::UNDEFINED,const irr::s32& = -1);

    bool operator==(const CEventMapping&);

    bool loadFromDescription(const std::string& description);
    //bool loadFromXml(const std::string& description);

    bool init(const TWString&,const NInputType::EId&,const irr::s32&);
    bool setup(const NInputType::EId&,const irr::s32&);
    bool setup(const irr::core::stringw& strType,const irr::core::stringw& strValue);
    //bool setup(const wchar_t* strType,const wchar_t* strValue);
    //irr::EEVENT_TYPE type;


    //The POV represents the angle of the POV hat in degrees * 100, from 0 to 35,900.
    //A value of 65535 indicates that the POV hat is centered (or not present).
    //This value is only supported on Windows. On Linux, the POV hat will be sent as 2 axes instead.

    inline
    bool povBeingUsed(const irr::SEvent::SJoystickEvent& event) const {
        return (event.POV != 65535);
    }



    void setName( const TWString& );
    const wchar_t* getName( ) const { return _name.c_str();};


    //irr::core::stringw _description;

    bool matchesEvent(const irr::SEvent&) const;
    bool matchesJoystickEvent(const irr::SEvent::SJoystickEvent&) const;

    //const wchar_t*
    irr::core::stringw generateDescription() const;
    //const wchar_t* getDescription() const {return _description.c_str();};
    //const wchar_t*
    irr::core::stringw valueToString() const;
    const irr::s32& getValue() const {return _value;};
    static const irr::core::stringw& keyCodeToString(const irr::EKEY_CODE&);
    const irr::core::stringw& typeToString() const;



//protected:
//    union {
//    irr::EKEY_CODE KeyCode;
//    irr::s32 _value; //pr le caliver uniquement
//    } _value;


    irr::s32 _value;

    //static bool isMappingForbidden();
    static void initializeBimaps();

    //const wchar_t*
    typedef bbi::bimap< int , irr::core::stringw > TBiMap;
    typedef TBiMap::value_type TKeyAssociation;
    static TBiMap _keyMap;
    static TBiMap _inputTypes;

    static irr::core::stringw _unknown;

    //bool updateState(const irr::SEvent& e);

    void setRepeatDelay(const irr::u32& repeatDelay) {
        _normalizedRepeatDelay = repeatDelay;
    }

    void enableRepeat(const bool& enableRepeat) {
        //_normalizedRepeatDelay = repeatDelay;
        _bRepeat = enableRepeat;
    }


    bool repeat() const {return _bRepeat; }
    //const bool& isActive() const {return _state;};
//
//private:


    bool checkState();
    bool _bRepeat;
    irr::u32 _normalizedRepeatDelay;
    irr::u32 _lastActivation;
    //int _times;
    //bool _state;   // Sert uniquement pr le clavier
};

#endif
