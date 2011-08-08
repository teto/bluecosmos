#include "CConsole.hpp"
#include <fusion/scripting/CLuaScript.hpp>
#include <irrlicht.h>
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

    ValidateInput(_editBox->getText(),interpreter);
    _listBox->addItem(_editBox->getText());
    _editBox->setText(L"");
    return true;
}

void
CConsole::Init(CGameEngine* engine,const core::recti& tabPos){
    if(!engine){
        return ;
    }

    _engine = engine;
    video::SColor  bgColor(100,255,0,255);
    video::SColor  textColor(255,0,255,0);
    int commandLineHeight = 20;
    int consoleWidth = tabPos.getWidth();
    int consoleHeight = tabPos.getHeight();

//commandLineHeight
    if(!_editBox){
        //pos/parent/id
        _tab =   _engine->guienv->addTab (tabPos);

        //rectangle, parent / id /drawBackground
        core::recti listSize(0,0,consoleWidth,consoleHeight-commandLineHeight);
        _listBox = _engine->guienv->addListBox(listSize ,_tab);
        _listBox->addItem(L"Hello world");

        //  text/rectangle/border /parent/id
        core::recti commandLineSize( 0,consoleHeight-commandLineHeight,consoleWidth,consoleHeight );
        _editBox = _engine->guienv->addEditBox(L"",commandLineSize,false,_tab);
    }

    _editBox->setDrawBorder(false);
    _editBox->setMultiLine(false);
    _editBox->setAutoScroll(true);

    _tab->setBackgroundColor(bgColor);
    _tab->setDrawBackground(false);
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
