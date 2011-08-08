/**
\file
\author
**/
#ifndef CFleet_HPP
#define CFleet_HPP



//#include "CIntrusiveList.hpp"
#include <forward_list>
//std::forward_list
#include <irrlicht.h>
#include <fusion/maths/macros.hpp>
#include <fusion/logging/ILogger.hpp>
#include <array>
#include "def.hpp"
#include "utils/TClock.hpp"

class CFleet;
class CPlayer;
class CMissile;
//class CGameEngine;
class CBullet;
class CStaticBattery;
class CGraphicalLevel;
class CIntrusiveList;
class CSinglePlayerState;


//typedef std::list<CStaticBattery*> TTrackedBatteries;
//: public CIntrusiveList
class CFleet
{


private:
    //CSinglePlayerState* _master;
    typedef  std::forward_list<CStaticBattery*> TBatteryContainer;
    TBatteryContainer _activeBatteries;

protected:
    //typedef std::array<CIntrusiveList,NEntityType::Count> TDeadPool;
    typedef std::array< TBatteryContainer, NEntityType::Count> TDeadPool;
    static  TDeadPool _deadPool;



    CStaticBattery* getDeadButAllocatedBattery(const NEntityType::EId& type);
    //removeBattery(CStaticBattery*);

//CStaticBattery* battery
    void killEntityNextTo(TBatteryContainer::iterator& );


    irr::scene::ISceneNode *_fleetRootNode;
    CSinglePlayerState* _fightingState;

public:
    void addConfiguredEntityToAliveBatteries(CStaticBattery* battery);
    irr::scene::ISceneNode * getRootNode() const { return _fleetRootNode;};

    static void clearDeadPool();
    static void destroyAll();
    void killAllAlive();

    //CIntrusiveList _aliveBatteries;

    //bool _showHitBox;
    void draw();


    /**
    * Used from Lua
    * \param
    *
    **/
//    CStaticBattery* addStaticBattery(const char* model);
//const char* model
    CStaticBattery* createAndConfigureStaticBattery();

    //CStaticBattery* createAndSetupBattery(CStaticBattery* battery);
//    CMissile* addMissile(const char* model,
//                        const irr::core::vector3df& position,
//                        CStaticBattery* target,
//                        const irr::core::vector3df& speed
//                        );

    //inline,const TVector3df& position
    //,const TVector3df& position
    CBullet* createAndSetupBullet(const char* model,const float& angleDeg);
    CBullet* createAndSetupBullet(const char* model,const TVector3df& forward );

    //
    CMissile* createAndSetupMissile(const char* model,const TVector3df& forward,const TVector3df& position );




    CFleet( CSinglePlayerState* );

    /// TODO old
    CStaticBattery* getNearestEnemy(const TVector3df& position);

    CStaticBattery* getNextTarget(const std::list<CStaticBattery*>& list);




    //, boost::mem_fn
    //CStaticBattery*
    bool checkCollisions(CFleet& fleet);
//const float& range,const irr::core::vector3df& position





    void update(const TTimer::TimeType&);
    virtual ~CFleet();


protected:

    //TBulletList::iterator deleteBullet(CBullet&);


};

#endif // CENEMYFLEET_HPP
