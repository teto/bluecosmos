/**
* \file intro.cpp
**/
#include "CTransitionState.hpp"
#include "CMenuState.hpp"
#include "../game_engine.hpp"
#include <algorithm>
#include "../utils/CFadingImage.hpp"

using namespace irr;
using namespace core;

//! Constructor
//"images/bluecosmos.png"
// Passer la position du sprite dans le constructor
CTransitionState::CTransitionState(
const std::string& description,const std::string& filename
) :
//TGameState(description),
_img(0)
{
    _filename = filename;
}


CTransitionState::~CTransitionState(){

}

//void
//CTransitionState::ChangeState()
//{
//    engine()->ChangeState( new CMenuState(),"Transition to menu");
//    //_INFO << "false update";
//}

/**** Function Init() ****/
void
CTransitionState::init(){


    // Hide Cursor
    engine()->showCursor(false);
    //device->getCursorControl()->setVisible(false);
// TODO definir la position.c_str()
//irr::core::dimension2du temp = game->getCenteredPositionForRectangle(logo->getOriginalSize());
    irr::video::ITexture* logo = engine()->driver()->getTexture(_filename.c_str() );

    _img.reset( new CFadingImage(logo) );
    _img->_position = engine()->getCenteredPosition(logo->getOriginalSize());

    _INFO << "position" <<     _img->_position.X << "/" <<     _img->_position.Y;

    _img->addFading(2000,irr::video::SColor(255,255,255,255))
         .addFading(10000,irr::video::SColor(0,255,255,255) );
// != 0
    //return (_img);
}



bool
CTransitionState::OnEvent(const SEvent& event){

//    CGameEngine::getInstance()->ChangeState()
    if(event.EventType == EET_KEY_INPUT_EVENT){

        _INFO << "Key touched ";
        //this->remove();
        popThisState();
    }
    return true;
}


/**** Function Update() ****/
void
CTransitionState::Update(){

    if(!_img->update(engine()->getElapsedTime())){
        // changer d'etat
        //this->remove();
        popThisState();
    }

};



/**** Function Draw() ****/
void
CTransitionState::Draw(){

    //_INFO << "valeur d'alpha" << _img->_alpha;
    _img->draw( engine()->driver() );

}
