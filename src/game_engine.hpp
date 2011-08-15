/**
* \file GameEngine.h
*/
#ifndef GAME_ENGINE_HPP_INCLUDED
#define GAME_ENGINE_HPP_INCLUDED

//#define _IRR_STATIC_LIB_
#include <irrlicht.h>
#include <fusion/logging/ILogger.hpp>
//#include <fusion/core/CSingleton.hpp>
#include <fusion/utilities/CBitset.hpp>
#include <map>
#include <boost/logic/tribool.hpp>  // header only
#include <stack> //header only
#include <bitset>
#include <fusion/scripting/CLuaThread.hpp>
#include <fusion/core/CSingleton.hpp>
#include <boost/bimap.hpp>
#include "utils/CSpriteManager.hpp"

#include "IGameEngine.hpp"
#include "entities/player.hpp"
#include "states/IStateManager.hpp"
#include "config.hpp"
#include "startup_config.hpp"
#include "audio/SAudioParameters.hpp"

namespace bbi = boost::bimaps;


//#include "observer/IMessageManager.hpp"
namespace irr {
    namespace gui {
        class IGUIConsole;
    }
    //class SIrrlichtCreationParameters;
}

namespace audio {
    class CFModExDriver;
    //class ISoundManager;
    class IAudioDriver;
}

class IObserver;
class ISoundManager;
class CParticleManager;

class CDialogState;
class EffectHandler;
class CEventManager;

namespace input {
    class CInputManager;
}
//class SIngameConfig;
//class SAudioParameters;

typedef irr::video::E_DRIVER_TYPE TVideoDriverId;


// std::tr1::bind pour pouvoir passer un nom de fichier
typedef bool (*TLoadConfigFromFileFunction)(irr::SIrrlichtCreationParameters&,SIngameConfig&,audio::SAudioParameters&);

fus::NLogLevel::EId convertIrrlichtLogLevel( const  irr::ELOG_LEVEL& );
irr::ELOG_LEVEL convertFusionLogLevel( const fus::NLogLevel::EId& );

