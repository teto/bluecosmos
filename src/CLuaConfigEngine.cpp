#include "IEngineConfig.hpp"
#include "binds/binds.hpp"
#include "audio/SAudioParameters.hpp"
#include "startup_config.hpp"
#include <fusion/scripting/CLuaVM.hpp>
#include <iostream>
#include <fstream>

void
loadEngineConfigFromLua(const char* filename, irr::SIrrlichtCreationParameters& engineParam,SIngameConfig& ingameConf,audio::SAudioParameters& audioParam){

    fus::CLuaVM script;

    script.bind ( bindConfigStructToLua() );
    //script.setSpecialNewIndex("whatever");

    luabind::object globals;
    script.getGlobals(globals);
    globals["AudioConfig"]      = &audioParam;
    globals["EngineConfig"]     = &engineParam;
    globals["GameConfig"]       = &ingameConf;
//boost::ref(
    if(!script.RunFile(filename)){
        //boost::throw_exception()
        throw std::runtime_error( script.getErrorDescription() );
    }
}


void
saveConfigIntoLuaFile(const char* filename, const irr::SIrrlichtCreationParameters& EngineConfig,const SIngameConfig& GameConfig,const audio::SAudioParameters& audioParam){

    //throw std::runtime_error("Save function not implemented");
    std::wofstream file( filename , std::ios_base::trunc );

    if(!file.good()){
        throw std::runtime_error("Could not open file to save configuration");
    }

    // Engine Config
    file << L"EngineConfig.DriverType =" << EngineConfig.DriverType << std::endl;
    file << L"EngineConfig.DriverType =" << EngineConfig.DriverType << std::endl;

    // Game Config
    file << L"GameConfig.EnableBloomShader =" << std::boolalpha << GameConfig.EnableBloomShader << std::endl;
    file << L"GameConfig.EnableDialogs =" << std::boolalpha << GameConfig.EnableDialogs << std::endl;
    file << L"GameConfig.EnableMotionBlurShader =" << std::boolalpha << GameConfig.EnableMotionBlurShader << std::endl;

    file << std::flush;

/*
    fus::TWCharStringBuilder text(L"<config>\n<player>\n");

    std::wstring temp;

    text(temp);
    // enregistre le mapping du joueur
    for(int i = 0; i < NPlayerInput::Count;++i){

        const CBindEntry& map = _mappingSet->getMapping(i) ;
        map.toXmlString(text);
        text("\n");
    }

    text("</player>\n");

// TODO construire window settings
    //text(windowSettingstoXmlString());
    text("<window ")
    ("fullscreen=\"")(_fullscreen)("\" ")
    ("vsync=\"")(_vsync)("\" ")
    ("width=\"")(_width)("\" ")
    ("height=\"")(_height)("\" ")
    ("antialiasing=\"")(_antialiasing)("\" ")
    //("shaders=\"")(_shaders)("\" ")
    // TODO convertir en simplestring
    ("driver=\"")(_videoDriver)("\" ")
    ("audio=\"")(_audioDriver)("\" />")
    ;

    ////////////////////////////////////////////////////////////
    /////   SHADERS
    ////////////////////////////////////////////////////////////
    //motionblur
    //BOOST_FOREACH(){
    for( TShadersList::iterator i(_shaders.begin()),end(_shaders.end()); i != end; ++i){
        text("<shader type=\"")(i->first)("\" enabled=\"")(i->second)("\" />");
    }

    //text("<game dialogs=")(_enableDialogs)(" language=")("french")(" />");


    // fin du fichier
    text("\n</config>");

    file << std::wstring(text);
    //file << text.str();


*/

    file.close();

}
