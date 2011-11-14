#include "CBindCollection.hpp"
#include "IInputCache.hpp"

#define FULL_ID(id,no) std::make_pair(id,no)
#define DESCRIPTOR(it) it->second.Descriptor

//
//bool CBindCollection::processEvent(TTimeUnit const& currentTime, const SEvent& event)
//{
//    //!
//}


void
//CBindCollection::updateCache( TTimeUnit const& currentTime, CInputManager& inputMgr, TCache * cache) const
CBindCollection::updateCache( TTimeUnit const& currentTime, const CBindDescriptor& eventDescriptor,const bool& currentState)
{

    //BOOST_ASSERT(cache);

//    for( TDescriptorList::right_const_iterator i( _descriptors.right.begin()), end( _descriptors.right.end() ); i!= end; ++i){


    // getAssociatedIds
    for( TDescriptorList::iterator i( _descriptors.begin()), end( _descriptors.end() ); i!= end; ++i)
    {

        const TFullId& fullId = i->first;
        const CBindDescriptor& descriptor = i->second.Descriptor;
        SBindCache& cache = i->second.State;

        // if descriptors match
        if(eventDescriptor == descriptor){

            // Update cache
            cache.update( currentTime,descriptor,currentState);
        }

        //_states[ fullId ];
        /*
        ETapMode mode;

        //boost::optional<ETapMode> mode =
        bool ret = cache.update( currentTime,descriptor,currentState);
        if( ret )
        {

            if(!cache.State){
                mode = ETapMode::JustReleased;
            }
            else if(cache.QuickDelayRespected){
                mode = ETapMode::DoublePressed;
            }
            else {
                mode = ETapMode::JustPressed;
            }

            // Set state
            //setState(fullId.first, (mode == descriptor.Mode ) );

        }
        */
    }


}



/**
modify_data to replace

    bm_type::right_iterator it = bm.right.find("one");
    bool successful_replace = bm.right.replace_key( it, "1" );
**/
const CBindDescriptor&
CBindCollection::operator[](TFullId const& fullId) {


    // Throw if doesn't exist
    return _descriptors[fullId].Descriptor;
};




CBindDescriptor&
CBindCollection::setBind(TFullId const& fullId,CBindDescriptor const& descriptor){

    //auto fullId = FULL_ID(id,param);

    //std::pair< TDescriptorList::left_iterator, bool> result = _descriptors.left.insert( TDescriptorList::left_value_type(fullId,descriptor ) );
    std::pair< TDescriptorList::iterator, bool> result = _descriptors.insert( std::make_pair(fullId, SAssociatedStruct() ) );

    // if matching id already exist
//    if( result.second == false){
//
//        // overwrite current descriptor
//        result.first->second.Descriptor = descriptor;
//    }

    result.first->second.Descriptor = descriptor;

    // return bind
    return result.first->second.Descriptor;
}


std::vector< CBindCollection::TFullId >
CBindCollection::getAssociatedIds( const CBindDescriptor & descriptor, std::size_t const& limit) const {


    std::vector<TFullId>  ids;

    //for( TDescriptorList::right_const_iterator i( _descriptors.right.begin()), end( _descriptors.right.end() ); i!= end; ++i){
    for( TDescriptorList::const_iterator i( _descriptors.begin()), end( _descriptors.end() ); i!= end; ++i){


        if( descriptor == i->second.Descriptor)
        {

            ids.push_back(i->first);
            if( ids.size() >= limit){
                break;
            }
        }
    }

    return ids;
}


//CBindCollection::TOptionalFullId
bool
CBindCollection::containBind(CBindDescriptor const& descriptor,TFullId& id){

    //TOptionalFullId ret;
    std::vector<TFullId>  ids;
    ids = getAssociatedIds(descriptor,1);

    if( !ids.empty() )
    {
        id = ids.front();
        return true;
    }

    return false;
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




#undef GET_MODE
#undef FULL_ID
#undef DESCRIPTOR
