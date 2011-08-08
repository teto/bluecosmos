/**
* \file state.h
**/

#ifndef _ISTATEMANAGER_HPP_INCLUDED
#define _ISTATEMANAGER_HPP_INCLUDED

//template<typename ENGINE>//,typename EventReceiver> class IGameState<>


#include <boost/shared_ptr.hpp>
#include <stack>
#include "IGameState.hpp"
#include "../def.hpp"
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_deque.hpp>
//#include "IIrrlichtGameState.hpp"

//class IGameState;


class IStateManager
{
public:
    //typedef IGameState TGameState;
    //typedef boost::shared_ptr<TGameState> TGameStatePtr;

protected:

// TODO remplacer par un  boost::ptr_list
    typedef std::list<TGameStatePtr> TStatesMap;
    TStatesMap _states;
    //TStatesMap _statesToAdd;
    //TStatesMap _to;

    //std::list<TGameStatePtr> _bufferedStates;

    TGameStatePtr _currentState;

    //IGameState::TEnginePtr _engine;

public:


    bool ChangeState(TGameStatePtr state,const std::string& );

    /*inline bool ChangeState(IGameState* state,const std::string& desc){
        TGameStatePtr ptr(state);
        return ChangeState(state,desc);
    }*/

    // TODO ppouvoir le remettre ici
    //virtual bool InitState(TGameStatePtr state) = 0;

    bool PushState(TGameStatePtr state);

    /*inline bool PushState(IGameState* state){
        TGameStatePtr ptr(state);
        return PushState(ptr);
    }*/
    bool RemoveState(TGameStatePtr state);

    bool PopState();

    inline bool isStackEmpty() { return _states.empty(); };

    inline TGameStatePtr getCurrentState() {return _states.back();};

    virtual void CleanUp() = 0;




};

#endif
