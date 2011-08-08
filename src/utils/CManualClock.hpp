#ifndef CMANUALCLOCK_HPP
#define CMANUALCLOCK_HPP

#include "IClock.hpp"


class CManualClock : public IClock<irr::u32>
{
public:
   CManualClock(const irr::u32& targetedTime = 0) :
    _elapsedTime(0),
    _targetedTime(targetedTime)
    //targetedTime
    {}

    void setTimer(const irr::u32& targetedTime) {
        _targetedTime = targetedTime;
    }

    void restart(){
        _elapsedTime = 0;
    }

    bool reached() const {
        return (_targetedTime <= _elapsedTime) ;
    }

    ////////////////////////////////
    //
    // \return True when timer elapsed
    ////////////////////////////////
    inline void update(const irr::u32& elapsedTime){
        _elapsedTime += elapsedTime;
    }

    inline
    bool operator+=(const irr::u32& elapsedTime){
        update(elapsedTime);
        return reached();
    }

//    inline
//    bool operator=(const T& elapsedTime){
//        _elapsedTime = elapsedTime;
//        return _elapsedTime;
//    }

    inline
    bool operator<(const irr::u32& elapsedTime){
        return (_elapsedTime < elapsedTime);
    }

    inline
    bool operator<=(const irr::u32& elapsedTime){
        return (_elapsedTime <= elapsedTime);
    }

    inline
    bool operator>(const irr::u32& elapsedTime){
        return (_elapsedTime > elapsedTime);
    }

    inline
    bool operator>=(const TimeType& elapsedTime){
        return (_elapsedTime >= elapsedTime);
    }


    const TimeType& getElapsedTime() const { return _elapsedTime;}
    TimeType getTimeLeft() const { return (_targetedTime-_elapsedTime);}
    void reset() { _elapsedTime = 0;}
    // ou double ?
    // compris entre 0 et 1
    double getAdvancement() const { return ((double)_elapsedTime/(double)_targetedTime);}
    ~CManualClock() {};


protected:
    TimeType _elapsedTime;
    TimeType _targetedTime;

};

#endif
