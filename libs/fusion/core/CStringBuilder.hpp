/**
* \file string.h
* \brief Some useful functions dealing with strings
*/
#ifndef _FUSION_CSTRINGBUILDER_HPP_INCLUDED
#define _FUSION_CSTRINGBUILDER_HPP_INCLUDED

#include <fusion/fusion.hpp>
#include <iostream>
#include <sstream>

namespace fus {

/***********
* Converts and add a value of type T into a std::string
**********/
template<typename CharType = char>
class CStringBuilder
{

public :

////////////////////////////////////////////////////////////
/// Allow switching between different loggers
///
/// \param Pointer to a certain instance derivated from ILogger
///
////////////////////////////////////////////////////////////
    CStringBuilder();

    ///// Construit l'injecteur avec une première valeur
    template <typename T> CStringBuilder(const T& Value){
        mStream << Value;
    }

    /// Create string from any type
    //!< Operator overload
    /// Register each type into the member stream
    /// Returning *this allows to chain conversions
    template <typename T>
    CStringBuilder&
    operator ()(const T& Value){
// TODO bug
        mStream << Value;
        return *this;
    }
    //!< Operator that converts into string
    operator std::basic_string<CharType>(){
        return mStream.str();
    }

    //
    const std::basic_string<CharType>
    //CharType*
    str(){
        return mStream.str();//
    }
    //operator std::wstring();     //!< Operator that converts into string

private:
    std::basic_ostringstream<CharType> mStream;     //!< Contain every converted type
};




// Opérateur de conversion implicite en string
//inline CStringBuilder::operator std::string()

typedef CStringBuilder<char> TCharStringBuilder;
typedef CStringBuilder<wchar_t> TWCharStringBuilder;

}

#endif
