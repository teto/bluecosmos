#ifndef _FUSION_ILOGGERDECORATOR_HPP_INCLUDED
#define _FUSION_ILOGGERDECORATOR_HPP_INCLUDED

#include "ILogger.hpp"

FUSION_NAMESPACE_BEGIN

// faire deriver CConsoleLogger de celui-ci
class ILoggerDecorator : public ILogger {

public:
    ILoggerDecorator(ILogger* logger) {
        _logger = logger;
    };

//protected:
    virtual void Write(const std::string& msg) {
        if(_logger)
        _logger->Write(msg);
    }

    virtual void NewMessage(const NLogLevel::EId& level) {
        if(_logger)
        _logger->NewMessage(level);
    };

private:
    ILogger* _logger;


};

FUSION_NAMESPACE_END

#endif
