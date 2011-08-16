/**
* \file options.h
*  \brief Option menu state
*
*   State called from menu, single and MultiPlayerState
*   Basée sur menu
**/

#ifndef OPTIONSTATE_HPP
#define OPTIONSTATE_HPP

#include "IGameState.hpp"
#include <irrlicht.h>
#include <boost/optional.hpp>
#include <array>
#include <map>



// Xeffects
class EffectHandler;
namespace input {
    class CBindFromEventGenerator;
}

class COptionState :
    public IGameState<NStateId::Options,false>
    //"Options"
{

enum EOptionTab {
Graphics,
Controls,
Sound,
Gameplay,
Count
};


public:

    COptionState(const irr::core::rectf&);
    ~COptionState();
	//void init();
	void CleanUp();
	bool OnEvent(const irr::SEvent&);

	void Update();
	void Draw();

/*
const irr::core::position2di _BUTTON_GAP(5,_BUTTON_HEIGHT + 10);
//const irr::core::recti _MENU_RECT_BUTTON();
#define _MENU_DECAL_RECT(x) (x) += _BUTTON_GAP;

extern const int _BUTTON_WIDTH;
const irr::core::recti _MENU_BUTTON_RECT(0,0,_BUTTON_WIDTH,_BUTTON_HEIGHT);
*/
    //static void decal(irr::core::recti& pos,const float& x,const float& y);

    boost::scoped_ptr<input::CBindFromEventGenerator> _descriptorGenerator;

protected:
    void setButtonValue(NPlayerInput::EId const& id);
    void createBindLine(wchar_t const* name,NPlayerInput::EId const& id, irr::gui::IGUITab* tab);

    bool waitingNewBind() const {
        //return (_indexOfFocusedElement >= 0);
        //return (_translatedIdToUpdate);
        return (_descriptorGenerator);
    }
//
//    updateDescription(CBind) const {
//
//    }
    //CBindEntry* getMapping();
    //int getMappingId();


// TODO unused !!
    bool processEventForSoundTab(const irr::SEvent::SGUIEvent& event);
    bool processEventForControlTab(const irr::SEvent::SGUIEvent& event);
    bool processEventForGraphicTab(const irr::SEvent::SGUIEvent& event);
    bool processEventForGameplayTab(const irr::SEvent::SGUIEvent& event);

    // "setup" plutot que "create"
    void createSoundTab(irr::gui::IGUITab* tab);
    void createControlTab(irr::gui::IGUITab* tab);
    void createGraphicTab(irr::gui::IGUITab* tab);
    void createGameplayTab(irr::gui::IGUITab* tab);


    void OnClickBack();
    bool OnClickSaveButton();

    void GUI_CreateMainMenu();              //!< Create main options menu

//reset ?
    void setToConfigValues();
    irr::core::stringw videoModeToText(const irr::core::dimension2du& dims,const irr::s32& depth);

//    typedef void (CBattery::*TUpdateFunction)(const float&);
    typedef bool (COptionState::*TProcessingFunction)(const irr::SEvent::SGUIEvent&);

    TProcessingFunction _processingFunctions[Count];

//!< Inform what tab we are on
//renommer en _tabControl
    //std::array<const wchar_t*, NPlayerInput::Count >;

    irr::core::rectf _pos;
    irr::gui::IGUITab* _overallTab;
    irr::gui::IGUITabControl* _tabControl;
    irr::gui::IGUIButton* _buttonToUpdate;
    //std::map<irr::gui::IGUIButton*,NPlayerInput::EId> _buttonsMap;
    //boost::optional<int> _translatedIdToUpdate ;

//irr::gui::IGUIButton*
    //std::array< irr::gui::IGUIButton*, NPlayerInput::Count > _buttonIds;

    //irr::s32 _indexOfFocusedElement;

    irr::gui::IGUIComboBox* _comboBox;



    // TODO informer l'utilisateur si l'application doit redémarrer ou pas.
    // On enregistre la version avant config,
    irr::SIrrlichtCreationParameters _bufferedParameters;
    // on recupere la version après et on compare les 2,
    // s'il y a des différences alors faut redémarrer le programme !

    //de  depart
    //bool _needRestart;
};

#endif // OPTIONSTATE_H
