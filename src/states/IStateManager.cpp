#include "IStateManager.hpp"
#include "IGameState.hpp"
#include "COptionsState.hpp"
#include "CTransitionState.hpp"
#include "CMenuState.hpp"
#include "CScoreState.hpp"
#include "../fightingState/CSinglePlayerState.hpp"
#include "../game_engine.hpp"
#include <fusion/logging/ILogger.hpp>
#include <algorithm>

///// Store upon the previous one and init state

IStateManager::IStateManager()
//_numberOfStatesToPop(0)
//_stateRemoved(false)
//,_currentState(0)
{

}

/// Store upon the previous one and init state
bool
IStateManager::pushState(TGameStateId id){

    IBasicGameState* state = 0;
    //retrieveState(it->UserData2);

/*
    TStatesMap::iterator it = _stateCollection.find( id );
    // TOdO si j'utilise de sinsert je recupere l'iterateur ?
    if(it ==  _stateCollection.end() ){
*/
        if( std::strcmp(id, NStateId::Options) == 0 ) {

            // TOdo mettre le rect dans la conf ?
            state = new COptionState( core::rectf(0.2f,0.2f,0.8f,0.8f) );
        }
        // TODO remplacer par un systeme avec des shaders
        else if( std::strcmp(id, NStateId::Transition) == 0 ) {

            state = new CTransitionState("Introduction","images/bluecosmos.png");
        }
        else if( std::strcmp(id, NStateId::Solo) == 0 ) {
            state = new CSinglePlayerState();
        }
        else if( std::strcmp(id, NStateId::MainMenu) == 0) {
            state = new CMenuState();
        }
        else {

            _LOG_ERROR << "Could not instanciate state  [" << id << "]";
            return false;
        }
//}


    //
    //if( std::strcmp(id,NStateId::options)
// done     // TODO faire onHold de l'etat en dessous sauf si cului -ci a deja le flag onHold()
    //onHold()

    _states.push( state );

    //state->onPush();
    return true;
}


void
IStateManager::printStates() const {

    //_INFO << _states;

}







// TODO getNumberOfStates
// Traite les evenements
void
IStateManager::synchronize(){

// TODO gerer les onHold && resume retrieveState

    bool shouldCallOnHold = true;
    bool shouldCallOnResume = true;

    IBasicGameState* backupedState = 0;
    if(!isStackEmpty()) {
        backupedState = _states.top();
    }

    //getCurrentState();

    // Maintenant faut ajouter les states
    //BOOST_FOREACH(TGameStatePtr& state, _statesToAdd){
    for(TEventStack::iterator it( _events.begin()), end(_events.end() ); it != end; ++it){

        const NStateEvent::EId type = it->first;
        const TGameStateId stateId = it->second;

        switch (type)
        {
            case NStateEvent::PushState:
                _INFO <<  "Trying to push state [" << stateId << "]";
                //try {} catch(){}
                /*


                IBasicGameState* state = retrieveState(it->UserData2);
                _states.push_back(state);
                state->onPushing()
                */
//                if(alreadyPushedOneStateOnStack == false){
//
//                    alreadyPushedOneStateOnStack = true;

                // s'il existe en etat en dessous on active son onHold();
                if(!isStackEmpty()){
                    _states.top()->onHold();
                }
                pushState(stateId);
                //}
                break;

            //case NStateEvent::EraseState:
//
//                TStatesMap::iterator it = _stateCollection.find( it->UserData2 );
//                if(it !=  _stateCollection.end() ){
//                    _stateCollection.erase(it);
//                }
                //break;

            //it->UserData2
            case NStateEvent::PopState:
                _INFO <<  "Trying to pop state [" << stateId << "]";
                //BOOST_ASSERT()
                if (isStackEmpty() || (_states.top()->getID() != stateId ) ) {

                    _LOG_WARNING << " which is not at the top of stack";

                }
                else {
                    _INFO << "Popping element";
                    //state->onPop();
                    delete _states.top();
                    _states.pop();
                    if(!isStackEmpty()){
                        _states.top()->onResume();
                    }
//                    if( deleteOnPopping() ){
//                        // then remove it from map
//                        // TODO
//                    }

                }
                break;


            default:
                break;
        }


    }

    _events.clear();

}




void
IStateManager::pushEvent(const NStateEvent::EId& eventType,const TGameStateId& userData) {

    _events.push_back( std::make_pair(eventType,userData) );
}





/// \function CleanUp()
void
IStateManager::CleanUp(){

    /// Loop ends when states stack empty
    //while(PopState()) {  }

    //_currentState.reset();

    _INFO << "Clean-up of the engine achieved";

}
#if 0
// TODO not interessant
// addToDeletionQueue
bool
IStateManager::RemoveState(TGameStatePtr& state){

    // Remove state
    //_states.remove( state );

    TStatesMap::iterator it = std::find( _states.begin(), _states.end(),state );

    if(it == _states.end() ){
        _LOG_WARNING << "Could not remove this state: not found";
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
#endif
