/**
\file
\author

TODO faudra pvr afficher les messages de log dedans
**/
#ifndef _CCONSOLE_HPP_INCLUDED
#define _CCONSOLE_HPP_INCLUDED

#include <fusion/console/IConsole.hpp>
#include <irrlicht.h>
#include"../states/IGameState.hpp"

// forward declaration
class CGameEngine;

// En fait c'est un etat mais persistant
class CConsole :
public TGameState,
public fus::IConsole
{


public:
    CConsole();
    ~CConsole();

    void Init(CGameEngine* engine,const irr::core::recti& tabPos);
    void Enable(const bool& enable);
    bool ValidCommand(fus::IInterpreter* interpreter);
    void Draw();


//protected:
//setMultiLine

    //irr::gui::IGUIEnvironment* _gui;
    int _delta;
    CGameEngine* _engine;
    irr::gui::IGUIEditBox* _editBox;
    irr::gui::IGUIListBox* _listBox;
    irr::gui::IGUITab* _tab;
    //irr::gui::IGUIWindow* _window;

};

#endif

