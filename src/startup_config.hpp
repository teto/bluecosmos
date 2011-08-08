#ifndef STARTUP_Config_HPP
#define STARTUP_Config_HPP

#include "events/CBindDescriptor.hpp"

#include "def.hpp"

//init(SIrrlicht param,audioParam,GameSpecific)


struct SIngameConfig {

SIngameConfig();

//
//typedef std::array<CBindDescriptor,NPlayerInput::Count> TMapping;
//typedef CBindCollection<NPlayerInput::Count,NPlayerInput::EId> TMapping;
//TMapping Keymap1;
//TMapping Keymap2;
TMappingSet* MappingPlayer1;


bool EnableBloomShader;
bool EnableMotionBlurShader;
bool EnableDialogs;

//static VideoDriversName[irr::video::EDT_ ] = ;
};










#endif
