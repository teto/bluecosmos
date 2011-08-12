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
        //
    };

    // TODO renommer en CachedValue
    SCachedState PastValue;     //!< Record of previous state
    bool QuickDelayRespected;   //!< To detect double tap

    irr::u32 TimeOfLastStateChange;
    irr::u32 TimeOfNextRepeat;  //!< Time of next repeat


    SBindCache();

    //! current state of the cache computed during last frame
    bool believedState() const;

    //void newActivation(TTimeUnit const&);
    //ETapMode update(TTimeUnit const& currentTime, const bool const& state);
    // TODO a bit ugly to pass the descriptor
    ETapMode update(TTimeUnit const& currentTime, const CBindDescriptor& , bool const& state);

protected:
    //onPress onrelease
    //int Value;
};


#endif // SBindCache_HPP_INCLUDED
