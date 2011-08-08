/**
* \file options.cpp
*
*/

#include "CErrorState.hpp"
#include "../game_engine.hpp"
#include "../config.hpp"
//#include <fusion/macros.hpp>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;

//IGUIElement* CErrorState::
//getButtonFrom IGUIElement* elem = _tabControl->getElementFromId(indexOfFocusedElement + NGuiIds::Count,true);

//const wchar_t*
CErrorState::CErrorState(const wchar_t* caption, const wchar_t* text) :
TGameState("Messagebox state"),
_messageBox(0),
_editBox(0)
//,_pos(pos)
{
// EMBF_OK
    _messageBox = gui()->addMessageBox(caption, text );
    //_messageBox = gui()->addMessageBox(caption.c_str(),text.c_str());
}

CErrorState::~CErrorState(){
    _INFO << "errorState DELETED";
    //_messageBox->remove();
    //scene()->addToDeletionQueue(_messageBox);//->remove();
}


/**** Function HandleEvents() ****/
// Quand je clique sur le bouton, je supprime cet etat
bool
CErrorState::OnEvent(const irr::SEvent& event){



	if( event.EventType == EET_GUI_EVENT)
	{
	    //event.GUIEvent.Caller->getID();
		//s32 id = event.GUIEvent.Caller->getID();
        //_INFO << "GUI EVENT:" << event.GUIEvent.EventType << "/" << EGET_MESSAGEBOX_OK;
//EGET_BUTTON_CLICKED
		if(event.GUIEvent.EventType == EGET_MESSAGEBOX_OK){

		    _INFO << "messageboxs closing";
//            switch(id){
//
//                default:
                    this->remove();
                    _INFO << "ENd of removing";
                    return true;
                    //engine()->RemoveState(this);
//                    break;
//            };
        }


	}


    return false;


}




void
CErrorState::onResume(){
    engine()->showCursor(true);
}

/**** Function Init() ****/
void
CErrorState::init(){

    //indexOfFocusedElement = -1;
    //TGameState::Init(game);

    /// Show again the cursor
    engine()->showCursor(true);

    /// Create initial menu

    //_tabControl->setRelativePositionProportional ( core::rectf(0,0,1.f,0.9f));



    //return true;
}



/**** Function Update() ****/
void
CErrorState::Update(){


}


/// \function Draw()
void
CErrorState::Draw(){

    scene()->drawAll();
    _messageBox->draw();

}
