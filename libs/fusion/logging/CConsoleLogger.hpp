/**
* \file log_file.h
*/
#ifndef _FUSION_CCONSOLELOGGER_HPP_INCLUDED
#define _FUSION_CCONSOLELOGGER_HPP_INCLUDED

//#include "exceptions.hpp"
//#include "ILoggerDecorator.hpp"
#include "ILogger.hpp"
#include <string>
//#include <locale>


namespace fus {

////////////////////////////////////////////////////////////
/// Allow switching between different loggers
///
/// \param Pointer to a certain instance derivated from ILogger
///
////////////////////////////////////////////////////////////
class CConsoleLogger
//: public ILoggerDecorator
: public ILogger
{

public://ILogger*
    CConsoleLogger();

//protected:
    void NewMessage(const NLogLevel::EId& level);
    void Write(const std::string& message);

};

}

#endif
