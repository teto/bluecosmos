#ifndef _FUSION_LOGGER_HPP_INCLUDED
#define _FUSION_LOGGER_HPP_INCLUDED

#include "ILogger.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>
#include <array>
#include <vector>
#include <stack>
#include <deque>
#include "../core/string.hpp"





//#define _CONTAINER_DECL(containerName) template <class T> Logger& operator <<(const containerName<T>& msg)
#define _CONTAINER_IMPL(containerName) template<class T> Logger& \
                                        operator <<(Logger& logger,const containerName<T>& msg){    \
                                            typedef typename containerName<T>::const_iterator TConstIterator; \
                                            for(TConstIterator i(msg.begin()),end(msg.end()); \
                                                i != end; ++i)\
                                            {    \
                                                logger << *i; \
                                            }   \
                                            return logger; \
                                        }


namespace fus {


typedef boost::shared_ptr<ILogger> TSharedLoggerPtr;


////////////////////////////////////////////////////////////
/// Contain many static functions allowing to load various
/// loggers ( one could write into an xml file whereas an
/// other might just display messages on screen
////////////////////////////////////////////////////////////



class Logger
//: public std::streambuf
{

public:
    //Logger();
    virtual ~Logger();

    ////////////////////////////////////////////////////////////
    /// Allow switching between different loggers
    ///
    /// \param Pointer to a certain instance derivated from Logger
    ////////////////////////////////////////////////////////////
    static void addLogger(ILogger* Logger);
    //static void addLogger(Logger* Logger);


    ////////////////////////////////////////////////////////////
    /// Log a message (C++ way)
    ///
    /// @param Importance of the new message
    ////////////////////////////////////////////////////////////
    static Logger& Log(const NLogLevel::EId& level = NLogLevel::Notice);
    static void Log(const NLogLevel::EId& level,const char*);

    static NLogLevel::EId& reportingLevel();

    static Logger& instance() { return _instance;}

    template <class T> Logger& operator <<(const T& msg);
    template <const wchar_t*> Logger& operator <<( const wchar_t* msg);

protected:
    /// Define above which levels of message is worth registering
    static NLogLevel::EId _reportingLevel;



    // std::stack
    typedef std::vector< TSharedLoggerPtr > TLoggersMap;
    static TLoggersMap _loggers;
    static bool _logging;

//Logger(const Logger&);
private:

    Logger& operator=(const Logger&);

    static Logger _instance;
};

/*
template<typename T, typename... ARGS>
//template <class T,class ...args>
Logger&
Logger::operator <<(const T& msg){
    BOOST_ASSERT( _loggers.size() > 0);

    if(!_logging){
        return *this;
    }


    std::string result;
    std::ostringstream stream;
    stream.exceptions ( std::ostringstream::eofbit | std::ostringstream::failbit | std::ostringstream::badbit );

    try {
        stream << msg;
        result = stream.str();
    }
    //ios::exception
    catch(std::ios::failure& e){
        result = "Logger: Exception thrown while converting !" ;
        //std::cout << "exception" << std::endl;
    }
    catch(...){
        result = "Logger: unknown Exception !" ;
        //std::cout << "exception" << std::endl;
    }

    // Send message to each registered logger
    //BOOST_FOREACH(TSharedLoggerPtr& logger,_loggers){
    for(TLoggersMap::iterator i( _loggers.begin() ), end(_loggers.end());
        i != end;
        ++i)
    {
        //logger->Write( result );
        (*i)->Write( result );
    }

    return Log(NLogLevel::Append);
}*/


template <const wchar_t* >
Logger&
Logger::operator << ( const wchar_t* msg) {

    std::string result;
    convertIntoNarrowString(msg, result);
    return (*this) << ( result );
}



// Surcharge de l'opérateur << pour logger des messages
template <class T>
Logger&
Logger::operator <<(const T& msg){

    BOOST_ASSERT( _loggers.size() > 0);

    if(!_logging){
        return *this;
    }


    std::string result;
    std::ostringstream stream;
    stream.exceptions ( std::ostringstream::eofbit | std::ostringstream::failbit | std::ostringstream::badbit );

    try {
        stream << msg;
        result = stream.str();
    }
    //ios::exception
    catch(std::ios::failure& e){
        result = "Logger: Exception thrown while converting !" ;
        //std::cout << "exception" << std::endl;
    }
    catch(...){
        result = "Logger: unknown Exception !" ;
        //std::cout << "exception" << std::endl;
    }

    // Send message to each registered logger
    //BOOST_FOREACH(TSharedLoggerPtr& logger,_loggers){
    for(TLoggersMap::iterator i( _loggers.begin() ), end(_loggers.end());
        i != end;
        ++i)
    {
        //logger->Write( result );
        (*i)->Write( result );
    }

    return Log(NLogLevel::Append);
}



    template<class T1,class T2> Logger&
    operator <<(Logger& logger,const std::pair<T1,T2>& msg){

        logger << "std::pair value<" << msg.first << "," << msg.second << ">";
        return logger;
    }

    _CONTAINER_IMPL(std::vector);
    _CONTAINER_IMPL(std::list);
    //_CONTAINER_IMPL(std::stack);
    _CONTAINER_IMPL(std::deque);
    //_CONTAINER_IMPL(array);


    #undef _CONTAINER_IMPL
}

#endif
