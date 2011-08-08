#ifndef CAUTOMATICCLOCK_HPP
#define CAUTOMATICCLOCK_HPP

#include "IClock.hpp"

class CAutomaticClock : public IClock<irr::u32>
{

protected:

    TTimer::TimeType _targetedTime;
    TTimer::TimeType _interval;

public:
    static irr::ITimer* _timer;

    //
    CAutomaticClock(const TimeType& targetedTime = 0);

    void setTimer(const TimeType& targetedTime) {

        _interval = targetedTime;
        restart();
    }


    TimeType getElapsedTime() const{
        return (_interval - _targetedTime);
    }

    TimeType getTimeLeft() const {

        return (_targetedTime - _timer->getTime()) ;
    }


    void restart() {
        _targetedTime = _interval + _timer->getTime();
    }

    // ou double ?
    // compris entre 0 et 1
    double getAdvancement() const {
        return getElapsedTime()/_interval;
    }


    virtual bool reached() const {
        return ( _timer->getTime() <= _targetedTime );
    };


};


#endif
