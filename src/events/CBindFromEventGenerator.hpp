/**
\file
*/
#ifndef _BC_CBINDFROMEVENT_HPP_INCLUDED
#define _BC_CBINDFROMEVENT_HPP_INCLUDED


#include <irrlicht.h>  //
#include <boost/optional.hpp>  // header only
//#include <fusion/core/CStringBuilder.hpp>
#include "SCachedState.hpp"

// Forward reference
class CBindDescriptor;
class CInputManager;

class CBindFromEventGenerator
//:
//    public irr::IEventReciever
{
protected:
    //boost::optional<
    // std::pair<>
    CBindDescriptor _tempDescriptor;
    SCachedState _cachedState;
    irr::u32 _timeOfDescriptorRetrieval;
    CInputManager& _inputMgr;


public:
    CBindFromEventGenerator (CInputManager&);

    //typedef boost::optional<CBindDescriptor> TReturnValue;
    //bool handleEvent(irr::SEvent const&);
    bool processEvent( irr::u32 const&,irr::SEvent const&);
    bool processingBind () const { return (_timeOfDescriptorRetrieval != 0);};
    boost::optional<CBindDescriptor> check(irr::u32 const&) ;

};


#endif
