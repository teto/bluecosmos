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
{
protected:

    CBindDescriptor Descriptor;
    SBindCache _cachedState;
    TTimeUnit _timeOfProcessingEnd;  //!< time at which we should stop the processing if descriptor
                                    //!< not fully qualified until then


    //TTimeUnit
    // state/respectQuickDelay
    std::stack< std::pair <bool,bool> > _pastStates;

public:
    CBindFromEventGenerator ();

    //typedef boost::optional<CBindDescriptor> TReturnValue;
    //bool handleEvent(irr::SEvent const&);
    //bool processEvent( TTimeUnit const&,irr::SEvent const&);
    //, CBindDescriptor& result
    bool processEvent( TTimeUnit const& time, irr::SEvent const& e);

    /**
    \param[out] Computed bind
    \param[out] State, true if button down, false if up
    \return True if could generate a descriptor
    **/
    static bool generateDescriptor(irr::SEvent const& e,CBindDescriptor& bind, bool& state);

    bool baseliningBind () const {
        //return ( (_timeOfProcessingEnd != 0) );
        return !Descriptor.undefined();
    };

    /**
    \param[in] time
    \param[out] Generated bind
    \return True if full bind generated
    **/
    bool check(TTimeUnit const&,CBindDescriptor& result) ;

};




#endif
