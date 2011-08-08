/**
\file
\author
**/
#ifndef _FUSION_CORE_STRING_HPP_INCLUDED
#define _FUSION_CORE_STRING_HPP_INCLUDED

#include <utf8.h>
//#include <fusion/fusion.hpp>
#include <string>

namespace fus {



inline void
convertIntoNarrowString(const std::wstring& original, std::string& converted)
{
    //

    utf8::utf16to8(original.begin(),original.end(), std::back_inserter(converted) );
}


inline void
convertIntoWideString(const std::string& original, std::wstring& converted)
{
    utf8::utf8to16(original.begin(),original.end(), std::back_inserter(converted) );
}




}


#endif
