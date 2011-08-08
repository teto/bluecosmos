
// definit ici et binde les fct lua necessaires
#include <luabind/luabind.hpp>

#include "binds.hpp"
// Include needed policy
#include <luabind/copy_policy.hpp>
//#include <luabind/dependency_policy.hpp>
#include <luabind/out_value_policy.hpp>
#include <luabind/raw_policy.hpp>
#include <luabind/return_reference_to_policy.hpp>
#include <luabind/return_reference_to_policy.hpp>
#include <luabind/error.hpp>
#include "../fightingState/CSinglePlayerState.hpp"
#include "../audio/ISound.hpp"
//#include "../audio/CFmodExDriver.hpp"
#include "../audio/IAudioDriver.hpp"


using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace luabind;
using namespace audio;




//CSinglePlayerState
//CGraphicalLevel* levelMgr
luabind::scope
bindSound()
{


    return luabind::class_<ISound>("ISound")
        //.def(luabind::constructor<std::string>())
        .def("Play",&ISound::play)
        .def("Pause",&ISound::pause)
        //.def("getArtist",&CSound::getArtist)
        //.def("getFilename",&CSound::getFilename)
        .def("Stop",&ISound::stop),

    luabind::class_<IAudioDriver>("IAudioDriver")
        .def("loadSound", &IAudioDriver::getSound )
        //.def("loadMusic", &IAudioDriver::getMusic )
    ;

//    ];

}


