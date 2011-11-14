#include "SCachedState.hpp"
#include "CBindDescriptor.hpp"



//
//bool
//SCachedState::operator==(const SCachedState& p) const {
//
//    return ( (Duration == p.Duration) && (p.State == State ) );
//}
//
//
//bool
//SCachedState::operator!=(const SCachedState& p) const {
//    return !(*this == p);
//}
//

//: _LastButOne(0), _lastPress(0)
SBindCache::SBindCache() :
    //NextPress(0)
    //,
    OldDuration(0)
    , State(false)  //EButtonState::Released)
    , TimeOfLastStateChange(0)
    , TimeOfNextRepeat(0)
    , QuickDelayRespected(false)
{
    //PastValue = std::make_pair(0,0);
    //Values[1] = std::make_pair(0,0);
}


// TODO passer le IInputManager* à cause des joysticks ou bien passer un array de joysticks ? pour l'instant ne fonctionne qu'avec le clavier
SBindCache::update(TTimeUnit const& currentTime,const CBindDescriptor& d)
{

}

//boost::optional<TTimeUnit>& const repeatTime
// bool autorepeat / timerepeat
bool
SBindCache::update(TTimeUnit const& currentTime,const CBindDescriptor& d, bool const& currentState)
{

    //_INFO << "Current time" << currentTime << "/" << TimeOfLastStateChange;
    BOOST_ASSERT( (TimeOfLastStateChange <= currentTime) && "Current time should be bigger than last time");

    bool ret = false;

    // If states are the same as previous one
    if(currentState == State)
    {
            // if autorepeat, might still return true
            if( d.isAutorepeatEnabled() ){

                /// if should be repeated
                if( currentTime < TimeOfNextRepeat ){

                    // set next trigger
                    //TimeOfNextRepeat += (*currentTime.RepeatTime);
                    TimeOfNextRepeat += (*d.RepeatTime);
                    QuickDelayRespected = false;
                    //return true;
                    //mode = EButtonState::JustPressed;
                    ret = true;
                }
            }

//        else {
//            mode = ETapMode::Released ;
//        }

    }
    /// if state change
    /// if State differ from last one
    else
    {

        State = currentState;
        ret = true;
        TimeOfLastStateChange = currentTime;

        const TTimeUnit newDuration = currentTime - TimeOfLastStateChange;

        if( currentState == true){

            QuickDelayRespected = ((newDuration < QuickTapDelay) && (OldDuration < QuickTapDelay) ) ? true : false;
//            mode = EButtonState::JustPressed;
        }

        OldDuration = newDuration;
    }

    return ret;
}


