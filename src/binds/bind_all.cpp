
// definit ici et binde les fct lua necessaires
#include "binds.hpp"
#include <luabind/luabind.hpp>

// Include needed policy
#include <luabind/copy_policy.hpp>
//#include <luabind/dependency_policy.hpp>
#include <luabind/out_value_policy.hpp>
#include <luabind/raw_policy.hpp>
#include <luabind/return_reference_to_policy.hpp>
#include <luabind/discard_result_policy.hpp>
#include <luabind/error.hpp>

#include "../game_engine.hpp"


using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace luabind;



bool
CGameEngine::bindEverythingToLua()
{

    // TODO remove that, on peut normalement rester la VM
    //static bool _luaAlreadyBinded = false;

    //if(_luaAlreadyBinded)
    //    return true;
    TScriptingVM& vm    = getScriptingVM();
    vm.reset();

    // TODO
    //faire un Reset de la VM ici avec un warning !



    // Ceci ne catch malehureusement pas l'assert
    try {

        // TODO rename with generate scope
        vm.bind( bindLevelHandlerToLua() );
        vm.bind( bindConfigStructToLua() );
        vm.bind( bindEngineToLua() );
        vm.bind( bindPlayerToLua() );
        vm.bind( bindFleets() );
        vm.bind( bindSound() );

//        lua_register(MainState, "print", LuaPrint );

    }
    //
    catch(luabind::error& e){
        _LOG_ERROR << "Luabind error in file [" << __FILE__ << "]" << e.what();
        return false;
    }
    catch(std::runtime_error& e){
        _LOG_ERROR << "Runtime error" << e.what();
        return false;
    }
    catch(...){
        _LOG_ERROR << "Unknown exception in file [" << __FILE__ << "]";
        return false;
    }

    return true;
}




