/**
* \file options.h
*  \brief Option menu state
*
*   State called from menu, single and MultiPlayerState
*   Basée sur menu
**/

#ifndef ERRORSTATE_HPP
#define ERRORSTATE_HPP

#include "IGameState.hpp"
#include <irrlicht.h>


class CErrorState:
public TGameState
{



public:
//const irr::core::rectf&
    //CErrorState(const irr::core::stringw &caption, const irr::core::stringw &text);
    CErrorState(const wchar_t* caption, const wchar_t* text);
    ~CErrorState();
	void init();
	void onResume();
//	void onHold();

	bool OnEvent(const irr::SEvent&);

	void Update();
	void Draw();



protected:


//!< Inform what tab we are on
//renommer en _tabControl
    //irr::core::rectf _pos;
    //irr::gui::IGUITab* _overallTab;
    irr::gui::IGUIWindow* _messageBox;
    irr::gui::IGUIEditBox* _editBox;
//    irr::gui::IGUITabControl* _tabControl;
//    irr::s32 indexOfFocusedElement;
//    irr::gui::IGUIComboBox* _comboBox;
};

#endif // OPTIONSTATE_H
