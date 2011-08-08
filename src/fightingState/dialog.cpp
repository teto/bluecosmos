#include "CSinglePlayerState.hpp"
#include <cmath>
#include <irrlicht.h>
#include "../entities/player.hpp"
#include "../config.hpp"
#include "../game_engine.hpp"
//#include "../IGameConfig.hpp"
#include "../states/CMenuState.hpp"
#include "../states/COptionsState.hpp"
#include "../states/CScoreState.hpp"
#include "../states/CErrorState.hpp"
#include "../states/CTransitionState.hpp"
#include "../states/IdList.hpp"
#include "../utils/CParticleManager.hpp"
#include "../entities/IMultiModeTransformer.hpp"
#include <fusion/scripting/CLuaThread.hpp>
#include <fusion/scripting/CLuaVM.hpp>
#include <fusion/maths/macros.hpp>
#include <fusion/core/string.hpp>
#include "../CSpeech.hpp"
#include "../CSpeaker.hpp"


using namespace irr;


void
CSinglePlayerState::showMessage(CSpeaker* speaker, CSpeech* speech) {

    BOOST_ASSERT(speaker);
    BOOST_ASSERT(speech);

    //_dialog = std::make_pair(speaker,speech);



    changeState( NPlayState::Dialog );

//
//    std::wstring text = speaker.getName();
//        text += L":\n";
//        // then his/her speech
//
//
//        text += speech.getMessage();
//        font->draw(
//            text.c_str(),
//            core::recti(300,10,500,50),
//
//        );

    gui::IGUIStaticText* text = static_cast<gui::IGUIStaticText*>( _dialogTab->getElementFromId( NGuiIds::DialogText ) ) ;
    text->setText( speech->getMessage().c_str() );
    //text->setFont();
//setMinSize / setMaxSize
    //_dialogTab  text->getTextHeight();

    gui::IGUIImage* img = static_cast<gui::IGUIImage*>( _dialogTab->getElementFromId( NGuiIds::DialogImage ) ) ;
    img->setImage ( speaker->getTexture() );

    gui::IGUIListBox* answers = static_cast<gui::IGUIListBox*>( _dialogTab->getElementFromId( NGuiIds::DialogAnswers ) ) ;

    _answers->clear();
//CSpeech::TAnswersList
    BOOST_FOREACH( const CSpeech::TAnswer& answer, speech->_answers ){

//answer.first.c_str()
        answers->addItem( answer.get<0>().c_str() );
    }
    _answers->setSelected(0);

    enableMenu( _dialogTab, true );

    // -- We should finish by this
    //_script->yield(0);
    //return;
}





TPlayerReply
CSinglePlayerState::getUserReply() const {

//    if(!_script->resume() ){
//        _LOG_ERROR << "could not resume script";
//    }
    return _lastPlayerReply;
}




