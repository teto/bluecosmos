#ifndef _BC_IINPUTCACHE_HPP_INCLUDED
#define _BC_IINPUTCACHE_HPP_INCLUDED

#include <irrlicht.h>
#include <map>
#include "defs.hpp"
#include "SCachedState.hpp"

// passer fullId en parametre template ?
template<class ID_TYPE>
class IInputCache
//: public IInputCache<NPlayerInput::EId>
{

public:
    typedef std::pair<ID_TYPE,int> TFullId;
    typedef std::map< TFullId, SBindCache> TBufferedStates;

    TBufferedStates _states;
    //typedef std::map< ID_TYPE,bool> TCachedInput;
    //typedef std::map< ID_TYPE,SCachedState> TBufferedStates;

    //TBufferedStates _states;

    const bool& operator[](ID_TYPE const& id) const { return isActive(id);};
    virtual const bool& isActive(ID_TYPE const& id) const = 0;

    // TODO remplacer bool par Mode
    virtual void setState(ID_TYPE const& id,bool const& value) = 0;


    // todo faire des update_or, update_and etc...
    void updateId(TFullId const& fullId, irr::u32 const& currentTime, const bool& currentState,ETapMode const& mode) {

        const bool res = ( mode == _states[ fullId ].update( currentTime,currentState) );
        setState(fullId.first,res);
    }

};

#endif