/// Handle successive states
class CGameEngine :
public IGameEngine,
public irr::IEventReceiver,
public IStateManager,
public fus::CSingleton<CGameEngine>
//public CMessageManager,
//public IObserver
{
    friend class CSingleton<CGameEngine>;

    irr::gui::IGUITab* _messageBoxesTab;




public:

    irr::SIrrlichtCreationParameters EngineConfig;
    //std::tr1::
    audio::SAudioParameters AudioConfig;
    SIngameConfig GameConfig;

    bool isCursorShown() const;

    void popupMessage(const wchar_t* shortDescription,const wchar_t* longDescription);
    void popupMessage(const wchar_t* shortDescription,const std::string& longDescription);

    //CDialogState*  startDialog(dialog);
    bool bindEverythingToLua();

    //bool startScript(const char* scriptFilename);

    typedef bbi::bimap< int , std::wstring > TBiMap;
    typedef TBiMap::value_type TKeyAssociation;

    static TBiMap _videoDrivers;

    //void bindLevelHandlerToLua(CGraphicalLevel* levelMgr);

    // 'cos it's an observer
    //void handleMessage ( const CMessage& message );

//    void shakeCamera();
    void showCursor(const bool& show) {
        _device->getCursorControl()->setVisible(show);
    };

    void setLogLevel( const fus::NLogLevel::EId& );


    bool getVideoDriverFromName(const std::wstring& name,TVideoDriverId& id);
    bool addVideoDriverIfSupported( const std::wstring& name, const TVideoDriverId& id );

    typedef boost::shared_ptr<CSpriteManager> TSpriteManager;
    static TSpriteManager _spriteManager;


    std::map<irr::core::stringw,irr::core::stringw> _BC_DEBUGData;
    irr::gui::IGUIStaticText* _debugDataElement;

irr::scene::ICameraSceneNode* _fpsCamera;
    //boost::scoped_ptr<irr::scene::ICameraSceneNode>

//_cameras.top();
//pushCam(ICamera
//popCam

    // get active camera
    irr::scene::ICameraSceneNode*
    getCamera(){
        return scene()->getActiveCamera();
    };

    //void setCamera(irr::scene::ICameraSceneNode* camera);

    //std::map<> _camera;

    irr::scene::ICameraSceneNode* switchFreeFlightCamera();

    // Pr le debug via lua
    void setCamPos(const float& x,const float& y,const float& z);
    void setCamTarget(const float& x,const float& y,const float& z);

    void closeIrrlichtDevice();
    bool enableJoysticks();
    //void ResetConfig();

    irr::gui::IGUIFont* getFont() { return _gui->getSkin()->getFont();}

    bool OnEvent(const irr::SEvent& event);


//    void pushStateEvent(const NStateEvent::EId&,const TGameStateId&);

    inline irr::IrrlichtDevice* device() { return _device; };
    inline irr::video::IVideoDriver* driver() { return _driver; };
    inline irr::scene::ISceneManager* scene() { return _smgr; };
    inline irr::gui::IGUIEnvironment* gui() { return _gui; };
    //inline irr::gui::IGUIEnvironment* postProcessingFramework() { return _postProcessingEffect; };

    input::CInputManager& getInputManager() { return *_inputManager;};


    void enableGUIAutoScale(irr::gui::IGUIElement*);
    bool createPlayer();

    // pr positionner de maniere centree
//    irr::core::dimension2du getAbsoluteDimension(const float&,const float&) const;// temp = game->driver->getScreenSize();
    inline const irr::core::dimension2du& getScreenSize () const {
        return _driver->getScreenSize ();
    }

template<typename T>
irr::core::vector2d<T>
getAbsoluteDimension(const float& x,const float& y) const {

//driver->
    return irr::core::vector2d<T>(x*getScreenSize().Width,y*getScreenSize().Height);
}

    CPlayer* getPlayer(const int& i = 0) { return _player.get(); };


    irr::core::recti getAbsoluteRectangle(const float& x,const float& y, const float& x2,const float& y2) const;
    //irr::core::rect<irr::s32> getAbsoluteRectangle(const float& x,const float& y, const float& w,const float& h) const;


    irr::core::position2di getCenteredPosition(const irr::core::dimension2du&) const;
   // bool SwitchBit(const NBit::EId& bit,blo::tribool enable = blo::indeterminate);

//    const std::string& getVersion() const { return conf::_GAME_VERSION; };

    bool setFont(const std::string& fontPath);

    void TakeScreenshot(const std::wstring& path = L"screenshot");


    //bool RunScript(const char* filename);
	void Quit();

	void Update();
	void Flush();
	void CleanUp();


    //int Run(TLoadConfigFromFileFunction fn);
    //int Run(const TEngineParameters&,const SIngameConfig&,const SAudioParameters&);
    int Run();

    TTimer::TimeType getElapsedTime() const;



    void
    updateDebugData(const irr::core::stringw& field,const irr::core::stringw& description){
        _BC_DEBUGData[field] = description;
    }


    void initializeScript();



    typedef boost::scoped_ptr<CParticleManager> TParticleManager;


public:
    //static TBiMap _videoDrivers;
    typedef audio::IAudioDriver TSoundManager;
    static void getAvailableVideoDriverList(std::vector<std::wstring>& list);



    static TParticleManager _particleManager;

    static inline CParticleManager* getParticleManager() { return _particleManager.get(); };
    static inline CSpriteManager* getSpriteManager() { return _spriteManager.get(); };
    inline TSoundManager* getSoundManager() { return _soundManager; };

    TPlayerPtr _player;
    //boost::shared_ptr<CEventManager> mEventManager;
    //boost::shared_ptr<CInputManager> _inputManager;
    input::CInputManager* _inputManager;


private:

    TSoundManager* _soundManager;

    irr::gui::IGUIConsole* _console;
    irr::video::IVideoDriver*    _driver;

    // TODO a la limite on pourrait le supprimer ca
    irr::scene::ISceneManager*   _smgr;
    irr::gui::IGUIEnvironment* _gui;
    irr::IrrlichtDevice *_device;
    CGameEngine();
    ~CGameEngine();

    void logDebugInformations();


    TTimer::TimeType mElapsedTime;
    TTimer::TimeType mLastTime;


//const irr::video::E_DRIVER_TYPE& = irr::video::EDT_OPENGL,blo::tribool = blo::indeterminate,blo::tribool = blo::indeterminate
//irr::SIrrlichtCreationParameters& parameters
    bool createIrrlichtDevice();

    // TODO a passer en private
    bool InitEngine();
//    bool InitEngine(const TEngineParameters&,const SIngameConfig&,const SAudioParameters&);


// TODO supprimer celui-ci
    //bool switchConsoleState();
    bool eventToMainHandler(const  irr::SEvent& event);

//fus::ELogLevel
    //static fus::NLogLevel::EId _irrlichtLogLevelsMap[irr::ELL_NONE + 1];
};



#endif
