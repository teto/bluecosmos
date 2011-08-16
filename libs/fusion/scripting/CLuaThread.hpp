/**

DEPRECATED
To be replaced with a luaManager

**/
#ifndef _FUSION_CLUASCRIPT_HPP_INCLUDED
#define _FUSION_CLUASCRIPT_HPP_INCLUDED

#include "IScriptInterpreter.hpp"
#include "CLuaVM.hpp"

//#include <luabind/luabind.hpp>
#include <string>
#include <luabind/lua_include.hpp>

namespace fus {

//class CLuaVM;

// TODO renommer en CThreadedScript
// derive d'un mainScript CLuaState
class CLuaThread : public CLuaVM
{


public:
//CLuaVM& vm
    CLuaThread( lua_State *);
   // CLuaThread( CLuaVM& vm) : CLuaThread(vm.getVM() ) { };
    ~CLuaThread();


    bool isSuspended() const;
    int status() const;
    int yield(const int& );
    int resume();
    bool execute();

protected:

    //lua_State *_thread;
};


}

#endif
