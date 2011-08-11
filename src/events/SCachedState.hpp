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

    /**
    first boolean => state
    clearer this way
    **/
    struct SCachedState {
        SCachedState() : State(0),Duration(0) {}
        bool State;
        irr::u32 Duration;
    };

    SCachedState PastValue;

    bool DoubleTapDelayExceeded;
    irr::u32 TimeOfLastStateChange;
    irr::u32 NextPress;
    //! in case autorepeat is enabled


    SBindCache();

    bool believedState() const;

    //void newActivation(TTimeUnit const&);
    //ETapMode update(TTimeUnit const& currentTime, const bool const& state);
    ETapMode update(TTimeUnit const& currentTime, const CBindDescriptor& , bool const& state);

protected:
    //onPress onrelease
    //int Value;
};


#endif // SBindCache_HPP_INCLUDED
