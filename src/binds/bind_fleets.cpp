
// definit ici et binde les fct lua necessaires
#include <luabind/luabind.hpp>

// Include needed policy
#include <luabind/copy_policy.hpp>
//#include <luabind/dependency_policy.hpp>
#include <luabind/out_value_policy.hpp>
#include <luabind/raw_policy.hpp>
#include <luabind/return_reference_to_policy.hpp>
#include <luabind/return_reference_to_policy.hpp>
#include <luabind/error.hpp>


#include "../fightingState/CSinglePlayerState.hpp"
#include "../CFleet.hpp"

#include "../CSpeaker.hpp"
#include "../CSpeech.hpp"
#include "../CGraphicalLevel.hpp"
#include "../entities/CModel.hpp"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace luabind;





//CSinglePlayerState
//CGraphicalLevel* levelMgrTScriptingVM& vm
luabind::scope
bindFleets()
{

// Export our class with LuaBind/mLuaState
return
    //, boost::shared_ptr<CFleet>
    luabind::class_<CFleet >("CFleet")
    // TODO renommer en spawnStaticBattery ?
        .def("addBattery",&CFleet::createAndConfigureStaticBattery);
        /*.def(luabind::constructor<>())

        .def("addSpeech",(void (CDialogState::*)(CSpeaker*,const std::string&)) &CDialogState::AddSpeech)
        */


  // ];



}



//TScriptingVM& vm
luabind::scope
bindLevelHandlerToLua()
{


//vm.reset();

// Export our class with LuaBind/mLuaState
return
    luabind::class_<CSpeaker>("Actor"),

    luabind::class_<CModel>("Model")
        ,


    luabind::class_<CSpeech>("Speech")
        //.def("setMessage", &CSpeech::setMessage)
        .def("addAnswer", &CSpeech::addAnswer)
        ,

    luabind::class_<CGraphicalLevel>("CGraphicalLevel")
        //.def("update",&CGraphicalLevel::update)
        .def("addLayer",&CGraphicalLevel::addLayer)
        .def("setBackground",&CGraphicalLevel::setBackground)
        //.def("loadModel",&CGraphicalLevel::createBatteryModel)

        //,
        //.def("removeEnemyBattery",&CGraphicalLevel::removeEnemyBattery)


        //.def("LoadBatteryDirectory",&CGraphicalLevel::LoadBatteryDirectory)
   ;


}

