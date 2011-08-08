/**
* \file entity_manager.h
*
sorte de geant wrapper
Pour la gestion des collisions: http://www.shmup-dev.com/forum/index.php?topic=1636.0
*/// On n'enregistre que les batteries <=> bullets & ennemis. Collision avec le joueur a part ?
// en fait tt est batterie : ennemis, joueur et bullets
#ifndef _BC_CLevel_HPP_INCLUDED
#define _BC_CLevel_HPP_INCLUDED


//#include "CFleet.hpp"
#include "def.hpp"
#include "utils/CIntrusivePool.hpp"
#include <vector>
#include "states/IGameState.hpp"
#include "entities/CStaticBattery.hpp"
#include "observer/CMessage.hpp"
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


// More tags if can be add into more than 1 list
class CLevel : public boost::noncopyable
{
public:

    enum EPlayState {
    Dialog,
    Playing,
    //Revival,
    PlayerDead,
    BossWarning
    };


protected:
//CLevel*
    //bool mShowHitBox;       //!< pr afficher les hitbox
    // TODO boost::shared_ptr
    std::list< CSpeaker*> _actors;


/**
Devrait y avoir un pool commun aux 2 fleets
voir si on peut pas proposer un systeme de strategie
Merger Missile/Bullet & Static battery
**/
//    typedef bin::slist< CBullet, Hook, bin::linear<true>, bin::cache_last<true>  > TBulletList;

    //_enemyF
public:


        irr::scene::ISceneNode* _world;

    irr::scene::ISceneNode* _terrain;
    //irr::scene::ISceneNode* _comprehensiveBox;
    irr::scene::ISceneNode* _layer;

//    static TVector3df getPlayerForwardVector() { return TVector3df(0,1,0) };
    boost::shared_ptr<CFleet> _alliedFleet;
    boost::shared_ptr<CFleet> _enemyFleet;

    CFleet* getAllyFleet() { return _alliedFleet.get(); };
    CFleet* getEnemyFleet() { return _enemyFleet.get(); };
    // TODO a supprimer
//    void updateState();

    //inline CGameEngine* engine() const { return IGameState::engine();};
    inline CPlayer& getPlayer() const { return *(ENGINE->getPlayer());};

    //void addEnemy(CStaticBattery*);
    void addAlly(CStaticBattery*);

    void addLayer();

    // set skydome
    void setBackground( const char* );
    // set skybox
//    void setBackground(
//                       const char*,
//                       const char*,
//                       const char*,
//                       const char*,
//                       const char*,
//                       const char*,
//                        );


//    CBullet*  createBullet();
//    CMissile* createMissile();

    CSpeaker* createActor(const std::string&,const std::string&);
    //CBatteryModel* createBatteryModel(const char* filename,const int& life,const int& bonus,const float& range);
    CModel* createBatteryModel(const char* filename,const int& life,const int& bonus,const float& range);
    //CSound* createSound();

    static CSpeech* createSpeech(const std::string&,const std::string&);

// TODO see lesquels supprimer
    irr::f32 _upperProgress;
    irr::f32 _lowerProgress;


    CStaticBattery* getNextTarget();

    float getUpperProgression() const;

//TODO to remove
    float getLowerProgression() const;


//CSinglePlayerState*
    bool init( );


    static void getVectorFromAngle(const float& angle,TVector3df& vectorToRotate);


    static TVector3df getPlayerForwardVector(){
        return TVector3df (0.f,0.f,1.f);
    }

    static TVector3df getEnemyForwardVector(){
        return TVector3df (0.f,0.f, -1.f);
    }

//    CMissile* addMissile(const char* model);
        void updatePlayerProgress(const float& playerProgress);

    irr::core::rectf _clippingPlane;

    //void draw();const float& playerAdv,
    void update( const TTimer::TimeType&, CSinglePlayerState* _state);
    void checkCollisions();



    ~CLevel();
    CLevel();



};


#endif
