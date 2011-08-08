#include "binds.hpp"
// definit ici et binde les fct lua necessaires
#include <luabind/luabind.hpp>




//#include "../fightingState/CSinglePlayerState.hpp"
#include "../entities/player.hpp"
#include "../entities/CBullet.hpp"
#include "../entities/IMultiModeTransformer.hpp"
#include <luabind/operator.hpp>
// Include needed policy
#include <luabind/copy_policy.hpp>
//#include <luabind/dependency_policy.hpp>
#include <luabind/out_value_policy.hpp>
#include <luabind/raw_policy.hpp>
#include <luabind/return_reference_to_policy.hpp>
#include <luabind/error.hpp>
#include <boost/any.hpp>

#include "concat.hpp"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace luabind;


//luabind::maketable
//CSinglePlayerState
//CGraphicalLevel* levelMgr
luabind::scope
bindPlayerToLua()
{

    return luabind::class_<CStaticBattery>("CBattery")
        //.def("pos",&CObject::getPosition)
        //(void (CDialogState::*)(CSpeaker*,const std::string& ,const std::string&))
        .def("pos",(void (CStaticBattery::*)(const float&,const float& ,const float&))&CStaticBattery::setPosition)
        // raw(_2) because first parameter is this
        .def("getPos",&CStaticBattery::exportPositionToLua, luabind::raw(_2) )
        .def("getDamage",&CStaticBattery::getDamage)
        .def("getRange",&CStaticBattery::getRange)
        .def("getRotation",&CStaticBattery::getRotation)
        .def("setup",&CStaticBattery::setup)
//        .def("setRange",&CStaticBattery::setRange)
//        .def("setBonus",&CStaticBattery::setBonus)
//        .def("setLife",&CStaticBattery::setLife)
        .def("setTarget",&CStaticBattery::setTarget)
        // setup(life/bonus/range etc...)
        .def("setMesh",&CStaticBattery::setMesh)
        .def("update",&CStaticBattery::update)
        // TO remove
        .def("updateRotation",&CStaticBattery::updateRotation)
        //.def("kill",&CStaticBattery::kill)
        //.def("onDeath",&CStaticBattery::onDeath)
        .def("translate",&CStaticBattery::translate)
        .def("setPosition",(void (CStaticBattery::*)(const float&,const float&,const float&))&CStaticBattery::setPosition)
        .def("shootBullet",&CStaticBattery::shootBullet)
        .def("setRotationSpeed",&CStaticBattery::setRotationSpeed)
        // defined in "luabind/operator.hpp" ?!
        //.def( luabind::tostring(luabind::self) )const_self
        .def( luabind::tostring(luabind::const_self ) )
        //.def( luabind::const_self == luabind::other<CStaticBattery>() )

        .def( luabind::concat_operator(luabind::const_self,luabind::other<std::string>() ) )
        .def( luabind::concat_operator(luabind::const_self,int() ) )
        .def( luabind::concat_operator(luabind::other<std::string>(),luabind::const_self ) )
        ,


    luabind::class_<SModeDescription>("SModeDescription")
        //.def("defineAnimation",&SModeDescription::defineAnimation, luabind::return_reference_to(_1) )
        .def("setAngleBounds",&SModeDescription::setAngleBounds, luabind::return_reference_to(_1) )
        .def("setRange",&SModeDescription::setRange, luabind::return_reference_to(_1) )
        .def("setupSpeeds",&SModeDescription::setupSpeeds, luabind::return_reference_to(_1) )
        .def("setCameraRecul",&SModeDescription::setCameraRecul, luabind::return_reference_to(_1) )
        ,

    luabind::class_<IMultiModeTransformer, SModeDescription>("Transformer")
        .enum_("Mode")
        [
//            value("Fighter",NWalkyrieModes::Fighter),
//            value("Gerwalk",NWalkyrieModes::Gerwalk),
//            value("Battloid",NWalkyrieModes::Battloid),

            value("yf19_Fighter",NWalkyrieModes::yf19_Fighter),
            value("yf19_Gerwalk",NWalkyrieModes::yf19_Gerwalk),
            value("yf19_Battloid",NWalkyrieModes::yf19_Battloid),
            value("yf21_Fighter",NWalkyrieModes::yf21_Fighter),
            value("yf21_Gerwalk",NWalkyrieModes::yf21_Gerwalk),
            value("yf21_Battloid",NWalkyrieModes::yf21_Battloid)

        ]
        .scope [
            def("getMode",&IMultiModeTransformer::getModeFromModeId)
        ],

    luabind::class_<CBullet, bases<CStaticBattery> >("CBullet"),

    // Bases => multiple inheritance
    // rq on peut utiliser boost::scoped_ptr<X> dans class_
    luabind::class_<CPlayer, bases<CStaticBattery> >("CPlayer")
        .enum_("Mode")
        [
            value("Fighter",NWalkyrieModes::Fighter),
            value("Gerwalk",NWalkyrieModes::Gerwalk),
            value("Battloid",NWalkyrieModes::Battloid)
        ]
        .def("processMoves",&CPlayer::processMoves)
        .def("processTransformations",&CPlayer::processTransformations)
        .def("processShootings",&CPlayer::processShootings)
        // en gros si on decommente les 2 prochaines lignes ca compile pas
        .def("clearAllowedModes",&CPlayer::clearModes)
        // return_reference_to policy tells luabind that return value is already on the heap
        .def("allowMode",&CPlayer::allowMode )
        //.def("forceMode",&CPlayer::forceMode )
        // doesn't work
        // TODO should use copy ?
        //.def("getMappingDescription",&CPlayer::getMappingDescription, luabind::copy(luabind::result))
        //.def("getMappingDescription",&CPlayer::getMappingDescription, luabind::raw(_2))

        //scope [
        //def("getMode",&CPlayer::getSpecs)
        //]
        //.def("setupMode",&CPlayer::setupMode)
        .enum_("Input")
        [
            value("Forward",        NPlayerInput::MoveForward),
            value("Backward",       NPlayerInput::MoveBackward),
            value("Left",           NPlayerInput::MoveLeft),
            value("Right",          NPlayerInput::MoveRight),
            value("ModeUp",         NPlayerInput::ModeUp),
            value("ModeDown",       NPlayerInput::ModeDown),
            value("MainShoot",      NPlayerInput::MainShoot),
            value("SecondShoot",    NPlayerInput::SecondShoot)
        ];

    //];

}


