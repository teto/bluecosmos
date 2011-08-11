#ifndef SBindCache_HPP_INCLUDED
#define SBindCache_HPP_INCLUDED


//#include
#include "defs.hpp"
#include <irrlicht.h>
#include <string>
#include <boost/optional.hpp>

// On l'utilise comme une constante
const irr::u32 DoubleTapDelay = 100;

// Renommer en S
struct SBindCache
{

    typedef irr::u32 TTimeUnit;

    /** 0 => oldest one
    first boolean => state
    clearer this way
    **/
    struct SCachedState {
        bool state;
        irr::u32 duration;
    };

    std::pair<bool,irr::u32> PastValue;
    SCachedState PastValue;
    irr::u32 TimeOfLastStateChange;

    //! in case autorepeat is enabled
    irr::u32 NextPress;

    SBindCache();

    bool believedState() const;

    //void newActivation(TTimeUnit const&);
    //ETapMode update(TTimeUnit const& currentTime, const bool const& state);
    bool update(TTimeUnit const& currentTime, const CBindDescriptor& , bool const& state);

protected:
    //onPress onrelease
    //int Value;
};


#endif // SBindCache_HPP_INCLUDED
