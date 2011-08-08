/**
* \file state.h
**/

#ifndef _ISTATEMANAGER_HPP_INCLUDED
#define _ISTATEMANAGER_HPP_INCLUDED

//template<typename ENGINE>//,typename EventReceiver> class IGameState<>


#include <boost/shared_ptr.hpp>
#include <stack>
#include <map>
#include "IGameState.hpp"
#include "../def.hpp"
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_deque.hpp>
//#include "IGameState.hpp"

//class IGameState;


class IStateManager
{

protected:

    //TGameStatePtr boost::shared_ptr<
    //typedef std::map<TGameStateId, IBasicGameState* > TStatesMap;
    typedef std::stack<IBasicGameState* > TStatesStack;
    TStatesStack _states;
    //TStatesMap _stateCollection;

//irr::SUserEvent

    typedef std::vector<TGameStateEvent> TEventStack;
    TEventStack _events;

    //TGameStatePtr _currentState;
    bool pushState(TGameStateId id);

public:
    IBasicGameState* getCurrentState() { return _states.top() ; };

    void pushEvent(const NStateEvent::EId&,const TGameStateId&);

//debug function
    void printStates() const;


    int getStackSize() const { return _states.size(); };
    bool isStackEmpty() const { return _states.empty(); };
    IStateManager();

    /*inline bool ChangeState(IGameState* state,const std::string& desc){
        TGameStatePtr ptr(state);
        return ChangeState(state,desc);
    }*/

    // TODO ppouvoir le remettre ici
    //virtual bool InitState(TGameStatePtr state) = 0;
    void synchronize();

    virtual void CleanUp() = 0;




};

#endif
