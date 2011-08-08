/**
* \file log_file.h
*/
#ifndef _FUSION_CFILELOGGER_HPP_INCLUDED
#define _FUSION_CFILELOGGER_HPP_INCLUDED

//#include "exceptions.hpp"
#include "ILogger.hpp"
#include <string>
#include <fstream>


namespace fus {

////////////////////////////////////////////////////////////
/// Allow switching between different loggers
///
/// \param Pointer to a certain instance derivated from ILogger
///
////////////////////////////////////////////////////////////
class CFileLogger
: public ILogger
{

public:
    CFileLogger(const std::string& filename);
    //CFileLogger(std::ofstream& stream);
    ~CFileLogger();



    void NewMessage(const NLogLevel::EId& level);
    void Write(const std::string& msg);

protected:
    std::ofstream mStream;
};

}

#endif
