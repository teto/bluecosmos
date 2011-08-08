#include "IGameState.hpp"
#include "../game_engine.hpp"
#include <xeffects/XEffects.h>


namespace NStateId {
const char Options[]      = "Options";
const char Transition[]   = "Transition";
const char Solo[]         = "Solo";
const char Score[]        = "Score";
const char MainMenu[]     = "Main menu";

}

IBasicGameState::IBasicGameState() :
//_name(name),
_engine( CGameEngine::instance() ),
_rootTab(0),
_smgr( 0 ),
_postProcessingHandler(0)
// tous les params
//_ownSceneManager(true/false),

{
    _smgr = engine()->scene();
    /////////////////////////////////////
    /////  Setup Post-processing pipeline
    /////////////////////////////////////

    _postProcessingHandler = new EffectHandler(
                                               engine()->device()
//                                               engine()->driver()->getScreenSize(),
//                                               false,
//                                               false
                                               );

}

//
//IStateManager*
//IGameState::getStateManager() const {
//    return _engine;
//};

void
IBasicGameState::pushState(TGameStateId stateId) const {

    getStateManager()->pushEvent(NStateEvent::PushState, stateId );
    //getStateManager()->pushEvent(NStateEvent::Hold, getID() );
    //engine()->pushEvent(NStateEvent::PushState, NStateId::Options );
}


void
IBasicGameState::popThisState() const {

    getStateManager()->pushEvent(NStateEvent::PopState, getID() );
    //engine()->pushEvent(NStateEvent::PushState, NStateId::Options );
}




irr::scene::ISceneManager*
IBasicGameState::scene() const {
    return _smgr;
    //return _engine.scene();
};


IStateManager*
IBasicGameState::getStateManager() const {
    return engine();
}


irr::gui::IGUIEnvironment*
IBasicGameState::gui() {
    return _engine.gui();
};


EffectHandler*
IBasicGameState::postProcessingFramework() {
    // PostProcessingFramework()
    return _postProcessingHandler;
    //_postProcessingEffect;
};


// TEMPORAIRE
//void
//IGameState::remove()
//{
//    //TGameStatePtr temp( this,NullDeleter() );
//    //TGameStatePtr temp( shared_from_this()  );
//
//    //_INFO << "REMOVE BEGIN" << temp.use_count();
//    getStateManager()->PopState( this );
//
//}
