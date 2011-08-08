/**
\file IGameConfig.h

Refaire pour l'adapter avec le systeme de boost::program_options
*/
#ifndef IGameConfig_HPP
#define IGameConfig_HPP


#include <map>
#include <string>
#include <bitset>
#include <irrlicht.h>
//#include <array>  // header only
//#include "def.hpp"



class SIngameConfig;
namespace audio {
    class SAudioParameters;
}

// TODO remplacer les bool par des void car les fonctions vont lancer des exceptions plutot
void loadEngineConfigFromLua(const char*, irr::SIrrlichtCreationParameters&,SIngameConfig&,audio::SAudioParameters&);


void saveConfigIntoLuaFile(
        const char* filename,
        const irr::SIrrlichtCreationParameters& engineParam,
        const SIngameConfig& ingameConf,
        const audio::SAudioParameters& audioParam);

//class IGameConfig
//{
//
//
//public:
//    CConfigManager();
//    ~CConfigManager();
//
//    //bool Save();
//    bool RawSave(
//                 const char* filename
//                 );
//
//
//    bool loadFromFile(const char* filename
//
//              );
//
//};


#endif