void
CSinglePlayerState::GUI_CreateDialogTab()  {

    /// CONFIG
    const int gap = 10;
    const int totalHeight = 400;
    const int textHeight = 200;
    const video::SColor textColor(255,255,255,255);
    const video::SColor backgroundColor(100,0,0,0);
    //const int gap = 10;


    irr::gui::IGUIEnvironment* gui = engine()->gui();

//
    // position2di
    //ENGINE->driver()->getViewPort().getWidth()
    //ENGINE->getScreenSize().Width
core::recti comprehensiveRect(  0,0, ENGINE->driver()->getViewPort().getWidth(), totalHeight );

    // "viewport in which we can draw"<<
    _INFO << "viewport in which we can draw" <<comprehensiveRect;

    _dialogTab = gui->addTab ( comprehensiveRect );
    //255
    _dialogTab->setBackgroundColor( backgroundColor );
    _dialogTab->setID( NGuiIds::DialogBox );
    _dialogTab->setDrawBackground(true);
    // speech


    //_PORTRAIT_DIMENSION
    //irr::core::recti  textRect( core::position2di(_PORTRAIT_SIZE.Width + 10, 0 ), core::dimension2du(comprehensiveRect -,250) );

    irr::core::recti  textRect( conf::_PORTRAIT_SIZE.Width + gap, gap , comprehensiveRect.getWidth() - gap , textHeight );
    //decal(rect,10,10);
    gui::IGUIStaticText* text = gui->addStaticText(L"test",textRect,false);
    text->setID( NGuiIds::DialogText );
    text->setOverrideColor ( textColor );

    // TODO


    //text->setParent(  );
    _dialogTab->addChild(text);


    //gui->addWindow (const core::rect< s32 > &rectangle, bool modal=false, const wchar_t *text=0, IGUIElement *parent=0, s32 id=-1);


    // speaker picture
    //texture->getOriginalSize()
    //core::dimension2di(100,50)
    irr::core::recti  srcRect( irr::core::position2di(gap,gap), conf::_PORTRAIT_SIZE );
    //irr::core::recti  textRect( _PORTRAIT_SIZE.Width + gap, 250 + gap , comprehensiveRect.getWidth() - gap , totalHeight - textHeight );

    gui::IGUIImage* img = gui->addImage( srcRect );
    img->setID( NGuiIds::DialogImage );
    img->setText(L"Temp");
    img->setUseAlphaChannel (true);

    _dialogTab->addChild( img );
    // contains answers
    //gui->addListBox();

    //////////////////////////////////////////////////////////
    ////    Answers list
    //////////////////////////////////////////////////////////

    //irr::core::recti  answersRect( irr::core::position2di(_PORTRAIT_SIZE.Width, 270), core::dimension2di(300,100) );
    //- textHeight
irr::core::recti  answersRect( conf::_PORTRAIT_SIZE.Width + gap, textHeight + gap , comprehensiveRect.getWidth() - gap , totalHeight  );

    gui::IGUIListBox* answers = gui->addListBox( answersRect );
    //answers->setOverrideColor ( video::SColor(255,255,255,255) );
    answers->addItem(L"test");

    answers->setDrawBackground(true);
    answers->setID( NGuiIds::DialogAnswers );
    answers->setItemOverrideColor ( 0, EGUI_LBC_TEXT , textColor);
    _dialogTab->addChild( answers );

    _answers = answers;

    //_INFO << "Answers rect" << answersRect;
/*

    }


    const irr::video::ITexture* texture = speaker.getTexture();
    if(texture){
        irr::core::recti  srcRect(irr::core::position2di(0,0), texture->getOriginalSize());
        engine()->driver->draw2DImage(
            texture,
            core::position2di(10,10),
            srcRect,
            0,              // clipRect
            video::SColor(255,255,255,255),
            true                // useAlphaChannelOfTexture
            );

    }
    */
}


void
CSinglePlayerState::updateDialog(){


    //_INFO << "updating dialog";

    bool resume = false;

    _player->updateInput();

    //CCollectionSnapshot<NPlayerInput::Count>& _mappingSet = _player->_input;


    //_answers->getItemCount ();
    //_dialog.second->_answers.size()

//    _answers->setSelected( _answers->getSelected() + 1 );

    // If there are questions
    //if( _answers->getItemCount () > 0 ){
#if 0
    const irr::u32 itemCount = _answers->getItemCount ();
    irr::s32 selectedId = _answers->getSelected();

            //_INFO << "Item COUNT > 0" ;
    if( itemCount > 0){

            //if( _mappingSet.getState(NPlayerInput::MoveForward) ){
            if( _mappingSet.getState(NPlayerInput::ModeDown) ){

                --selectedId;
                if(selectedId < 0){
                    selectedId = itemCount-1;
                }
            }
            //else if( _mappingSet.getState(NPlayerInput::MoveBackward) ){
            else if( _mappingSet.getState(NPlayerInput::ModeUp) ){

                //_answers->setSelected( _answers->getSelected() - 1 );
                ++selectedId;
                if( selectedId >= itemCount ){
                    selectedId = 0;
                }

            }

        _answers->setSelected( selectedId );
    }


    // IF shall resume script

//    TODO reactiver
    if( _mappingSet.getState(NPlayerInput::MainShoot) ){

        _lastPlayerReply = _answers->getSelected();

        _INFO << "User reply (from C++): [" << _lastPlayerReply << "]";

        // Hide menu
        enableMenu( _dialogTab, false );

        changeState( NPlayState::Playing );

        // verifier le retour
        if(!_script->resume()){

            _LOG_ERROR << "Could not resume script";
        }
    }
    else {
        //_INFO << "No reply yet";
    }
#endif
    //_INFO << "left answered";
}



void
CSinglePlayerState::updateCinematic( ){
}


// TODO checker si le joueur est mort


