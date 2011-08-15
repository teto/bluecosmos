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
#include "CInputManager.hpp"

#include "../def.hpp"
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/vector_of.hpp>
#include <vector>

namespace bbi = boost::bimaps;


namespace input {

// fwd declaration
template<class ID_TYPE>
class IInputCache;

//struct fullId {};
//struct descriptor {};

// Passer le TFullId en parametre
class CBindCollection
{

public:
    //typedef ID_TYPE TBindId;


    //typedef Cache<NPlayerInput::Count,NPlayerInput::EId > TCache;
    typedef NPlayerInput::EId TBindId;
    typedef int TParam;
    typedef std::pair<TBindId,TParam> TFullId;

    //SIZE
    typedef IInputCache<TBindId> TCache;

    //typedef typename boost::optional< std::vector<TFullId> > TOptionalVector;
    typedef typename boost::optional<TFullId> TOptionalFullId;
    //typedef SBimap< TFullId, CBindDescriptor > TDescriptorList;
    // taggeddescriptor
    //unordered_set_of
    //bbi::unordered_set_of<
    // Ici pr choisir le type de container
    //http://www.boost.org/doc/libs/1_47_0/libs/bimap/doc/html/boost_bimap/the_tutorial/controlling_collection_types.html#boost_bimap.the_tutorial.controlling_collection_types.configuration_parameters

    //set_of => ordered, unique
    //unordered_set_of 	=> hashed, unique
    // vector_of=> mutable,random access with view "vector_map "
    // set_of and unordered_set_of map views overload operator[] to retrieve the associated data of a given key only when the other collection type is a mutable one.
    //, bbi::list_of_relation
    //typedef bbi::bimap< bbi::unordered_set_of< TFullId>, bbi::vector_of<CBindDescriptor> > TDescriptorList;
    typedef std::map< TFullId, CBindDescriptor > TDescriptorList;
    //typedef std::multimap< TBindId , TParam> TFullIdList;

protected:

    TDescriptorList _descriptors;
    //TFullIdList _fullIdsList;
public:
    //TCache* generateCache();

    //std::vector<CBindDescriptor>
    // Va chercher le numero 0
    //const CBindDescriptor& operator[](TBindId const&) ;
    const CBindDescriptor& operator[](TFullId const&) ;


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
    TOptionalFullId
    containBind(CBindDescriptor const& descriptor);




    // Essayer de remettre un const devant inputMgr
    void updateCache( TTimeUnit const& currentTime, CInputManager& inputMgr, TCache* cache) const;

    // On peut utiliser la fonction map.count()
    // renvoyer un tableau d'iterateur ?
    //std::size_t getDescriptors(TBindId const& id, TIdDescriptors& descriptors);


};

// mutlimap version
//std::pair<typename TDescriptorList::iterator,typename TDescriptorList::iterator> result = _descriptors.equal_range( descriptor );
//if(result == _descriptors.end())
//for(auto it(result.first) ; it != result.second; ++it){

}

#endif
