/**
\file config_manager.h

Refaire pour l'adapter avec le systeme de boost::program_options
*/
#ifndef _BC_CBindCollection_HPP_INCLUDED
#define _BC_CBindCollection_HPP_INCLUDED


#include <irrlicht.h>  // header only
#include <array>
#include <fusion/logging/ILogger.hpp>
#include <boost/bimap.hpp>
#include <boost/optional.hpp>
#include <boost/noncopyable.hpp>
#include <map>
#include <fusion/utilities/SBimap.hpp>
#include "CBindDescriptor.hpp"
#include "CBind.hpp"
//#include "CInputManager.hpp"

#include "../def.hpp"
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/vector_of.hpp>
#include <vector>
#include "CBindDescriptor.hpp"
#include "SCachedState.hpp"
#include <irrlicht.h>

namespace bbi = boost::bimaps;




// fwd declaration
//template<class ID_TYPE>
//class IInputCache;


struct SAssociatedStruct
{
    SAssociatedStruct() {};
    CBindDescriptor Descriptor;
    SBindCache State;
};


// Passer le TFullId en parametre
class CBindCollection
{

public:
    //typedef ID_TYPE TBindId;


    //typedef Cache<NPlayerInput::Count,NPlayerInput::EId > TCache;
    typedef NPlayerInput::EId TBindId;
    typedef int TParam;
    typedef std::pair<TBindId,TParam> TFullId;  //!< This way we can have several shortcuts associated with a unique action !

    //typedef IInputCache<TBindId> TCache;

    typedef typename boost::optional<TFullId> TOptionalFullId;


    //typedef std::map< TFullId, CBindDescriptor > TDescriptorList;
    typedef std::map< TFullId, SAssociatedStruct > TDescriptorList;

protected:

    TDescriptorList _descriptors;
public:



    const CBindDescriptor& operator[](TFullId const&) ;


    /**
    Return vector of ids and of size < limit matching the descriptor. Useful to check if a descriptor was already registered

    **/
    std::vector<TFullId>
    getAssociatedIds( CBindDescriptor const& descriptor, std::size_t const& limit) const;

    void removeBinds(TFullId const& id);
    // TODO for descriptor
    //void removeBinds(TBindId const& id);


    /**
    Returns identifier matching current "id" mode with descriptor
    ,ETapMode const& = ETapMode::JustPressed
    // = -1
    **/
    //,TParam const& param
    CBindDescriptor&
    setBind(TFullId const& id,CBindDescriptor const& descriptor);

    /**
    \returns Id of matching descriptor/mode if exists, otherwise returns unitialiazed
    //, ETapMode const& mode
    **/
    //TOptionalFullId
    bool containBind(CBindDescriptor const& descriptor, TFullId& id);



    //bool processEvent(TTimeUnit const& currentTime, const irr::SEvent& event);
    //void updateCache(TTimeUnit const& currentTime, const irr::SEvent& event);
    void   updateCache( TTimeUnit const& currentTime, const CBindDescriptor& eventDescriptor,const bool& currentState);


    // Essayer de remettre un const devant inputMgr
    //void updateCache( TTimeUnit const& currentTime, CInputManager& inputMgr, TCache* cache) const;



};

// mutlimap version
//std::pair<typename TDescriptorList::iterator,typename TDescriptorList::iterator> result = _descriptors.equal_range( descriptor );
//if(result == _descriptors.end())
//for(auto it(result.first) ; it != result.second; ++it){


#endif
