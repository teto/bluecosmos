/**
* \file log.cpp
* \brief
*/

#include "Logger.hpp"


namespace fus {

////////////////////////////////////////////////////////////
/// Static members
////////////////////////////////////////////////////////////

Logger::TLoggersMap Logger::_loggers;

Logger Logger::_instance;


//Logger* Logger::mInstance = 0;
//std::stack<Logger*> Logger::mInstances;


NLogLevel::EId Logger::_reportingLevel = NLogLevel::Notice;
bool Logger::_logging = false;


// Si pas de debug,on affiche pas les ENotice
//#ifdef _NDEBUG
//ELogLevel Logger::_reportingLevel = NLogLevel::Notice;
//#endif


//ELogLevel Logger::mMessageLevel = ENotice;
//bool Logger::mNewMessage = false;
//const NLogLevel::EId& level
NLogLevel::EId&
Logger::reportingLevel() {
    return _reportingLevel;
}

//! Destructor
Logger::~Logger(){
    //destroy();
}


//! Constructor
void
Logger::addLogger(ILogger* logger){

    BOOST_ASSERT(logger != 0);


    TSharedLoggerPtr sharedLogger( logger );
    _loggers.push_back( sharedLogger );

}




//! Handles with messages ( C++ way )
// static
Logger&
Logger::Log(const NLogLevel::EId& level){

    //BOOST_ASSERT( _loggers.size() > 0 );

    // If it 's a new message
    if( (level != NLogLevel::Append) ){

        // if level > minimum level
        if(level >= _reportingLevel){

            _logging = true;

            // Send a new message signal to level
            BOOST_FOREACH( TSharedLoggerPtr& logger, _loggers){

                logger->NewMessage(level);
            }
        }
        else {
            _logging = false;
        }
    }

    //
    //return (*_loggers.front());
    //Logger
    //return *this;
    return instance();

}



void
Logger::Log(const NLogLevel::EId& level,const char* msg) {
    Log(level) << level << msg;
}


}
