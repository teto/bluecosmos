#ifndef SCACHEDSTATE_HPP_INCLUDED
#define SCACHEDSTATE_HPP_INCLUDED


//#include
#include "defs.hpp"
#include <irrlicht.h>
#include <string>

// On l'utilise comme une constante
const irr::u32 DoubleTapDelay = 100;

struct SCachedState
{

    typedef irr::u32 TTimeUnit;

    // 0 => oldest one
    std::pair<bool,irr::u32> Values[2];




    SCachedState() //: _LastButOne(0), _lastPress(0)
    {
        Values[0] = std::make_pair(0,0);
        Values[1] = std::make_pair(0,0);
    }


    //void newActivation(TTimeUnit const&);
    ETapMode update(TTimeUnit const& currentTime, bool const& state);

    //int Value;
};


#endif // SCACHEDSTATE_HPP_INCLUDED
