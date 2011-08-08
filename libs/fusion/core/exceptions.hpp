/**
* \file exceptions.h
**/
#ifndef _FUSION_EXCEPTIONS_HPP_INCLUDED
#define _FUSION_EXCEPTIONS_HPP_INCLUDED

#include <fusion/fusion.hpp>
#include <string>

namespace fus {

////////////////////////////////////////////////////////////
/// \class CException Basic class dealing with exceptions
////////////////////////////////////////////////////////////
class CException : public std::exception
{

public:
    CException(const std::string& message);     //!< Constructor
    /// Destructor ( throw() shows destructor won't throw any exception )
    virtual ~CException() throw();
    /// Return message associated to this exception
    virtual const char* what() const throw();

protected :
    std::string mMessage;       //!< Message associé à l'exception

};





/// If condition not checked
struct SAssertException : public CException{
    SAssertException(const std::string& file, int line, const std::string& message);
};

/// permet de remplacer par rien du tt les assert
#if _FUSION_DEBUG
    #define Assert(condition) do { if (!(condition)) \
        throw fus::SAssertException(__FILE__, __LINE__, "Condition not checked:\t" #condition); \
        } while(0);
#else
    inline void DoNothing(bool) {};
    #define Assert(condition) DoNothing(!(condition))
#endif


/// If loading ( of a resource for example ) s'est mal déroulé
struct SLoadingException : public CException {
    SLoadingException(const std::string& File, const std::string& Message);
};




////////////////////////////////////////////////////////////
/// \struct SBadConversion
/// If not able to cast a type or convert something
////////////////////////////////////////////////////////////
struct SBadConversion : public CException {
    SBadConversion(const std::string& Error);
};


////////////////////////////////////////////////////////////
/// \enum EMathError
////////////////////////////////////////////////////////////
enum EMathError {
EDivisionPerZero = 0,
EOutOfRange,
EOutOfMatrix
};

////////////////////////////////////////////////////////////
/// \class CException Basic class dealing with exceptions
////////////////////////////////////////////////////////////
struct SMathException : public CException {
    SMathException(const EMathError& error,const std::string& name);
};

}


#endif
