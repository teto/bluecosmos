#include "SCachedState.hpp"
#include "SCachedState.hpp"

//: _LastButOne(0), _lastPress(0)
SBindCache::SBindCache() :
    NextPress(0)
    , TimeOfLastStateChange(0)
    , TimeOfNextRepeat(0)
    , QuickDelayRespected(false)
{
    PastValue = std::make_pair(0,0);
    //Values[1] = std::make_pair(0,0);
}



bool
SBindCache::believedState() const {
    return !PastValue.state;
}


// TODO configuré juste pr les JustPressed pr l'instant
//bool
ETapMode
SBindCache::update(TTimeUnit const& currentTime,const CBindDescriptor& d, bool const& currentState) {

    BOOST_ASSERT(TimeOfLastStateChange < currentTime);

    ETapMode mode ;

    // If states are the same as previous one
    if(currentState == this->believedState() ) {

        // if state up and autorepeat enabled for that descriptor
        // (d.Mode != JustReleased)
        // TODO on pourrait generaliser ca au justReleased
        if(currentState){

            if(d.isAutorepeatEnabled() && (d.Mode == ETapMode::JustPressed) ){

                /// if should be repeated
                if( currentTime < TimeOfNextRepeat ){

                    // set next trigger
                    TimeOfNextRepeat += (*currentTime.RepeatTime);
                    QuickDelayRespected = false;
                    return true;
                    //mode = ETapMode::JustPressed;
                }
            }
        }
//        else {
//            mode = ETapMode::Released ;
//        }

    }
    /// if state change
    /// if State differ from last one
    else {

        TimeOfLastStateChange = currentTime;

        SCachedState newCache = {};
        newCache.Duration = currentTime - TimeOfLastStateChange;
        newCache.State = currentState;


        // compute duration
        //const irr::u32 currentDuration = currentTime - TimeOfLastStateChange;
        // remplacer 100 par QuickTapDelay
        // (PastValue.duration < QuickTapDelay) &&

        //NextPress
        if( currentState == false){
            mode = ETapMode::JustReleased;
        }
        // If new state is true
        // check for double Tap
        else if( (d.Mode == ETapMode::DoublePressed) && (newCache.Duration < QuickTapDelay) && ){
                mode = ETapMode::DoublePressed;
                //= true;

            //DoubleTapDelay > currentTime){


        }
        // Otherwise singleTap
        else {
            mode = ETapMode::JustPressed;
        }

        PastValue = newCache;
    }
    //return std::move(mode);
    return mode;
    //return ( d.Mode == mode);
    //return false;
}
