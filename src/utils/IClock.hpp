#ifndef ICLOCK_HPP
#define ICLOCK_HPP


#include <irrlicht.h>

//class ICountdown


/**
Les timers doivent deriver de cette classe pr assurer un changement facile
**/
// rename en CClock / CTimer ?
template<typename T>
class IClock
{

public:
    typedef T TimeType;
    //virtual IClock(const T& targetedTime = 0);
    virtual void setTimer(const T& targetedTime) = 0;
    //virtual T getElapsedTime() const = 0;
    //virtual const T& getTimeLeft() const = 0;
    virtual void restart() =  0;
    // ou double ?
    // compris entre 0 et 1
    //virtual double getAdvancement() const = 0;

    virtual bool reached() const = 0;

/*
    inline
    bool operator+=(const T& elapsedTime){
        return update(elapsedTime);
    }

//    inline
//    bool operator=(const T& elapsedTime){
//        _elapsedTime = elapsedTime;
//        return _elapsedTime;
//    }

    inline
    bool operator<(const T& elapsedTime){
        return (_elapsedTime < elapsedTime);
    }

    inline
    bool operator<=(const T& elapsedTime){
        return (_elapsedTime <= elapsedTime);
    }

    inline
    bool operator>(const T& elapsedTime){
        return (_elapsedTime > elapsedTime);
    }

    inline
    bool operator>=(const T& elapsedTime){
        return (_elapsedTime >= elapsedTime);
    }
*/
private:
    //T _interval;
};






//typedef IClock<irr::u32> TTimer;
//typedef IClock<irr::u32> TBaseTimer;


#endif // ICLOCK_HPP
