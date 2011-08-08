#include "CConsole.hpp"
#include <fusion/scripting/CLuaThread.hpp>
#include <irrlicht.h>
#include <algorithm>
#include "../game_engine.hpp"

// setMultiLine


using namespace irr;
using namespace gui;

CConsole::CConsole(){

    _engine = 0;
    _editBox = 0;
    _delta = 0;
    _tab = 0;
}

CConsole::~CConsole(){

}

// Pr pvr faire coulisser le panneau
void
CConsole::Enable(const bool& enable){

    if(enable == false){
        _delta = -5;
    }
    else {
        _delta = 5;
    }
}


bool
CConsole::ValidCommand(fus::IInterpreter* interpreter){

//const wchar_t *
    std::wstring command( _editBox->getText() );

    ValidateInput( command,interpreter);
    _listBox->addItem( command.c_str() );
    _editBox->setText(L"");
    return true;
}


void
CConsole::Init(CGameEngine* engine,const core::recti& tabPos){

    if(!engine){
        return ;
    }

    _engine = engine;

    _index = -1;

    video::SColor  bgColor(100,255,0,255);
    video::SColor  textColor(255,0,255,0);
    int commandLineHeight = 20;
    int consoleWidth = tabPos.getWidth();
    int consoleHeight = tabPos.getHeight();

//commandLineHeight
    if(!_editBox){
        //pos/parent/id
        irr::gui::IGUIEnvironment* gui = _engine->gui();
        _tab =   gui->addTab (tabPos);

        //rectangle, parent / id /drawBackground
        core::recti listSize(0,0,consoleWidth,consoleHeight-commandLineHeight);
        _listBox = gui->addListBox(listSize);
        _tab->addChild(_listBox);

        //_listBox->addItem(L"Console Item 1");

        //  text/rectangle/border /parent/id
        core::recti commandLineSize( 0,consoleHeight-commandLineHeight,consoleWidth,consoleHeight );

        ///
        _editBox = gui->addEditBox(L"",
                                               commandLineSize,
                                               false                //!< Enable border
                                               );
        _tab->addChild(_editBox);
    }

    _editBox->setDrawBorder(true);
    _editBox->setMultiLine(false);
    _editBox->setAutoScroll(true);

    _tab->setBackgroundColor(bgColor);
    _tab->setDrawBackground(true);
    _tab->setTextColor(textColor);
    _listBox->setAutoScrollEnabled(true);
}

void
CConsole::Draw(){

    if(_delta != 0){
        //getAbsoluteClippingRect
        //getAbsolutePosition
        //_tab->setpos
    }
    _tab->draw();
}





void
CConsole::cycleThroughCommands(const bool& up){


    if( up ){

        // If index < 0 than we save input
        if(_index < 0){
            _bufferedInput = _editBox->getText();
        }
        _index = std::min( _index + 1 ,(int)(_listBox->getItemCount()) );
    }
    else {
        _index = std::max( _index - 1, -1);
    }

    if(_index < 0){
        //_index = -1;
        _editBox->setText(_bufferedInput.c_str() ) ;
    }
    else {
        _editBox->setText( _listBox->getListItem(_index) );
    }


}
