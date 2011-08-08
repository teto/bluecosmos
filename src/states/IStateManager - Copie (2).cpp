#include "IStateManager.hpp"
#include "IGameState.hpp"
#include "IIrrlichtGameState.hpp"
#include "../game_engine.hpp"
#include <fusion/logging/ILogger.hpp>
#include <algorithm>

///// Store upon the previous one and init state

IStateManager::IStateManager() :
//_numberOfStatesToPop(0)
_stateRemoved(false)
//,_currentState(0)
{

}

/// Store upon the previous one and init state
bool
IStateManager::PushState(TGameStatePtr& state){

    //Assert(state);
    //if(!state){

    BOOST_ASSERT(state != 0);


    // Save/backup top of the pile
    //TGameStatePtr topStack = 0;



    //if(!state->Init()){
        //
        _statesToAdd.push_back( state );
        //_states.remove(state);
        return false;
    //}


    return false;
}

// TODO not interessant
// addToDeletionQueue
bool
IStateManager::RemoveState(TGameStatePtr& state){

    // Remove state
    //_states.remove( state );

    TStatesMap::iterator it = std::find( _states.begin(), _states.end(),state );

    if(it == _states.end() ){
        _WARNING << "Could not remove this state: not found";
        return false;
    }



    // if state ok
    _INFO   << "Clean up of previous state '"
            << state->getName()
            << "' achieved";

    it = _states.erase(it);
    //const std::string& stateName =  _states.top()->getName();
    //std::cout << "state name" << stateName;
    _stateRemoved = true;
    //delete state
    return true;
}


// TODO getNumberOfStates

void
IStateManager::Synchronize(){


//    int temp = _numberOfStatesToPop;
    //int numberOf = (int) _statesToAdd.size();

    // Pop states until temp negative or stack empty
//    while( (temp > 0) ){
//
//        if(isStackEmpty()){
//            break;
//        }
//        --temp;
//    }
    //_INFO << "stack size" << getStackSize();

    int numberOfAddedStates = 0;
    bool stateAdded = false;

    // Maintenant faut ajouter les states
    BOOST_FOREACH(TGameStatePtr& state, _statesToAdd){

        // On l'initialise puis on le met sur pause
        if(state->Init()){
            // s'il s'est correctement initialisé
            //alors je l'ajoute
            // resume(); resume()
            _states.push_back(state);

            //if(stateAdded){
            if(numberOfAddedStates > 0){
                _states.back()->onHold();
            }

            //stateAdded=true;
            ++numberOfAddedStates;
        }
        else {
            _WARNING << "Could not init state";
        }

    }

    // TODO: resume ou pas state
    if(!isStackEmpty()){

        _currentState = _states.back();
        //_currentState.reset( _states.back() );
        // && !stateAddded
        if( (_stateRemoved) && (numberOfAddedStates <= 0) ){
            _currentState->onResume();
        }
    }

    //reset
    //_numberOfStatesToPop = 0;
    _stateRemoved = false;
    _statesToAdd.clear();
}


//TGameStatePtr state
// = 0

bool
IStateManager::PopState(){

    if(!isStackEmpty()){
        RemoveState(  _states.back() );
    }


    return false;
    //return RemoveState( _states.back() );
}



// Utiliser des try and catch
/// \function ChangeState()
/// Clean previous state and load the new one
bool
IStateManager::ChangeState(TGameStatePtr& state,const std::string& desc){

    //Assert(state);
//state
    //Log(ELL_INFORMATION) << "Changing state";
    _INFO << "Changing state...";

    /// Clean Up current state
    PopState();

    //RemoveState();
    PushState(state);

    /// Store and init the new state
    //Log("Initializing ...");
    //Log(ELL_INFORMATION) << "Initializing " << desc << "...";

    /// If good ( otherwise -> error )
//    if(PushState(state)){
//      //  Log(ELL_INFORMATION) << "State initialized";
//        _INFO << "State initialized";
//        return true;
//    }
//    else{
//        _INFO << "An error occured during the initialization !";
//        return false;
//    }
    return true;
}


/// \function CleanUp()
void
IStateManager::CleanUp(){

    /// Loop ends when states stack empty
    while(PopState()) {  }

    _currentState.reset();

    _INFO << "Clean-up of the engine achieved";

}
