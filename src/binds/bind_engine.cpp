#include "binds.hpp"
// definit ici et binde les fct lua necessaires
#include <luabind/luabind.hpp>

// Include needed policy
#include <luabind/copy_policy.hpp>
//#include <luabind/dependency_policy.hpp>
#include <luabind/out_value_policy.hpp>
#include <luabind/raw_policy.hpp>
#include <luabind/return_reference_to_policy.hpp>
#include <luabind/yield_policy.hpp>
#include <luabind/error.hpp>
#include <luabind/discard_result_policy.hpp>
#include "../fightingState/CSinglePlayerState.hpp"
//#include "entities/player.hpp"
#include "../IGameEngine.hpp"
#include "../game_engine.hpp"
//#include "../fightingState/CDialogState.hpp"
#include "../CSpeaker.hpp"
#include "../CSpeech.hpp"
#include <fusion/logging/Logger.hpp>
#include <fusion/scripting/Lua_utils.hpp>


using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace luabind;



typedef void (*TCLoggingFunction)(const fus::NLogLevel::EId&,const char*);




//CSinglePlayerState
//CGraphicalLevel* levelMgr
luabind::scope
bindEngineToLua()
{

// Export our class with LuaBind/mLuaState

    return luabind::class_<fus::ILogger>("Logger")
        .enum_("LogLevel")
        [
            value("Debug",fus::NLogLevel::Debug),
            value("Notice",fus::NLogLevel::Notice),
            value("Warning",fus::NLogLevel::Warning),
            value("Error",fus::NLogLevel::Error)

        ]
        .scope [
            //def("reportingLevel",&fus::Logger::reportingLevel),
            //def("Log", (void (fus::Logger:*)(const fus::NLogLevel::EId&,const char*)) &fus::Logger::Log)

            def("Log", (TCLoggingFunction)&fus::Logger::Log)
        ],

    luabind::class_<vector3df>("vector3df"),
    //luabind::def("print", &fus::luaPrint),
//(TCLoggingFunction) &fus::Logger::Log

// TODO les passer en sharedPointer





// REmplacer ici par un ISoundManager


    luabind::class_<CSinglePlayerState>("CSinglePlayerState")
        //.def("addActor", &CGraphicalLevel::update)
            .def("showMessage",&CSinglePlayerState::showMessage, luabind::discard_result)
            .def("getUserReply",&CSinglePlayerState::getUserReply)
            .def("loadLevel",&CSinglePlayerState::loadLevel)
            .def("isPlayerUpdatable",&CSinglePlayerState::isPlayerUpdatable)
            .def("getUpperProgression",&CSinglePlayerState::getUpperProgression)
            .def("loadActor",&CSinglePlayerState::createActor)
            .def("update",&CSinglePlayerState::Update)
            .scope[
            def("createSpeech",&CSinglePlayerState::createSpeech)
            //,
            //def("createSpeech",(CSpeech* (*)(const std::string&))&CGraphicalLevel::createSpeech)
        ]
        ,

//
    luabind::class_<IGameEngine>("IEngine")
        .def("getElapsedTime",&IGameEngine::getElapsedTime)
        ,

    luabind::class_<CGameEngine,IGameEngine>("Engine")

        //.def("startDialog",&CGameEngine::startDialog)
        .def("setCamPos",&CGameEngine::setCamPos)
        .def("setCamTarget",&CGameEngine::setCamTarget)

   ;

}
