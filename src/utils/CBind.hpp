#ifndef _BC_CBind_HPP_INCLUDED
#define _BC_CBind_HPP_INCLUDED

#include "CEventMapping.hpp"

//class CBindDescriptor;

class CBind :
    public CBindDescriptor
{

    CBind();

    bool checkState(const irr::u32& currentTime);

protected:
    bool updateLastActivationTime(const irr::u32& registeredActivationTime, const irr::u32& currentTime) ;


    irr::u32 _lastActivation;

};


#endif
