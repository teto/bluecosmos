/**
* \file player.hpp
* \todo regourper tous les input pour les passer en parametre ? dans les update
*/
#ifndef ENTITY_PLAYER_HPP
#define ENTITY_PLAYER_HPP


//#include "IEntity.hpp"
//#include "IMultiModeTransformer.hpp"
#include "SModeDescription.hpp"
#include "CStaticBattery.hpp"
#include <fusion/macros.hpp>
//#include "../IEngineConfig.hpp"
#include <irrlicht.h>
#include <bitset>
#include <list>
//#include <slist>
#include <array>
#include <luabind/luabind.hpp>
//#include <boost/circular_buffer_fwd.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/weak_ptr.hpp>
#include "../def.hpp"
#include "../CSpeaker.hpp"
//#include "../events/CBindCollection.hpp"



//forward declaration
//class CGraphicalLevel;
class CPlayer;
class  IMultiModeTransformer ;

//template <int SIZE,class ID_TYPE>
class CBindCollection;
//
//template <int SIZE,class ID_TYPE>

namespace SPK {
    namespace IRR {
        class IRRSystem;
    }
}

namespace NWalkyrieModel {
enum EId {
YF19,
YF21
};
}

namespace NBooster {
enum EId {
Left,
Right,
Count
};

}


//! Register performances of the player
struct SStats {
SStats();
int Destroyed;  //!< Number of destroyed enemies
//int Level;      //!< Reached level
int Score;      //!< Score
int Deaths;     //!< number of deaths registered
int NbOfTransformations;
void addKill(CStaticBattery*);
//std::array<int,CPlayer::ModesCount> PlayedTimes;
};






//forward declaration
class CGameEngine;
class CBindDescriptor;
class CSinglePlayerState;
//class CBattery;

//<NBooster::Count>
typedef IMultiModeTransformer TWalkyrie;





// Derive de CStaticBattery pr pvr etre pris en chasse par
class CPlayer :
//public IMultiModeTransformer,
public CStaticBattery,
public CSpeaker
//,
//public IPlayerMode
{

    static const NWalkyrieModes::ERealMode _virtualModes[2][3];

public:
    enum EBooster {
    BoosterLeft,
    BoosterRight
    };





protected:
    //std::array<>
    // Register each possible move
    //typedef irr::core::vector3df TMovesMap;
    //static TVector3df _moves[2][2];

private:
    enum EElapsedTime {
    SinceLastMissile,
    SinceLastShot,
    SinceLastTransformation,
    //SinceBeingKilled,
    SinceLastBlinkRevival,
    //Cooldown,
    ElapsedTimesCount
    };

    int _blinksCounter;


    //typedef std::list<CStaticBattery*> TTrackedBatteries;
    CMissile* _trackedMissile;

    // Mettre des timers ?
    typedef std::array<TTimer::TimeType,ElapsedTimesCount> TElapsedTimes;
    TElapsedTimes _elapsedTimes;



    CGameEngine& _engine;
    CSinglePlayerState* _fightingState;

    float _missilesHeat;
    bool _coolingDown;
//
//    typedef SModeDescription TSpecsMap[ModesCount];
//
//    //static
//    TSpecsMap _specs;
    //////////////////////////////////////////////
    /// Set to true as soon as touch pressed, when key released, then throw missiles
    //////////////////////////////////////////////
    bool _targeting;

protected:
    const bool isTrackingEnemies() const { return _targeting; };

public:    //typedef TTrackedBatteries
    TTrackedBatteries _trackedBatteries;

    float _cannonHeat;
    NWalkyrieModel::EId _walkyrieType;
    // Les passer en std
    boost::shared_ptr<IMultiModeTransformer> _walkyrie;
    //boost::shared_ptr<CBindCollection  > _binds;

    // TODO remplacer par un tablo
    SPK::IRR::IRRSystem* _leftBooster;
    SPK::IRR::IRRSystem* _rightBooster;

    TVector3df _currentPos;
    TVector3df _rotation;
    TVector3df _targetedRotation;
    TVector3df _previousRotation; // sert de backup ds le cas d'1 tracking misisile

    int _livesLeft;                     //!< Lives number

    // todo creer une lanceur de missiles ?
    // voir comment on stock les missiles ?
    int _missilesLeft;

    // on ne s'en sert pas pr l'instant
    std::string _name;  // nom du vaisseau "yf19 ou yf21 par exemple




    SStats _stats;


    //typedef CBindCollection<NPlayerInput::Count> TMappingSet;

    TMappingSet *_mappingSet;
    //boost::shared_ptr< CCollectionSnapshot<NPlayerInput::Count> > _input;
    //CCollectionSnapshot<NPlayerInput::Count> _Input;
    TPlayerInputCache *_cachedInput;




    //void addAlly(CStaticBattery*);


    void updateInput();
    bool startTrackingEnemies();
    bool stopTrackingEnemies();
    bool trackNewBattery();


    //void setMapping(boost::shared_ptr<TMappingSet> mapping);
    void onTimeoutDisparition();
    void onDeath();
    void onCollision(CStaticBattery*);

    void setupAsModel( const NWalkyrieModel::EId& id );
//    void setupAsYF19();
//    void setupAsYF21();

    const NEntityType::EId getType() const { return NEntityType::Player;};



    float getRange() const;

    void setupNewLife();
    void setupForNewGame();

    // TODO faire sans
    //void getMappingDescription(lua_State* L,const int& id);


    const bool& coolingDown() const ;
    const int& getLivesLeft() const {return _livesLeft;};
    const int& getScore() const {return _stats.Score;};
    void kill();

    //void OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* node);
    bool update(const TTimer::TimeType& elapsed);

    void processMoves();
    void processFighterMoves();
    void processGerwalkMoves();
    void processBattloidMoves();



//    void processShootingsAsGerwalk();
//    void processShootingsAsBattloid();
//    void processShootingsAsFighter();

    // returns true if killed
    // straightaway 1 damage is enough to kill player
    //bool addDamage(const int&);

public:
    //boost::weak_ptr
    float getCruiseSpeed();// const;

    //[_currentMode]
    //inline const SModeDescription& getSpec() const { return _currentSpec;;};

    const TVector3df& getPosition(){ return _currentPos; };

    //IMultiModeTransformer* transformer
//    bool setTransformerModel(irr::scene::ISceneManager* smgr, const NWalkyrieModel::EId& id);
bool setTransformerModel(const char* meshFilename, const char* leftBoosterName,const char* rightBoosterName);

    // TODO renommer en load
    void createBoosters();
    void FireMissiles();
    void FirePrimaryShot();
    void processShootings();
    bool processTransformations();


    CGameEngine& engine() const;

//scene::IAnimatedMeshSceneNode* node,CGameEngine*,
//TMappingSet& mapping
    CPlayer();
    ~CPlayer();



    void clearModes(const NWalkyrieModes::EVirtualMode&);
    // TODO renommer en addMode
    void allowMode(const NWalkyrieModes::EVirtualMode& mode);

};

#endif
