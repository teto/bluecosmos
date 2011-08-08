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
#include "CBindDescriptor.hpp"
#include "CBind.hpp"
#include "CInputManager.hpp"
#include "SCachedState.hpp"


namespace bbi = boost::bimaps;




// forward declaration
//class CBindDescriptor;
//class CBindEntry;

// Fwd declaration
template <int SIZE,class ID_TYPE>
class CBindCollection ;

template <int SIZE,class ID_TYPE>
class Cache
{

//    irr::u32 LastUpdateTime;
//    irr::u32 CurrentUpdateTime;

    typedef CBindCollection<SIZE,ID_TYPE> TBindCollection;
    friend class CBindCollection<SIZE,ID_TYPE>;
    TBindCollection* _collection;
public:
    typedef std::array<bool,SIZE> TCachedInput;// As many bools as Ids

    typedef std::array< SCachedState,SIZE> TBufferedStates;
    TBufferedStates _states;
    TCachedInput _cachedInput;




//: _collection(collection)
    Cache( )
    {
        _cachedInput.fill(0);
    }

    const bool& isActive(ID_TYPE const& id) const { return _cachedInput[id]; };


//    update(){
//        _cachedInput.fill(0);
//      updateId
//    }

protected:
    //
    void updateId(ID_TYPE const& id, irr::u32 const& currentTime, const bool& currentState,ETapMode const& mode){
        // Mode
        // |=
        _cachedInput[id] |= ( mode == _states[id].update( currentTime,currentState) );
    }

    //int newEvents;



};


#define GET_MODE(id) _binds[id]

// fwd declaration
template <int SIZE,class ID_TYPE>
class CBindCollection;

// Proxy

template <int SIZE,class ID_TYPE>
class CProxy : boost::noncopyable
{
    //
    CBindCollection<SIZE, ID_TYPE>* _master;
public:
    typedef std::vector< CBindDescriptor* > TDescriptors;
    CProxy( CBindCollection<SIZE, ID_TYPE>& collection) : _master( collection ) {

    }
    //operator[]()CBindDescriptor
    // contain
    //bind(CBindDescriptor& descriptor);
    //remove();
    //replace()
    //size();
    TDescriptors& getDescriptors() {return _descriptors};

    // Pointe vers ceux du map
    TDescriptors _descriptors;
};

/////////////////////////////////////
///  Factory de CBindDescriptor
////////////////////////////////////
// A generaliser
// faudra pas oublier de supprimer les descriptor ?
template <int SIZE,class ID_TYPE>
class CBindCollection
{

public:
    typedef ID_TYPE TBindId;




    typedef Cache<SIZE,ID_TYPE> TCache;
    // Doivent être unique
    typedef std::array<TBindId, CProxy* > TBindsList;
    typedef std::map< CBindDescriptor, TBindId> TDescriptorList;
    //typedef std::set<CBindDescriptor> TDescriptorList

    typedef typename TDescriptorList::iterator TDescriptorIterator;

    typedef typename boost::optional<TDescriptorIterator> TReturnValue;
    //typedef std::pair<bool,TBindId> TReturnValue;
    typedef std::vector<TDescriptorIterator> TIdDescriptors;



    friend class CProxy;

protected:

    TDescriptorList _descriptors;

public:
    TCache*
    generateCache() {

        TCache *cache = new TCache();
        return cache;
        // TODO generateCache
        //return std::move(cache);
    }


    //std::vector<CBindDescriptor>
    /*TIdDescriptors
    operator[](TBindId const& id) const {

        //std::vector<CBindDescriptor> temp;
        TIdDescriptors temp;
        getDescriptors(id,temp);
        // C++0x
        return std::move(temp);
    };*/

