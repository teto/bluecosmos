#include "IStateManager.hpp"
#include "IGameState.hpp"
#include "IIrrlichtGameState.hpp"
#include "../game_engine.hpp"
#include <fusion/logging/ILogger.hpp>
#include <algorithm>

///// Store upon the previous one and init state



/// Store upon the previous one and init state
bool
IStateManager::PushState(TGameStatePtr state){

    //Assert(state);
    //if(!state){

    BOOST_ASSERT(state != 0);


    // Save/backup top of the pile
    TGameStatePtr topStack = 0;

    _states.push_back( state );

    if(!state->Init()){
        //
        _states.remove(state);
        return false;
    }


    return false;
}

// addToDeletionQueue
bool
IStateManager::RemoveState(TGameStatePtr state){

    // Remove state
    //_states.remove( state );

    TStatesMap::iterator it = std::find( _states.begin(), _states.end(),state );

    if(it == _states.end() ){
        _WARNING << "Could not remove this state: not found";
        return false;
    }

    _states.erase(it);

    // if state ok
    _INFO   << "Clean up of previous state '"
            << state->getName()
            << "' achieved";
    //const std::string& stateName =  _states.top()->getName();
    //std::cout << "state name" << stateName;



    // if
    if( !isStackEmpty() ){
        // activate top one
        _states.back()->OnActivation();
    }

    //delete state
    return true;

}

//TGameStatePtr state
// = 0
bool
IStateManager::PopState(){

    //

    if( _states.empty() ){
        return false;
    }

    return RemoveState( _states.back() );

}



// Utiliser des try and catch
/// \function ChangeState()
/// Clean previous state and load the new one
bool
IStateManager::ChangeState(TGameStatePtr state,const std::string& desc){

    //Assert(state);
//state
    //Log(ELL_INFORMATION) << "Changing state";
    _INFO << "Changing state";

    /// Clean Up current state
    PopState();

    /// Store and init the new state
    //Log("Initializing ...");
    //Log(ELL_INFORMATION) << "Initializing " << desc << "...";

    /// If good ( otherwise -> error )
    if(PushState(state)){
      //  Log(ELL_INFORMATION) << "State initialized";
        _INFO << "State initialized";
        return true;
    }
    else{
        _INFO << "An error occured during the initialization !";
        return false;
    }
}


/// \function CleanUp()
void
IStateManager::CleanUp(){

    /// Loop ends when states stack empty
    while(PopState()) {  }

    _INFO << "Clean-up of the engine achieved";

}
