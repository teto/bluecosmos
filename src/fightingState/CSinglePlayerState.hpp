/**
* \file single.h
**/
#ifndef SinglePlayerState_HPP
#define SinglePlayerState_HPP

#include "../CGraphicalLevel.hpp"
#include "../states/IGameState.hpp"
#include "../entities/player.hpp"
#include <map>
#include <boost/weak_ptr.hpp>

#include <list>
#include <irrlicht.h>
#include <memory>
#include "../utils/IClock.hpp"

namespace fus {
    class CLuaThread;
    class CLuaVM;
}

class CSpeaker;
class CSpeech;
class CFadingImage;


using namespace irr;
using namespace gui;
using namespace scene;
using namespace core;

void enableMenu(irr::gui::IGUITab* , const bool&);

// Forward declaration
//class CGraphicalLevel;

namespace NTexture {
enum EId {
Life = 0,
Energy,
Explosion,
Cursor,
Lockon,
Count  // Doit toujours rester dernier
};
}


namespace NCamera {
enum EId {
LeftHUD,
RightHUD,
Scene,
Flying,
Count
};

}

namespace NPlayState {
    enum EId {
    Dialog,
    InitializingScriptingEngine,
    Editing,
    Playing,
    //Revival,
    //PlayerDead,
    NoLevelLoaded,
    Uninitialized,
    Cinematic,
    Menu,
    BossWarning,
    EndingLevel,
    StartingLevel,
    GameOver,
    Count
    };

}

class CSinglePlayerState :
    public IGameState<NStateId::Solo,true>
{
private:

    typedef std::pair<CSpeaker*,CSpeech*> TDialog;
    //TDialog _dialog;
    TPlayerReply _lastPlayerReply;

/// HACCCCKKK
    bool _initialized;


std::string _levelFilename;

//    boost::shared_ptr<CGraphicalLevel> _levelMgr;
    boost::shared_ptr<CFadingImage> _levelTransitionImage;

    irr::gui::IGUITab* _pauseMenu;
    irr::gui::IGUITab* _gameOverMenu;
    irr::gui::IGUITab* _dialogTab;

    NPlayState::EId _playState[2];
    //NPlayState::EId _backupState;
    //std::string _nextLevelName;

    gui::IGUIListBox* _answers;

protected:

    void GUI_CreateDialogTab();

    void updateDialog();
    void updateCinematic();
    void updatePlaying();
    void updateWarning();
    void updateStartingLevel();
    void updateEndingLevel();
    void updateMenu();

    //void drawDialog();
    bool reloadLevel();

    const NPlayState::EId& getInnerState( ) const { return _playState[0];};
    void restorePreviousState( ) ;
    //void changeState( const NPlayState::EId& newState );
    void changeState( NPlayState::EId newState );
    bool setupFadingTransition(const char* filename);


    bool setupLuaThread();
    TTimer* _shakingTimer;
    TVector3df _camPosBackup;
    CPlayer* _player;//vont etre geree via entitymanager
    ICameraSceneNode* _camera;

    void updateCamera();


public:
    // partie dialogue
    void showMessage(CSpeaker* speaker, CSpeech* speech);
    TPlayerReply getUserReply() const;


    // TODO la je passe forcement le nom du niveau a charger
    CSinglePlayerState();
    ~CSinglePlayerState();



    void startEditor(const char* filename,const int& line);


    void allLevelsFinished();
	void Update();

    bool loadLevel(const std::string&);
    void shakeCamera();

//createFollowSplineAnimator (s32 startTime, const core::std::array< core::vector3df > &points, f32 speed=1.0f, f32 tightness=0.5f, bool loop=true, bool pingpong=false)=0
    void launchCinematic();

    void addSimpleExplosion(const TVector3df& position );

    //void setChaseCam(vector3df posIn,vector3df rotIn,float vel,float dist,float height,float aimHeight,float speed,ICameraSceneNode * cam );
    void setupCameras();

    void onResume();
    void onHold();

	void CleanUp();

	void Draw();
	bool OnEvent(const irr::SEvent&);

    bool isPlayerUpdatable() const;



    boost::scoped_ptr<fus::CLuaVM> _script;
    irr::scene::ISceneNode* _world;



//    static TVector3df getPlayerForwardVector() { return TVector3df(0,1,0) };
//    boost::shared_ptr<CFleet> _alliedFleet;
//    boost::shared_ptr<CFleet> _enemyFleet;
    std::shared_ptr<CFleet> _alliedFleet;
    std::shared_ptr<CFleet> _enemyFleet;

    CGraphicalLevel* _level;

    //CGraphicalLevel* getLevel();


    CFleet* getAllyFleet() { return _alliedFleet.get(); };
    CFleet* getEnemyFleet() { return _enemyFleet.get(); };
    // TODO a supprimer
//    void updateState();

    //inline CGameEngine* engine() const { return IGameState::engine();};
    //inline CPlayer& getPlayer() const { return *(ENGINE->getPlayer());};

    //void addEnemy(CStaticBattery*);




    CSpeaker* createActor(const std::string&,const std::string&);
    //CBatteryModel* createBatteryModel(const char* filename,const int& life,const int& bonus,const float& range);
   // CModel* createBatteryModel(const char* filename,const int& life,const int& bonus,const float& range);
    //CSound* createSound();
//,const std::string&
    static CSpeech* createSpeech(const std::string& );

// TODO see lesquels supprimer
    irr::f32 _upperProgress;


    CStaticBattery* getNextTarget();

    float getUpperProgression() const;


//CSinglePlayerState*

    //bool init(CSinglePlayerState* state  );






//    CMissile* addMissile(const char* model);
    //void updatePlayerProgress(const float& playerProgress);

// TODO pvr le modifier depuis LUA
    irr::core::rectf _clippingPlane;

    //void draw();const float& playerAdv,
    //, CSinglePlayerState* _state
    void update( const TTimer::TimeType&);
    void checkCollisions();




protected:
    //void UpdatePlayer(CPlayer *player);
    void DrawLeftHUD(const core::position2di& upperLeft);
    void DrawRightHUD(const core::position2di& upperLeft);
    void drawExplosions();
    void GUI_CreatePauseMenu();
    void GUI_CreateGameOverMenu();
    void GUI_CreateEditorTab();


    irr::gui::IGUITab* _editorTab;

    //inline CGraphicalLevel& getLevelManager() {return *_levelMgr;};
    boost::scoped_ptr<CGraphicalLevel> _graphicalLevel;

//    typedef std::list<std::string> TLevels;
//    TLevels _levels;

//const TTimeUnit&
    typedef void (CSinglePlayerState::*TUpdateFunction)();
    std::array<TUpdateFunction,NPlayState::Count> _updateFunctions;
    //irr::video::ITexture* mTextures[NTexture::Count];


    //std::vector<std::string> _levels;

};

#endif
