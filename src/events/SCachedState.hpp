#ifndef SBindCache_HPP_INCLUDED
#define SBindCache_HPP_INCLUDED


//#include
#include "defs.hpp"
#include <irrlicht.h>
#include <string>
#include <boost/optional.hpp>



// On l'utilise comme une constante
const TTimeUnit DoubleTapDelay = 100;


/**
first boolean => state
clearer this way
**/
//struct SCachedState {
//    SCachedState() : State(0),Duration(0) {}
//    bool State;
//    irr::u32 Duration;
//    //
//    bool operator==(const SCachedState&) const;
//    bool operator!=(const SCachedState&) const;
//};


class CBindDescriptor;

// Renommer en S
struct SBindCache
{

    //typedef irr::u32 TTimeUnit;


    // TODO renommer en CachedValue
    //SCachedState PastValue;     //!< Record of previous state
    TTimeUnit OldDuration;
    bool QuickDelayRespected;   //!< To detect double tap

    bool State;

    TTimeUnit TimeOfLastStateChange;
    TTimeUnit TimeOfNextRepeat;  //!< Time of next repeat


    SBindCache();

    //! current state of the cache computed during last frame
    //bool believedState() const;

    //void newActivation(TTimeUnit const&);
    //ETapMode update(TTimeUnit const& currentTime, const bool const& state);
    // TODO a bit ugly to pass the descriptor
    //ETapMode
    //boost::optional<SCachedState>
    //boost::optional<ETapMode>
    bool // s'il y a eu un changement
    update(TTimeUnit const& currentTime, const CBindDescriptor& , bool const& state);

protected:
    //onPress onrelease
    //int Value;
};


#endif // SBindCache_HPP_INCLUDED
