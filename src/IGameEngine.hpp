/**
* \file GameEngine.h
*/
#ifndef IGAMEENGINE_HPP_INCLUDED
#define IGAMEENGINE_HPP_INCLUDED

#include <fusion/logging/ILogger.hpp>
// supprimer suivant


#include <fusion/utilities/CBitset.hpp>
//#include "states/IGameState.hpp"
//
#include <map>
#include <boost/logic/tribool.hpp>  // header only
#include <stack> //header only
#include <bitset>
#include <fusion/scripting/CLuaThread.hpp>
#include <fusion/scripting/CLuaVM.hpp>
#include <boost/smart_ptr.hpp>
#include "def.hpp"
#include <irrlicht.h>

namespace blo = boost::logic;

/*
enum ERenderingMode {
Fill = GL_FILL,
Line = GL_LINE,
Point = GL_POINT,
FillWithLine
};
*/
// forward declaration
class CConfigManager;
class CGraphicalLevel;
class CDialogState;
class SIngameConfig;
class SAudioParameters;


typedef irr::SIrrlichtCreationParameters TEngineParameters;


namespace NBit {
enum EId {
Console,
WireFrame,
DebugData,
SetSize,
Fullscreen, // TOdo supprimer
VSync,      // aussi
Antialiasing,   // aussi
DisplayHitCircles,//aussi

FreeFlight,


BulletTime,
EnableDialogs,

Count
};
}


namespace NEngineState {
enum EId {
//Initializing,   // TODO renommer en reseting
Paused,
//Console,
Error,
Running,
Exiting,
Uninitialized
};

}



enum class EEngineState {
Paused,
Error,
Running,
Exiting,
Uninitialized
};



class IGameEngine
{

public:

    inline bool paused() const { return (_internalState == NEngineState::Paused);}

    bool SwitchBit(const NBit::EId& bit,blo::tribool enable = blo::indeterminate);



    virtual void TakeScreenshot(const std::wstring& path = L"screenshot") = 0;

// TODO to change
	virtual void Quit() = 0;

	virtual void Update() = 0;
	virtual void Flush() = 0;

//states

    virtual void showCursor(const bool& show) = 0;
    virtual bool isCursorShown() const = 0;


    //virtual bool Run(const TEngineParameters&,const SIngameConfig&,const SAudioParameters&) = 0;

    //virtual bool Run() = 0;

    //unsigned int
    //const &
    virtual irr::u32 getElapsedTime() const = 0;

    IGameEngine();
    ~IGameEngine();

//    bool InitEngine(TSharedConfigPtr& config);

    // ca ca devrait aller dans le CGameEngine
    TScriptingVM& getScriptingVM() { return _vm;};


protected:
    TScriptingVM _vm;
    bool getBoolean(const NBit::EId& id) const { return mBitSet[id];}
    NEngineState::EId _internalState;

private:
    typedef std::bitset<NBit::Count> TBitset;
    // TODO renommer en _running
    TBitset mBitSet;
    //bool _consoleState;
};



#endif
