/**
\file
*/
#ifndef _BC_CBINDFROMEVENT_HPP_INCLUDED
#define _BC_CBINDFROMEVENT_HPP_INCLUDED


#include <irrlicht.h>  //
#include <boost/optional.hpp>  // header only
//#include <fusion/core/CStringBuilder.hpp>
#include "SCachedState.hpp"


namespace input {



// Forward reference
class CBindDescriptor;
class CInputManager;

class CBindFromEventGenerator
{
protected:
    // std::pair<>
    CBindDescriptor _tempDescriptor;
    SBindCache _cachedState;
    TTimeUnit _timeOfProcessingEnd;  //!< time at which we should stop the processing if descriptor
                                    //!< not fully qualified until then
    CInputManager& _inputMgr;

    //TTimeUnit
    // state/respectQuickDelay
    std::stack< std::pair <bool,bool> > _pastStates;

public:
    CBindFromEventGenerator (CInputManager&);

    //typedef boost::optional<CBindDescriptor> TReturnValue;
    //bool handleEvent(irr::SEvent const&);
    bool processEvent( TTimeUnit const&,irr::SEvent const&);
    bool processingBind () const { return ( _timeOfProcessingEnd != 0);};
    boost::optional<CBindDescriptor> check(TTimeUnit const&) ;

};

}


#endif
