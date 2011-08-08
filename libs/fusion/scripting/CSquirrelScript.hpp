#ifndef _FUSION_CSQUIRRELSCRIPT_HPP_INCLUDED
#define _FUSION_CSQUIRRELSCRIPT_HPP_INCLUDED

#include "IScriptInterpreter.hpp"

#include <squirrel.h>
#include <sqstdio.h>
#include <sqstdaux.h>
#include <string>

namespace fus {

class CSquirrelScript :
public IInterpreter
{


public:

    CSquirrelScript();
    ~CSquirrelScript();

    bool RunCommand(const std::string& param);
    bool RunFile(const std::string& param);

    void handleError();
//protected:
    // ma vm
    HSQUIRRELVM _vm;
};


}

#endif