    //const CBindDescriptor& old
    /*TReturnValue
    //replaceBind(TBindId const& id,const CBindDescriptor& newDesc,std::size_t const& position){
    replaceBind(const CBindDescriptor& old,const CBindDescriptor& newBind){


        if(getDescriptors( id, temp) <= position){
            return ret;
        }

        std::pair<TDescriptorIterator,bool> insertResult = _descriptors.insert( std::make_pair(newBind,id) );

        TReturnValue temp = addBind()

        TReturnValue res = containBind(newDesc);
        //TReturnValue res = containBind(newDesc);
        if(res){
            (*res)->first = newDesc;
            //(*res)->first.Mode = newDesc.Mode;
            return res;
        }
        return res;
    }
*/

    void removeBinds(TBindId const& id){

        TIdDescriptors temp;
        getDescriptors(id,temp);
        //std::for_each( temp.begin(), temp.end(), [] { _descr} )
        for(auto i(temp.begin() ),end(temp.end()) ; i != end ; ++i){
            _descriptors.erase( *i );
        }
    }

//    bool removeBinds(const CBindDescriptor& descriptor){
//        auto ret = containBind(descriptor);
//        if(ret){
//            _descriptors.erase( *ret );
//            return true;
//        }
//        return false;
//    }


    /**
    Returns identifier matching current "id" mode with descriptor
    **/
    TReturnValue
    //TBindId
    //CBindDescriptor&
    addBind(TBindId const& id,CBindDescriptor& descriptor,ETapMode const& = ETapMode::JustPressed){

        TReturnValue ret ;
        //assert( descriptor.undefined() );
        //if(descriptor == NullDescriptor)    return false;
        if( descriptor.undefined() ) return ret;

        //ret = containBind(descriptor);

        // If not already bound to an id
        //if(exists){ return (*exists)->first; }
        //if(ret){ return ret; }

        // else add it
        std::pair<TDescriptorIterator,bool> insertResult = _descriptors.insert( std::make_pair(descriptor,id) );

        // element didn't already exist
        if(insertResult.second == true){
            ret = insertResult.first;
        }
        // TODO return std::move(ret);


        return ret;

        //return exists;
    }


    /**
    \returns Id of matching descriptor/mode if exists, otherwise returns unitialiazed
    //, ETapMode const& mode
    **/
    TReturnValue
    containBind(CBindDescriptor const& descriptor){

        //TReturnValue
        //boost::optional<TBindId> ret;
        TReturnValue ret;
        //boost::optional<TDescriptorIterator> ret;



        TDescriptorIterator it = _descriptors.find(descriptor);

        // if match
        if( it != _descriptors.end() ){
            ret = it;
        }

        return ret;
    }




    // Essayer de remettre un const devant inputMgr
    void updateCache( const irr::u32& currentTime, CInputManager& inputMgr, TCache& cache){
        // TODO use const_iterator
        #define UPDATE_CACHE( container ) \
        for( auto i( container.begin()), end( container.end() ); i!= end; ++i){ \
            const ETapMode& mode = _binds[ i-> second ]; \
                \
            cache.updateId( i-> second, currentTime, inputMgr.getState(i->first.Device, i->first.Id), mode ); \
        }

        //UPDATE_CACHE( _descriptors[0] );
        //UPDATE_CACHE( _descriptors[1] );

        #undef UPDATE_CACHE
    }


    // On peut utiliser la fonction map.count()
    // renvoyer un tableau d'iterateur ?
    std::size_t
    getDescriptors(TBindId const& id, TIdDescriptors& descriptors) {

        descriptors.clear();

        for (auto it(_descriptors.begin()),end(_descriptors.end()); it != end ; ++it ){

            // multimap => (*it).first
            if( it->second == id){
                descriptors.push_back( it );
            }
        }
        return descriptors.size();
    }
    //or


#undef GET_MODE


};

// mutlimap version
//std::pair<typename TDescriptorList::iterator,typename TDescriptorList::iterator> result = _descriptors.equal_range( descriptor );
//if(result == _descriptors.end())
//for(auto it(result.first) ; it != result.second; ++it){

#endif
