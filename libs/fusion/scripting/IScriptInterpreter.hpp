#ifndef _FUSION_ISCRIPTINTERPRETER_HPP_INCLUDED
#define _FUSION_ISCRIPTINTERPRETER_HPP_INCLUDED

#include <fusion/fusion.hpp>
#include <string>

namespace fus {



class IInterpreter
{


public:
    //CScript() {};
    virtual ~IInterpreter() {};
    virtual bool RunCommand(const char* param) = 0;
    //virtual bool RunFile(const std::string& param) = 0;

protected:

};



}


#endif
