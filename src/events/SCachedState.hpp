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

    TTimeUnit OldDuration;
    bool QuickDelayRespected;   //!< To detect double tap

    bool State;

    // Times it was up
    TTimeUnit TimeOfLastStateChange;

    TTimeUnit TimeOfNextRepeat;  //!< Time of next repeat


    SBindCache();



    bool update(TTimeUnit const& currentTime, const CBindDescriptor& );

protected:
    //onPress onrelease
    //int Value;
};


#endif // SBindCache_HPP_INCLUDED
