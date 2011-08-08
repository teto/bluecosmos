#include "SCachedState.hpp"


    //void newActivation(TTimeUnit const&);
    ETapMode SCachedState::update(TTimeUnit const& currentTime, bool const& state) {

        ETapMode mode ;

        // If states are the same as previous one
        if(state == Values[1].first)  {

            mode = (state == false) ? ETapMode::Released : ETapMode::Pressed;
            /*if(state == false){
                return ETapMode::Released;
            }
            else {
                return ETapMode::Pressed;
            }*/
        }
        else {

            // State differ from last one
            if( state == false){
                mode = ETapMode::JustReleased;
            }
            // If new state is true
            // check for double Tap
            else if(Values[0].second + DoubleTapDelay > currentTime){

                mode = ETapMode::DoublePressed;
            }
            // Otherwise singleTap
            else {
                mode = ETapMode::JustPressed;
            }
            Values[0] = Values[1];
            Values[1].first = false;
            Values[1].second = currentTime;
        }
        return std::move(mode);
    }
