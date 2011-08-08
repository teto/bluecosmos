/**
* \file state.h
**/

#ifndef _IIRRLICHTGAMESTATE_HPP_INCLUDED
#define _IIRRLICHTGAMESTATE_HPP_INCLUDED


#include <irrlicht.h>
#include "IGameState.hpp"
//#include "game_engine.hpp"
#include "../game_engine.hpp"
#include <boost/enable_shared_from_this.hpp>

//class EffectHandler;

class IGameState  :
public IGameState,
public irr::IEventReceiver,
public boost::enable_shared_from_this<IGameState>
{
public:
    //irr::gui::IGUIElement* _rootElement;

    void remove();



    IGameState(const std::string& name) : IGameState(name)
    {}

	//virtual bool init(CGameEngine * engine) { return IGameState<CGameEngine>(engine); };
    virtual bool OnEvent(const irr::SEvent& event) = 0;
    // TODO utiliser
    //virtual bool onEvent(const irr::SGUIEvent& event) = 0;


    inline
    irr::gui::IGUIEnvironment* gui() {return engine()->guienv;};

    inline
    irr::scene::ISceneManager* scene() {return engine()->smgr;};

    inline
    EffectHandler* effect() { return engine()->_postProcessingEffect; };

    // Irrlicht variables;
    //irr::scene::ISceneManager* _scene;
    //ISceneNode* _dummy;

};

///
struct NullDeleter
{
    void operator ()(IGameState*& Ptr) const
    {
        _INFO << "Destruction";
        //delete Ptr;
    }
};



#endif
