#include "SCachedState.hpp"

//: _LastButOne(0), _lastPress(0)
SBindCache::SBindCache() :
    NextPress(0)
    , TimeOfLastStateChange(0)
{
    PastValue = std::make_pair(0,0);
    //Values[1] = std::make_pair(0,0);
}

bool
SBindCache::believedState() const {
    return !PastValue.state;
}
//void newActivation(TTimeUnit const&);
//ETapMode
// TODO configuré juste pr les JustPressed pr l'instant
bool
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
                if( currentTime < (*currentTime.RepeatTime) + NextPress ){

                    // set next trigger
                    NextPress += (*currentTime.RepeatTime);
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
        // compute duration
        const irr::u32 currentDuration = currentTime - TimeOfLastStateChange;

        //NextPress
        if( currentState == false){
            mode = ETapMode::JustReleased;
        }
        // If new state is true
        // check for double Tap
        else
//            if(d.Mode == ETapMode::DoublePressed){
//
//            }
//
            // remplacer 100 par une variable statique
            if( (PastValue.duration < 100) && (currentDuration < 100) ){
                mode = ETapMode::DoublePressed;
            }
            //DoubleTapDelay > currentTime){


        }
        // Otherwise singleTap
        else {
            mode = ETapMode::JustPressed;
        }

//        Values[0] = Values[1];
//        Values[1].first = false;
//        Values[1].second = currentTime;
    }
    //return std::move(mode);
    return ( d.Mode == mode);
    return false;
}
