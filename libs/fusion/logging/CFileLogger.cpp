/**
* \file log_file.cpp
**/

#include <fusion/config.hpp>
#include "CFileLogger.hpp"
//#include <boost/date_time.hpp>
//namespace bgr = boost::gregorian;
//namespace bpx = boost::posix_time;


namespace fus {


/*
CFileLogger::CFileLogger(std::ofstream& stream){
    mStream = stream;
}
*/

//! Open file and write header with date/time
CFileLogger::CFileLogger(const std::string& filename )
{
    //ILoggerDecorator::ILoggerDecorator(logger);

    mStream.open(filename.c_str(),std::ios_base::out);
    if(!mStream){
        //throw SLoadingException(filename, "Impossible to get Write access");
    }

//
//
//    bpx::ptime now = bpx::second_clock::local_time();;
//    bgr::date today = now.date();// bgr::day_clock::local_day();
//startTime.time_of_day()

    mStream << _FUSION_SEPARATOR_ << std::endl
            //<< "Log created the :\t" << GetDate() << " at " << GetTime() << std::endl
            //<< "Log created the :\t" << now.date() << " at " << now << std::endl
            << _FUSION_SEPARATOR_ << std::endl;
}

/// Destructor
CFileLogger::~CFileLogger(){
    mStream << _FUSION_SEPARATOR_ << std::endl
            << "Log closed at :\t" << "TODO" << std::endl
            << _FUSION_SEPARATOR_ << std::endl << std::flush;
    mStream.close();
}


void
CFileLogger::NewMessage(const NLogLevel::EId& level){

//    ILoggerDecorator::NewMessage(level);
    //std::string finalMessage = "\n";
    //std::string finalMessage = "[" + std::string(CStringBuilder(ILogger::mTimer.elapsed())) + "]";
    std::string finalMessage = "\n";

    switch(level){

        case NLogLevel::Notice:
            finalMessage += "Notice: " ;
            break;

        case NLogLevel::Warning:
            finalMessage += "Warning:" ;
            break;

        case NLogLevel::Error:
            finalMessage += "ERROR:  " ;
            break;
        case NLogLevel::Debug:
            finalMessage += "Debug:  ";
            break;

        default:
            finalMessage = "invalid log level";
            break;
    }

    finalMessage += "\t";
    //Write(mTimer.elapsed());

    Write(finalMessage);
}


///
void
CFileLogger::Write(const std::string& msg){

    //ILoggerDecorator::Write(msg);
    //Assert(mStream.good());

    // To save straightaway the message ( otherwise could not be written into the file )
    mStream << msg << std::flush;
}

}
