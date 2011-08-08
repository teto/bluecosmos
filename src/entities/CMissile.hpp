/**
\file
\author
**/
#ifndef CMISSILE_HPP
#define CMISSILE_HPP


#include "CStaticBattery.hpp"


class CMissile :
public CStaticBattery
//,
//public Tracker;
{
private:

protected:
    //CStaticBattery* _target;
public:

    CMissile();
    //~CMissile();


    TVector3df _forward;
    TVector3df _speed;
    TVector3df _lockedPosition;

    const NEntityType::EId getType() const { return NEntityType::Missile;};

    void kill();

    //bool setup(const char* model, CFleet* fleet, const TVector3df& position,const TVector3df& forward);
    bool setup( const char* model, CFleet* fleet, const TVector3df& position,const TVector3df& forward);

    bool update(const TTimer::TimeType&);

};

#endif
