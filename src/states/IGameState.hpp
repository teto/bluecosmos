/**
* \file state.h
**/

#ifndef _IGAMESTATE_HPP_INCLUDED
#define _IGAMESTATE_HPP_INCLUDED

#include <string>
#include <irrlicht.h>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "../def.hpp"
#include <boost/shared_ptr.hpp>
//#include "../game_engine.hpp"
//#define ENGINE CGameEngine

class IStateManager;
class CGameEngine;
class EffectHandler;

//typedef boost::shared_ptr<CGameEngine> TEnginePtr;

namespace NStateConfig {
enum  EId {
CopyScene,
MustBeUnique

};

}

//namespace {

namespace NStateId {
extern const char Options[];
extern const char Transition[];
extern const char Solo[];
extern const char Score[];
//extern const char MainMenu[] ="menu";
extern const char MainMenu[];// = "menu";

}

//}
//UserData1


/**
we can now use  "shared_from_this()" to get a shared_ptr of "this"
**/

class IBasicGameState
{
private:
    //IStateManager* getStateManager() const { return static_cast<IStateManager*>(_engine); };
    IStateManager* getStateManager() const;

protected:
    CGameEngine& _engine;
    irr::gui::IGUIEnvironment* gui();
    irr::scene::ISceneManager* scene() const;


public:
    virtual bool OnEvent(const irr::SEvent& event) = 0;
    // TODO utiliser
    //virtual bool onEvent(const irr::SGUIEvent& event) = 0;
    //addPostProcessingEffect();

    virtual ~IBasicGameState() {};

    EffectHandler* postProcessingFramework();

    inline CGameEngine* engine() const {return &_engine;};

    //inline EffectHandler* effect() { return _engine->_postProcessingEffect; };

    //static getID()

    /// \return true if must be deleted from the
    //virtual void CleanUp() = 0;


    void pushState(TGameStateId) const;

    void replaceThisState(TGameStateId id) const {
        popThisState();
        pushState( id) ;
    }
    void popThisState() const;

    virtual void onResume() {};
    virtual void onHold() {};

//    virtual void onPop() {};
//    virtual void onPush() {};

// TODO supprimer a terme

	virtual void Draw() = 0;
	virtual void Update() = 0;

    virtual bool deleteOnPopping() const = 0;
    virtual TGameStateId getID() const = 0;

protected:
    IBasicGameState();

private:
    irr::gui::IGUITab* _rootTab;
    irr::scene::ISceneManager* _smgr;
    EffectHandler* _postProcessingHandler;
    //bool _deleteOnEnd;

    //IBasicGameState(const std::string&);

};






//,bool copyScene
template<TGameStateId ID,bool DELETE_ON_POPPING>
class IGameState :
public IBasicGameState ,
public irr::IEventReceiver
//public boost::enable_shared_from_this<IGameState>
{




protected:



public:
// Plus besoin de le passer apres comme ca
// mm pas besoin d'en faire une instance unique ^^
    IGameState() : IBasicGameState() {}
    virtual ~IGameState(){};    //!< Compel to inherit fromthis class



	//virtual void CleanUp() = 0;
//    virtual bool OnEvent(const irr::SEvent& event) = 0;
    // equivalents de Onpause/Onresume
//    virtual void onResume() {};
//    virtual void onHold() {};
//	virtual void Draw() = 0;
//	virtual void Update() = 0;

    bool deleteOnPopping() const { return DELETE_ON_POPPING;}
    TGameStateId getID() const { return ID;}



private:
    //std::string _name;

};


//typedef IGameState<CGameEngine> TGameState;
// N'a pas de sens ?
typedef IBasicGameState TGameState;
//"Options"

#endif
