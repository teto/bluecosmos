/**
* \file single.h
**/
#ifndef CustomEvent_HPP_INCLUDED
#define CustomEvent_HPP_INCLUDED


//#include "IGameState.hpp"
#include <irrlicht.h>
#include <list>
#include <string>
#include <vector>
#include <boost/tuple/tuple.hpp>
//#include "def.hpp"


namespace NStateEvent {
    enum EId {
        //ChangeState,
        PushState,      //!< Pushes state on top of stack
        PopState
        //,       //!< Let
        //EraseState      //!< Pops and erase state instance from map, compelling creation of a new instance later on
    };
}


/*
//EET_USER_EVENT
class ICustomEvent : public irr::SEvent
{

public:


// State ID

    ICustomEvent(const NStateEvent::EId& id)
    //: irr::SEvent::EventType(irr::EET_USER_EVENT)
    //,UserData1(id),UserData2(0)
    {
        EventType = irr::EET_USER_EVENT;
        UserData1 = id;
    }
};



class CStateEvent : public ICustomEvent {


    CStateEvent(const EId& id,IGameState* caller,IGameState*) : CCustomEvent(id),
    {

    };

    IGameState* Caller;
    IGameState* NextState;

};

//device->postEventFromUser(event);
*/

#endif
