
/**
* \file GameEngine.h
*/
#ifndef _FUSION_HPP_INCLUDED
#define _FUSION_HPP_INCLUDED

//#define namespace fus { namespace fus {
//#define } }




#define _IRRLICHT_SUPPORT





#include "logging/Logger.hpp"
#include <chrono>



#define _INFO    fus::Logger::Log(fus::NLogLevel::Notice)
//<< "[" << std::chrono::system_clock::now().time_since_epoch().count() << "]"
#define _LOG_WARNING fus::Logger::Log(fus::NLogLevel::Warning)
#define _LOG_ERROR   fus::Logger::Log(fus::NLogLevel::Error)
#define _LOG_DEBUG   fus::Logger::Log(fus::NLogLevel::Debug) << "In function [" << __FUNCTION__ << "] defined in [" << __FILE__ << ":" << __LINE__ << "]"

//<< "
//#define _INFO    fus::Logger::Log() << fus::NLogLevel::Notice
//#define _LOG_WARNING fus::Logger::Log(fus::NLogLevel::Warning)
//#define _LOG_ERROR   fus::Logger::Log(fus::NLogLevel::Error)
//#define _LOG_DEBUG   fus::Logger::Log(fus::NLogLevel::Debug) << "In function [" << __FUNCTION__ << "] defined in [" << __FILE__ << ":" << __LINE__ << "]"

#ifdef _IRRLICHT_SUPPORT

    #include <irrlicht.h>
    #include "logging/irrlicht_operators.hpp"
#endif



#ifndef M_PI
    #define M_PI 3.141592653589793238462643
#endif


#endif
