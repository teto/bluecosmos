/**
\file
\author
**/
#ifndef CBULLET_HPP
#define CBULLET_HPP

#include <irrlicht.h>
#include "CStaticBattery.hpp"

class CBullet :
public CStaticBattery
{
public:
    CBullet();
    //bool setup(const char* model, CFleet* fleet, const TVector3df& position,const TVector3df& forward);

    virtual ~CBullet();

    const NEntityType::EId getType() const { return NEntityType::Bullet;};

    // returns true if timer out
    bool update(const TTimer::TimeType&);

    TVector3df _forward;//!< direction the battery is facing

//Movd into CStaticBatt
    //irr::core::vector3df _forward;
protected:

    //friend class
};

#endif // CBULLET_HPP
