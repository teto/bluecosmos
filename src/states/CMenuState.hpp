/**
* \file menu.h
* Utiliser std::tr1
**/
#ifndef _BC_CMENUSTATE_HPP_INCLUDED
#define _BC_CMENUSTATE_HPP_INCLUDED


#include "IGameState.hpp"
#include <irrlicht.h>
#include <boost/scoped_ptr.hpp>
#include <array>
#include <boost/ptr_container/ptr_list.hpp>
#include "IdList.hpp"
//#include "../audio/ISound.hpp"
#include "../utils/C2DSprite.hpp"

// pr faire mvt de camera autour du vaisseau ?
//createFlyCircleAnimator


namespace NGuiIdsState {
enum EId {
MainMenu,
Scores,
Credits
};
}

namespace audio {
class ISound;
}


class CMenuState :
    public IGameState<NStateId::MainMenu,false>
{

public:
    CMenuState();
    ~CMenuState();

	void init();
	void CleanUp();

    void onResume();
    void onHold();

	void Update();
	void Draw();

    void changeInternalState(const NGuiIdsState::EId& state);

    bool OnEvent(const irr::SEvent& event);


protected:
    NGuiIdsState::EId _menuState;

    void GUI_CreateMainMenu();              //!< Create main (home) menu

    irr::gui::IGUITab* _menu;
    irr::gui::IGUIEditBox* _editBox;
    //irr::gui::IGUIWindow* _editBox;
    irr::scene::ISceneNode* _skybox;
    irr::gui::IGUIStaticText* _buildInfoText;

    //ISceneNode* _world;
    //smgr->getMesh("models/animated/yf19.b3d")
//    CMenu mMenu;                            //!< Instance of current menu

    typedef boost::ptr_list<C2DSprite> TSpritesMap;
    TSpritesMap _sprites;
    boost::scoped_ptr<audio::ISound> _hoverSound;
//std::vector<
    irr::s32 _materialIds[2];
};


#endif
