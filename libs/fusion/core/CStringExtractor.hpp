/**
* \file string.h
* \brief Some useful functions dealing with strings
*/
#ifndef _FUSION_CSTRINGEXTRACTOR_HPP_INCLUDED
#define _FUSION_CSTRINGEXTRACTOR_HPP_INCLUDED


//#include <algorithm>
#include <sstream>
//#include <cctype>
#include <iostream>
#include <string>
#include <fusion/fusion.hpp>

namespace fus {



/*************
* \brief Convert a string into another type T
**************/

template<typename CharType>
class CStringExtractor
{

public :
////////////////////////////////////////////////////////////
/// Allow switching between different loggers
///
/// \param Pointer to a certain instance derivated from ILogger
///
////////////////////////////////////////////////////////////
    /// Build the extractor from text
    CStringExtractor(const CharType* Text);

    /// Attempt extracting a value of T type
    template<typename T> CStringExtractor& operator ()(T& Value);
    //CStringExtractor& CStringExtractor::operator ()(const std::string& Value);



    std::basic_string<CharType>
    Flush() const {
        return( mStream.str());
    }

    void ThrowIfEOF();

    /// Set a new mStream
    void Set(const std::string& stream) {
        mStream.clear();
        mStream.str(stream);
    }

private :
    std::basic_istringstream<CharType> mStream;
};


/**********************************************
*************** CStringExtractor **************
***********************************************/


// Construit l'extracteur à partir d'une chaîne
template<typename CharType>
CStringExtractor<CharType>::CStringExtractor(const CharType* Text) :
mStream(Text)
{

}

//fonction nouvellement ajoute,verifier qu'ellene fait pas de pb
/*inline CStringExtractor& CStringExtractor::operator ()(const std::string& Value){
    mStream.str(Value);
    return *this;
}*/

// Extrait une valeur de type T
template <typename CharType>
template <typename T>
inline CStringExtractor<CharType>&
CStringExtractor<CharType>::operator ()(T& Value){
    if (!(mStream >> Value)){
        if (mStream.eof()){
            std::cout << "chaine vide" << std::endl;
            //throw SBadConversion(CStringBuilder("Attempt to extract \"")(typeid(T).name())("\"from an empty string"));
        }
        else {
            std::cout << "conversion foireuse" << std::endl;
            //throw SBadConversion(CStringBuilder("Conversion from \"string\" to \"")(typeid(T).name())("\" seems impossible"));
        }
    }

    return *this;
}



// Vérifie qu'il n'y a plus rien à extraire
template<typename CharType>
inline void
CStringExtractor<CharType>::ThrowIfEOF(){
    std::string Left;
    if (std::getline(mStream, Left))
        std::cout << "string too long";
        //throw CBadConversion("String too long, \"" + Left + "\" wasn't extracted");
}



typedef CStringExtractor<wchar_t> TWStringExtractor;
typedef CStringExtractor<char> TStringExtractor;


}

#endif
