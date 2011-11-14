/**
* \file entity_manager.h
*
sorte de geant wrapper
Pour la gestion des collisions: http://www.shmup-dev.com/forum/index.php?topic=1636.0
*/// On n'enregistre que les batteries <=> bullets & ennemis. Collision avec le joueur a part ?
// en fait tt est batterie : ennemis, joueur et bullets
#ifndef _BC_CGraphicalLevel_HPP_INCLUDED
#define _BC_CGraphicalLevel_HPP_INCLUDED


//#include "CFleet.hpp"
#include "def.hpp"
#include <vector>
#include "states/IGameState.hpp"
#include "entities/CStaticBattery.hpp"
//#include "observer/CMessage.hpp"
#include "game_engine.hpp"
#include <boost/utility.hpp>
#include <irrlicht.h>

class CSpeaker;
class CSpeech;

// forward declarations
class CPlayer;
class CGameEngine;
class CSinglePlayerState;
class CFleet;
//class CStaticBattery;
class CModel;

//boost::factory

// TODO renommer en CLevel
// More tags if can be add into more than 1 list
class ILevel
{

public:

    virtual bool isLoaded() const;

    virtual bool reload();

    /**

    **/
    virtual bool run() const;

protected:

public:


//        irr::scene::ISceneNode* _world;
//
//    irr::scene::ISceneNode* _terrain;
//    irr::scene::ISceneNode* _layer;

////    static TVector3df getPlayerForwardVector() { return TVector3df(0,1,0) };
//    boost::shared_ptr<CFleet> _alliedFleet;
//    boost::shared_ptr<CFleet> _enemyFleet;
//
//    CFleet* getAllyFleet() { return _alliedFleet.get(); };
//    CFleet* getEnemyFleet() { return _enemyFleet.get(); };
    // TODO a supprimer
//    void updateState();

    //inline CGameEngine* engine() const { return IGameState::engine();};
//    inline CPlayer& getPlayer() const { return *(ENGINE->getPlayer());};

    //void addEnemy(CStaticBattery*);
//    void addAlly(CStaticBattery*);

    //void addLayer();

    // set skydome
    //void setBackground( const char* );
    // set skybox
//    void setBackground(
//                       const char*,
//                       const char*,
//                       const char*,
//                       const char*,
//                       const char*,
//                       const char*,
//                        );

//
////    CBullet*  createBullet();
////    CMissile* createMissile();
//
//    CSpeaker* createActor(const std::string&,const std::string&);
//    //CBatteryModel* createBatteryModel(const char* filename,const int& life,const int& bonus,const float& range);
//    CModel* createBatteryModel(const char* filename,const int& life,const int& bonus,const float& range);
//    //CSound* createSound();
////,const std::string&
//    static CSpeech* createSpeech(const std::string& );
//
//// TODO see lesquels supprimer
//    irr::f32 _upperProgress;
//    irr::f32 _lowerProgress;

    void update( const TTimer::TimeType&);

    ~CGraphicalLevel();
    CGraphicalLevel();



};


#endif
