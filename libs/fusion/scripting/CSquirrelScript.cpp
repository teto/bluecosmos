//#include "config.hpp"
#include "CSquirrelScript.hpp"
#include "../logging/ILogger.hpp"
#include "../core/CStringBuilder.hpp"
#include <luabind/luabind.hpp>

namespace fus {

CSquirrelScript::CSquirrelScript(){

//sq_seterrorhandler
    _vm = sq_open(1024); //creates a VM with initial stack size 1024

	// initialize Lua
//	if(!state){
//
//	    mLuaState = lua_open();
//
//        // load Lua base libraries
//        luaL_openlibs(mLuaState);
//	}
//	else {
//	    mLuaState = state;
//	}
//
//    // Connect LuaBind to this lua state
//    luabind::open(mLuaState);

}

CSquirrelScript::~CSquirrelScript(){

    //luabind::close()
    sq_close(_vm);
    ILogger::Log(ENotice) << "Contexte lua supprime";
}

bool
CSquirrelScript::RunCommand(const std::string& param){
    // CONVERTIR en const char*
	// run the script
//
//
//    if (luaL_dostring(mLuaState,param.c_str()) != 0){
//        // il y a eu une erreur dans le script
//        handleError();
//        return false;
//    }

    return true;

}

void
CSquirrelScript::handleError(){
//
//
//    lua_Debug d;
//    fus::TCharStringBuilder msg("CSquirrelScript.cpp:\t");
//    // 2nd parameter is the level of function 0 => current function
//    // n+1 level calls level nfunction
//    lua_getstack(mLuaState, 1, &d);
//    //Returns information about a specific function or function invocation
//    // must be called with a valid lua_Debug, 's','l','n' fills certain fields of lua_Debug
//    // Returns 0 on error
////    if(lua_getinfo(mLuaState, "Sln", &d) == 0){
////        msg("Couldn't retrieve info\n");
////    }
//
////a "printable" version of source d.short_src
//
//    msg("File involved:\t")(d.source)
//        ("\nCurrent line:\t")(d.currentline )
//        ("\nDescription:\t")(lua_tostring(mLuaState, -1))("\n");
//
//    // name is a reasonable name for a function
//    // namewhat a more descriptible
//    if (d.name != 0){
//
//        msg("(")( d.namewhat )( " " )(d.name)(")");
//    }
//    else {
////        msg("")
//    }
//
//    //lua_pushstring(mLuaState, msg.str().c_str());
//    ILogger::Log(EError) << msg.str();//lua_tostring(mLuaState,-1);
}

bool
CSquirrelScript::RunFile(const std::string& param){

	// Utiliser un try/Catch

//    try {
//        // run the script
//        if (luaL_dofile(mLuaState,param.c_str()) != 0){
//            // il y a eu une erreur dans le script
//            handleError();
//            return false;
//        }
//    }
//    catch(luabind::error& e){
//
//        handleError();
//        return false;
//    }
//    return true;
    return false;
}


}
