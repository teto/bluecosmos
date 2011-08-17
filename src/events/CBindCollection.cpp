#include "CBindCollection.hpp"
#include "IInputCache.hpp"

#define FULL_ID(id,no) std::make_pair(id,no)

namespace input {

void
CBindCollection::updateCache( TTimeUnit const& currentTime, CInputManager& inputMgr, TCache * cache) const
{

    BOOST_ASSERT(cache);

//    for( TDescriptorList::right_const_iterator i( _descriptors.right.begin()), end( _descriptors.right.end() ); i!= end; ++i){
    for( TDescriptorList::const_iterator i( _descriptors.begin()), end( _descriptors.end() ); i!= end; ++i){

        const TFullId& fullId = i->first;
        const CBindDescriptor& descriptor = i->second;

        // TODO a revoir ptet
        cache->updateId(
                        fullId,
                        currentTime,
                        inputMgr.retrieveStateFromDescriptor(descriptor),
                        descriptor
                        //inputMgr.getState(i->first.Device, i->first.Id),
                        //descriptor.Mode
                    );
    }


}


//CBindCollection::generateCache() {
//
//    TPlayerInputCache *cache = new TCache();
//    return cache;
//    // TODO generateCache
//    //return std::move(cache);
//}


/**
modify_data to replace

    bm_type::right_iterator it = bm.right.find("one");
    bool successful_replace = bm.right.replace_key( it, "1" );
**/
const CBindDescriptor&
CBindCollection::operator[](TFullId const& fullId) {


    // Throw if doesn't exist
    //return _descriptors.left[fullId];
    return _descriptors[fullId];
};


//CBindCollection::removeBinds(CBindDescriptor const& descriptor){
//}



//CBindCollection::TReturnValue
//CBindCollection::TFullId
CBindDescriptor&
CBindCollection::setBind(TFullId const& fullId,CBindDescriptor const& descriptor){

    //auto fullId = FULL_ID(id,param);

    //std::pair< TDescriptorList::left_iterator, bool> result = _descriptors.left.insert( TDescriptorList::left_value_type(fullId,descriptor ) );
    std::pair< TDescriptorList::iterator, bool> result = _descriptors.insert( std::make_pair(fullId,descriptor ) );

    // if matching id already exist
    if( result.second == false){
        result.first->second = descriptor;
    }
    //else {
        // faudrait checker que le fullid existe pas et s'il existe utiliser modify
//        it->second = descriptor;
//    }

    // return bind
    return result.first->second;
}


std::vector< CBindCollection::TFullId >
CBindCollection::getAssociatedIds( const CBindDescriptor & descriptor, std::size_t const& limit) const {


    std::vector<TFullId>  ids;

    //for( TDescriptorList::right_const_iterator i( _descriptors.right.begin()), end( _descriptors.right.end() ); i!= end; ++i){
    for( TDescriptorList::const_iterator i( _descriptors.begin()), end( _descriptors.end() ); i!= end; ++i){

        if( descriptor == i->second){

            ids.push_back(i->first);
            if( ids.size() >= limit){
                break;
            }
        }
    }

    return ids;
}


CBindCollection::TOptionalFullId
CBindCollection::containBind(CBindDescriptor const& descriptor){

    TOptionalFullId ret;
    std::vector<TFullId>  ids;
    ids = getAssociatedIds(descriptor,1);

    if( !ids.empty() ){
        ret = ids.front();
    }

    return ret;
}



void
CBindCollection::removeBinds(TFullId const& id){

//    TIdDescriptors temp;
//    getDescriptors(id,temp);
//    //std::for_each( temp.begin(), temp.end(), [] { _descr} )
//    for(auto i(temp.begin() ),end(temp.end()) ; i != end ; ++i){
//        _descriptors.erase( *i );
//    }
}


}

#undef GET_MODE
#undef FULL_ID
