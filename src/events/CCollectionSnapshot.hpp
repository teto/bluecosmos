#ifndef _BC_CCollectionSnapshot_HPP_INCLUDED
#define _BC_CCollectionSnapshot_HPP_INCLUDED

//#include "CBindDescriptor.hpp"
#include <array>

//class CBindDescriptor;

template<std::size_t SIZE>
class CCollectionSnapshot
{
    // state / lastActivationTime
    //std::vector< std::pair<bool,irr::u32> > _map;
    std::array< bool,SIZE > _map;

public:
    bool
    operator[](const int& id) {
        return getState(id);
    }

    inline bool&
    getState(const int& id) {
        return _map[id];
    }

//    CBind();
//
//    bool checkState(const irr::u32& currentTime);
//
//protected:
//    bool updateLastActivationTime(const irr::u32& registeredActivationTime, const irr::u32& currentTime) ;
//
//
//    irr::u32 _lastActivation;

};


#endif
