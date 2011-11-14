/*! \file main.cpp
 *   \brief Here is the main loop of the game
 *
 *   The engine is first instanced in this file and then all methods
 *   are called successively inside the while() structure
*/
#include "IEngineConfig.hpp"
#include "game_engine.hpp"
#include "def.hpp"
#include "config.hpp"
#include "states/CTransitionState.hpp"
#include "states/CMenuState.hpp"
#include "fightingState/CSinglePlayerState.hpp"
#include "entities/IMultiModeTransformer.hpp"
#include <fusion/logging/CConsoleLogger.hpp>
#include <fusion/logging/CFileLogger.hpp>
//#include <boost/detail/lightweight_test.hpp>
#include <boost/smart_ptr.hpp>
//#include "events/CInputManager.hpp"



//! The main function
int
main (int argc, char *argv[]){

    //! Begins logging every event to help debugging the game ( yes there are bugs ! )
    // On doit pouvoir passer des streams
    #ifndef _DEBUG
    fus::Logger::addLogger(new fus::CConsoleLogger());
    #endif

    fus::Logger::addLogger(new fus::CFileLogger("log.txt"));

    //  typedef void (*terminate_handler) ();
//    terminate_handler error_handler;
//    std::set_terminate( error_handler );
    //std::set_unexpected

    fus::Logger::reportingLevel() = fus::NLogLevel::Notice;
    //! Instanciation of the game engine

    // TODO appels des fct statique

    initializeKeycodes();
    initializeDeviceCodes();
    //CEventManager::initStaticMembers();

    // If more than one param than next param is filename of config to load
    if(argc > 1){

    }

//    try {
    CGameEngine& game( CGameEngine::instance() );
//    }
//    catch(...){
//        _LOG_ERROR << "test";
//    }
    IMultiModeTransformer::initialize();


//    const char* filename = "config.lua";
    const char* configFilename = conf::CONFIG_FILENAME;

    // TODO nom du fichier = 1er param de la ligne de commande normalement argv[1]
    try {

        _INFO << "Loading config file [" << game.EngineConfig.DriverType << "]";
        loadEngineConfigFromLua( configFilename , game.EngineConfig, game.GameConfig, game.AudioConfig );
    }
    catch(...) {
        _LOG_ERROR << "Could not load config [" << configFilename << "]";

        try {
            saveConfigIntoLuaFile( configFilename , game.EngineConfig, game.GameConfig, game.AudioConfig );
        }
        catch(...) {
//        if( !saveConfigIntoLuaFile("config.lua", game.EngineConfig, game.GameConfig, game.AudioConfig )) {
//            _LOG_ERROR << "Could not save config";
//        }
            _LOG_ERROR << "Could not save config";

        }
    }




//    if( !game.InitEngineFromLua(config) ){
//        //ILogger::Log()
//        _LOG_ERROR << "Impossible to initialize engine !";
//        return 1;
//    }
//

    game.pushEvent(NStateEvent::PushState,NStateId::MainMenu);
    //game.pushEvent(NStateEvent::PushState,NStateId::Solo);

    //game.synchronize();
    //"config.lua", loadConfig
    //std::bind( loadConfigFromLua std::placeholders_1)["config.lua"]
    return game.Run(   );

//    if( !game.Run("config.lua", loadConfig ) ){
//
//        _LOG_ERROR << "Exception or error thrown :(";
//        //return EXIT_FAILURE;
//    }


    //game.CleanUp();                //!< Cleans the engine

    // boost::report_LOG_ERRORs();
	//return 0;


//_INFO << "Count of param" << state.use_count();
   // return EXIT_SUCCESS;            //!< EXIT_SUCCESS = 0
};
