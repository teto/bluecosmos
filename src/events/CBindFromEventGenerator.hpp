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
    SBindCache _cachedState;
    irr::u32 _timeOfProcessingEnd;  //!< time at which we should stop the processing if descriptor
                                    //!< not fully qualified until then
    CInputManager& _inputMgr;
    //
    std::stack<SCachedState> _pastStates;

public:
    CBindFromEventGenerator (CInputManager&);

    //typedef boost::optional<CBindDescriptor> TReturnValue;
    //bool handleEvent(irr::SEvent const&);
    bool processEvent( irr::u32 const&,irr::SEvent const&);
    bool processingBind () const { return (_timeOfDescriptorRetrieval != 0);};
    boost::optional<CBindDescriptor> check(irr::u32 const&) ;

};


#endif
