/**
* \file log.h
* \description cf http://loulou.developpez.com/tutoriels/moteur3d/partie1/#L2.1
http://kanze.james.neuf.fr/articles/fltrsbf1.html
* \todo faire deriver de stack_interface
*/
#ifndef _FUSION_ILogger_HPP_INCLUDED
#define _FUSION_ILogger_HPP_INCLUDED

#include <string>
#include <iostream>
#include <sstream>

#include <list>
#include <boost/shared_ptr.hpp>
//#include <boost/foreach.hpp>
#include <array>
#include <vector>


namespace fus {

////////////////////////////////////////////////////////////
/// Allow classification of logged messages according to
/// their importance ( from lowest to highest )
////////////////////////////////////////////////////////////

namespace NLogLevel {
enum EId {
Debug,
Notice,
Warning,
Error,
None,

Append         // for internal use
};

}

class ILogger
: public std::streambuf
{

public:
    //! Register a message : to overload
    virtual void Write(const std::string& msg) = 0;
    virtual void NewMessage(const NLogLevel::EId& level) = 0;

};


}

#endif
