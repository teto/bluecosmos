/** \file config.h
 *  \brief Defines all default values ( that is starting with an underscore "_" )
**/
#ifndef __BC_DEFINITION_HPP__
#define __BC_DEFINITION_HPP__

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <irrlicht.h>
#include "CustomEvent.hpp"
#include <list>




class CGameEngine;
class CPlayer;
class IBasicGameState;

namespace fus {
    class CLuaVM;
}

//typedef boost::shared_ptr<CGameEngine> TEnginePtr;
//boost::scoped_ptr<CGameEngine>
typedef CGameEngine* TEnginePtr;

//boost::scoped_ptr<
typedef boost::shared_ptr<CPlayer> TPlayerPtr;
//typedef CPlayer* TPlayerPtr;
typedef boost::shared_ptr<IBasicGameState> TGameStatePtr;
// This is how we recognize an Id
typedef const char* TGameStateId;
//ICustomEvent
//typedef irr::SEvent::SUserEvent TGameStateEvent;
typedef std::pair<NStateEvent::EId,TGameStateId> TGameStateEvent;
//typedef CCustomEvent TGameStateEvent;

typedef fus::CLuaVM TScriptingVM;

typedef irr::core::vector3df TVector3df;

typedef irr::u32 TTimeUnit;


namespace NEntityType {
// !!! Les int ne doivent pas se recouvrir !!
//enum class EEntityType  {
enum EId  {
//Enemy = 0,
//EnemyBullet = 1,
//EnemyMissile = 2,
//AlliedBullet = 4,
//AlliedMissile = 8,
//Player = 16,

Missile,
Bullet,
Battery,
Player,
Count
};

}

namespace NWalkyrieModes {

//createAndConfigureStaticBattery
    enum ERealMode {
    //HighSpeedFighter = 0,
    yf19_Fighter = 0,
    yf19_Gerwalk,
    yf19_Battloid,

    yf21_Fighter,
    yf21_Gerwalk,
    yf21_Battloid,
    //FighterWithWheels =4  // Pareil que Efighter mais apres
    Count // internal use
    };


    enum EVirtualMode {
    Fighter,
    Gerwalk,
    Battloid

    };
}


typedef NWalkyrieModes::ERealMode TModeId;
typedef int TPlayerReply;

class CStaticBattery;
typedef std::list<CStaticBattery*> TTrackedBatteries;



// Forward dec
//template <int SIZE,class ID_TYPE>
namespace input {
    class CBindCollection;
}
class CPlayerInputCache;


//typedef CBindCollection<NPlayerInput::Count,NPlayerInput::EId> TMappingSet;
typedef input::CBindCollection TMappingSet;


//typedef CBindCollection TPlayerInputCollection;
//typedef CBindCollection<NPlayerInput::Count,NPlayerInput::EId> TMappingSet;
//typedef Cache<NPlayerInput::Count,NPlayerInput::EId> TPlayerInputCache;

typedef CPlayerInputCache TPlayerInputCache;


namespace NPlayerInput {
enum EId {
MoveLeft = 0,   // Should remain first
MoveRight,
MoveForward,
MoveBackward,
MainShoot,
//SwitchingDirection,
//EnableSpin,
QuickMainShoot,
SecondShoot,
QuickSecondShoot,
ModeUp,
ModeDown,

Count  // should remain last
};
}

//extern std::array<const wchar_t*,NPlayerInput::Count> BindNames;

// TODO declarer en extern ?
//std::vector<std::wstring> BindNames
extern const wchar_t*  BindNames[NPlayerInput::Count];
#define ENGINE  CGameEngine::getInstance()

#endif
