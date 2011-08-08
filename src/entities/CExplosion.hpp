/**
\file
\author
**/
#ifndef CMISSILE_HPP
#define CMISSILE_HPP


#include "CStaticBattery.hpp"


class CMissile :
public CStaticBattery
{

public:
    CStaticBattery* _target;
    irr::core::vector3df _forward;
    irr::core::vector3df _speed;
    irr::core::vector3df _lockedPosition;

    void suicide();
    void setTarget(CStaticBattery*);

    bool update(const irr::u32&);

};

#endif
