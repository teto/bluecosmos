#ifndef _BC_CPLAYERINPUTCACHE_HPP_INCLUDED
#define _BC_CPLAYERINPUTCACHE_HPP_INCLUDED

#include "../def.hpp"
#include "IInputCache.hpp"
#include <array>

class CPlayerInputCache :
    public input::IInputCache<NPlayerInput::EId>
{

    //static const std::size TSize = NPlayerInput::Count ;
    typedef NPlayerInput::EId ID_TYPE;
public:
    typedef std::array<bool,NPlayerInput::Count > TCachedInput;// As many bools as Ids
    TCachedInput _cachedInput;


    CPlayerInputCache( ) {
        reset();
    }

    void reset(){
        _cachedInput.fill(0);
    }

    void setState(ID_TYPE const& id,bool const& value) {
        _cachedInput[id] = value;
    }

    const bool& isActive(ID_TYPE const& id) const { return _cachedInput[id];};
    //
    // todo faire des update_or, update_and etc...
    //void updateBind(TFullId const& fullId, irr::u32 const& currentTime, const bool& currentState,ETapMode const& mode);
//    {
//        // Mode
//        // |=
//        _cachedInput[id] |= ( mode == _states[id].update( currentTime,currentState) );
//    }

    //int newEvents;

protected:

};

#endif
