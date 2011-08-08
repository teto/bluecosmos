
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
#include <irrlicht.h>
#include "../startup_config.hpp"
#include "../audio/SAudioParameters.hpp"
#include <fusion/scripting/CLuaVM.hpp>


using namespace irr;
using namespace luabind;




//CSinglePlayerState
//CGraphicalLevel* levelMgr
luabind::scope
bindConfigStructToLua()
{


    return luabind::class_<SIngameConfig>("IngameConfig")
        .def_readwrite("EnableBloomShader",&SIngameConfig::EnableBloomShader)
        .def_readwrite("EnableMotionBlurShader",&SIngameConfig::EnableMotionBlurShader)
        .def_readwrite("EnableDialogs",&SIngameConfig::EnableDialogs),

    // TODO enregistrer l'enumeration des drivers
        luabind::class_<audio::SAudioParameters>("SAudioParameters")
//            .enum_("DriverTypes")
//            [
//                value("fmodex", audio::Fmodex),
//                value("openal",video::EDT_DIRECT3D8),
//                value("null",video::EDT_DIRECT3D8)
//            ]
        //.def_readwrite("Volume",&SIrrlichtCreationParameters::Fullscreen)
        //.def_readwrite("Vsync",&SIrrlichtCreationParameters::Vsync)


        ,

    //luabind::def("__newindex",&specialNewIndex),

    luabind::class_<irr::SIrrlichtCreationParameters>("SIrrlichtCreationParameters")
        .def_readwrite("Fullscreen",&SIrrlichtCreationParameters::Fullscreen)
        .def_readwrite("Vsync",&SIrrlichtCreationParameters::Vsync)
        .def_readwrite("DriverType",&SIrrlichtCreationParameters::DriverType)
        .enum_("DriverTypes")
            [
                value("opengl", video::EDT_OPENGL),
                value("directx8",video::EDT_DIRECT3D8),
                value("directx9",video::EDT_DIRECT3D9),
                value("software",video::EDT_BURNINGSVIDEO)
            ]

//enum_<video::E_DRIVER_TYPE>("VideoDriver")
//        .def_readwrite("DriverType",&SIrrlichtCreationParameters::DriverType)
//        .def_readwrite("DriverType",&SIrrlichtCreationParameters::DriverType)
//        .def_readwrite("DriverType",&SIrrlichtCreationParameters::DriverType)
    ;

//    ];

}


