/**
* \file exceptions.cpp
**/
#include "exceptions.hpp"
#include "CStringBuilder.hpp"
#include <iostream>

namespace fus {

//! Define a basic exception
CException::CException(const std::string& message ) : mMessage(message) {

    // A supprimer plus tard ?
    #ifdef _FUSION_DEBUG
    ILogger::Log(EError) << message;
    #endif
}

//! Destructor
CException::~CException() throw() {
}

/// Overload std::what()
const char* CException::what() const throw(){
    return mMessage.c_str();
}


//! Exception throwed by an assert as defined in "exceptions.h"
SAssertException::SAssertException(const std::string& File, int Line, const std::string& Message)
: CException(TCharStringBuilder(Message)("\n\tFile:\t")(File)("\n\tLine:\t")(Line)){
}

//! If any loading failure
SLoadingException::SLoadingException(const std::string& File, const std::string& Message)
: CException(TCharStringBuilder("Error during loading of ")(File)(":\n\t")(Message)){
}


//! If conversion impossible
SBadConversion::SBadConversion(const std::string& Error) : CException(Error) {
}


SMathException::SMathException(const EMathError& error,const std::string& name)
: CException("erreur en lien avec mathematiques")
{

    switch (error){
    	case EDivisionPerZero:
    		break;

        case EOutOfMatrix:
            break;

    	default:
    		break;
    }

    //throw CException();

}


}
