/**
* \file log_file.cpp
**/
#include "CConsoleLogger.hpp"
#include <iostream>

namespace fus {

//CConsoleLogger::CConsoleLogger(ILogger* logger) : ILoggerDecorator(logger) {
CConsoleLogger::CConsoleLogger()
{

    //ILoggerDecorator::ILoggerDecorator(logger);
/*
    locale mylocale("");      // Construct locale object with the user's default preferences
    std::cout.imbue( mylocale );   // Imbue that locale
    */
}


void
CConsoleLogger::NewMessage(const NLogLevel::EId& level){
    //ILoggerDecorator::NewMessage(level);

    std::string msg = "\r\n";
    switch(level){
        case NLogLevel::Notice:
            msg += "Notice: " ;
            break;
        case NLogLevel::Warning:
            msg += "Warning:" ;
            break;
        case NLogLevel::Error:
            msg += "ERROR:  ";
            break;
        case NLogLevel::Debug:
            msg += "DEBUG:  ";
            break;
        default:
            msg += "Invalid log level";
            break;

    };
    msg += "\t";

    Write(msg);
}

///
void
CConsoleLogger::Write(const std::string& msg){
    //ILoggerDecorator::Write(msg);
    std::cout << msg << std::flush;
};


}
