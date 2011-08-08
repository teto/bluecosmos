#include "CAutomaticClock.hpp"

CAutomaticClock::CAutomaticClock(const irr::u32& interval)
//: _targetedTime(0),_interval(0)
{
    setTimer(interval);
    restart();
}
