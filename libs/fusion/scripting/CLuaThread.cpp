#include "CLuaThread.hpp"
#include "CLuaVM.hpp"
//#include "../logging/ILogger.hpp"
#include <luabind/luabind.hpp>
#include <luabind/error.hpp>
#include <luabind/lua_include.hpp>

namespace fus {


//There is no explicit function to close or to destroy a thread. Threads are subject to garbage collection, like any Lua object.
CLuaThread::CLuaThread(lua_State* vm)
//: CLuaVM::_vm(0)
//:  ( thread )
{

    BOOST_ASSERT( vm );


    // TODO checker isthread()
    //isstate getVM()
    _vm = lua_newthread( vm );
}




//! Destructor
CLuaThread::~CLuaThread(){

    //_INFO << "Lua thread destroyed. Will be taken care of by Lua state";
}



bool
CLuaThread::isSuspended() const {
    return (status() == LUA_YIELD);
}



int
CLuaThread::status() const {


    //int lua_status (lua_State *L);
//Returns the status of the thread L.
//The status can be 0 for a normal thread, an error code if the thread finished its execution with an error, or LUA_YIELD if the thread is suspended.
    return lua_status( _vm );

}



// TODO retourner des booleens a la place
//The parameter nresults is the number of values from the stack that are passed as results to lua_resume.
/**
nbOfReturnedValues should be one or 0
**/
//int
int
CLuaThread::yield(const int& nbOfReturnedValues) {




//When a C function calls lua_yield in that way, the running coroutine suspends its execution,
//and the call to lua_resume that started this coroutine returns.
//The parameter nresults is the number of values from the stack that are passed as results to lua_resume.

    int ret = lua_yield( _vm, nbOfReturnedValues);

	return ret;
}



//lua_close(MainState);
int
CLuaThread::resume() {

//fus::CLuaVM::stackDump( _vm);
	//return luabind::detail::resume_impl( getVM() , 0, 0);

	return lua_resume( _vm , 0);
}


//void
//CLuaThread::pushErrorHandler(){
//    /*lua_gettop();
//lua_getglobal(L, "debug");
//lua_getfield(L, -1, "traceback");
//lua_remove(L, -2);*/
//}



bool
CLuaThread::execute(){

    int ret = resume();

    // script finished
    if(ret == 0){
//        _LOG_WARNING << "script finished !";
    }

    // LUA_YIELD = 1
    // Il y a une erreur !!
    else if( (ret != LUA_YIELD) ){
        setErrorDescription(ret);
        return false;
    }
    return true;

}



}
