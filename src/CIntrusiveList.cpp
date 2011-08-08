#include "CIntrusiveList.hpp"
#include "entities/CStaticBattery.hpp"


// TODO rempalcer par  std::forward_list

CIntrusiveList::CIntrusiveList() : _root(0)
{
    //ctor
}

CIntrusiveList::~CIntrusiveList()
{
    //dtor
}

//
//void
//CIntrusiveList::push_back(CStaticBattery* battery){
//
//
//    battery->_next = 0;
//    battery->_previous = 0;
//}

CStaticBattery*
CIntrusiveList::pop_front() {
    // if no element
    if( empty() )  return 0;

    CStaticBattery* temp = _root;


    _root = _root->_next ;
    if(_root){
        _root->_previous = 0;
    }

    temp->_next = 0;
    temp->_previous = 0;
    return temp;
}


void
CIntrusiveList::push_front(CStaticBattery* battery){

    //
    if(_root){
        battery->_next = _root;
        _root->_previous = battery;
    }


    battery->_previous = 0;
    _root = battery;

}


void
CIntrusiveList::clear(){

    CStaticBattery* current = 0;// front();
    //CStaticBattery* del = 0;

    while( (current = pop_front()) != 0){
//
//        del = current;
//        current = current->_next;
        delete current;
    }
//    battery = 0;

}


void
CIntrusiveList::print(){


    //
}



void
CIntrusiveList::remove(CStaticBattery* battery){

    CStaticBattery* previous = battery->_previous;
    CStaticBattery* next     = battery->_next;

//    if(battery == _root){
//        pop_front();
//    }

    // If previous == 0 than battery is root
    if(previous){
        previous->_next = next;
    }
    else {
        _root = next;
    }


    if(next){
        next->_previous = previous;
    }

    battery->_next      = 0;
    battery->_previous  = 0;
}
