/**
* \file menu.cpp
*
* utiliser la camera de gameengine ou la sienne propre ?
*/
#include "CMenuState.hpp"
#include "COptionsState.hpp"
#include "CScoreState.hpp"
#include "../fightingState/CSinglePlayerState.hpp"
#include "../game_engine.hpp"
#include <vector>
#include <fstream>
#include "../config.hpp"
#include "../IdList.hpp"
#include "../utils/CBitSet.hpp"
#include "../entities/IMultiModeTransformer.hpp"
#include "../utils/C2DSprite.hpp"
#include "../audio/IAudioDriver.hpp"
#include "../audio/ISound.hpp"
#include <xeffects/XEffects.h>
#include <luabind/version.hpp>

// TEST gettext
//#include <libintl.h>
//#define _(String) gettext (String)
//#define gettext_noop(String) String
//#define N_(String) gettext_noop (String)



using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;



CMenuState::CMenuState() :
//TGameState("Main menu"),
_menu(0),
_editBox(0),
_skybox(0),
_hoverSound(0),
_buildInfoText(0),
_menuState(NGuiIdsState::MainMenu)
{

    _menu = 0;

    /// Create initial menu
    GUI_CreateMainMenu();
    changeInternalState(NGuiIdsState::MainMenu );


// TODO pas de camera active
    //scene::ICameraSceneNode* camera = engine()->smgr->addCameraSceneNode(
    scene::ICameraSceneNode* camera = scene()->addCameraSceneNode(
                                0,
                                core::vector3df(0, 0, -5),
                                core::vector3df(0, 0, 0)
                                );
    //engine->getCamera();
    //engine->smgr->setActiveCamera();
    //addCameraSceneNodeMaya  ();

    camera->setTarget(TVector3df(0,0,0));


    scene::ISceneNodeAnimator* anim = scene()->createFlyCircleAnimator(
                                core::vector3df(0,0,0),     //center
                                20.0f,                      //radius
                                0.0001,                     //speed
                                core::vector3df(0.f, 1.f, 0.f), //direction
                                0,                          //start position
                                0                           //raidus ellipsoid
                                );

    camera->addAnimator(anim);

    video::IVideoDriver* driver = engine()->driver();

    _skybox = scene()->addSkyBoxSceneNode(
            driver->getTexture("images/irrSkyBox/irrlicht2_up.jpg"),
            driver->getTexture("images/irrSkyBox/irrlicht2_dn.jpg"),
            driver->getTexture("images/irrSkyBox/irrlicht2_lf.jpg"),
            driver->getTexture("images/irrSkyBox/irrlicht2_rt.jpg"),
            driver->getTexture("images/irrSkyBox/irrlicht2_ft.jpg"),
            driver->getTexture("images/irrSkyBox/irrlicht2_bk.jpg")
    );

    //skybox->setParent( scene()->getRootSceneNode() );

    //scene::ISceneNode* skydome= game->smgr->addSkyDomeSceneNode(game->driver->getTexture("media/skydome.jpg"),200,60,1.f,2.0f,50);

    /// Show again the cursor
    engine()->showCursor(true);


    ////////////////////////////////////////////
    ///     Load hover sound
    ////////////////////////////////////////////

    _hoverSound.reset( engine()->getSoundManager()->getSound( "sounds/menu_hover.wav") );


}


CMenuState::~CMenuState() {

    _menu->remove();
}



void
CMenuState::changeInternalState(const NGuiIdsState::EId& state){

    if(state == NGuiIdsState::MainMenu){

        _menu->setVisible(true);
        _editBox->setVisible(false);
        //_editBox->setEnabled(false);
    }
    else {

        _menu->setVisible(false);
        //_menu->setEnabled(false);
        _editBox->setVisible(true);
    }
}


void
CMenuState::onResume()
{
    //
    _menu->setVisible(true);
    engine()->showCursor(true);
    //tab->setEnabled (true);

    // TODO supprimer l'effet
//    postProcessingFramework()->removePostProcessingEffect(_materialIds[0]);
//    postProcessingFramework()->removePostProcessingEffect(_materialIds[1]);
}






void
CMenuState::onHold(){

    //

    _menu->setVisible(false);

	core::stringc shaderExt = ".glsl";


//removePostProcessingEffect
//	_materialIds[0] = postProcessingFramework()->addPostProcessingEffectFromFile(core::stringc("shaders/BlurHP") + shaderExt) ;
//	_materialIds[1] = postProcessingFramework()->addPostProcessingEffectFromFile(core::stringc("shaders/BlurVP") + shaderExt) ;

    //tab->setEnabled (false);

}


/**
TODO Detecter les changements pr demander si le joueur est sur de vouloir rebooter graphisme:
EGET_EDITBOX_ENTER
EGET_TAB_CHANGED
EGET_CHECKBOX_CHANGED
EGET_EDITBOX_CHANGED
EGET_MENU_ITEM_SELECTED,
EGET_COMBO_BOX_CHANGED,
**/

bool
CMenuState::OnEvent(const SEvent& event){


	switch (event.EventType){

        //case EET_MOUSE_INPUT_EVENT:break;
        case EET_MOUSE_INPUT_EVENT :
            //if( event.MouseInput.ButtonStates == 1)
            if(event.MouseInput.isLeftPressed () ){
                //    _menuState = NGuiIdsState::MainMenu;
                changeInternalState(NGuiIdsState::MainMenu );
//                _INFO << "left button pressed";
//                // TODO gerer tout seulnew CSprite(
//                C2DSprite* sprite = CGameEngine::getSpriteManager()->add2Dsprite( engine()->driver()->getTexture("images/animatedCursor.png"),4,3, true );
//                sprite->enableLoop(false);
//                sprite->setFrameTime( 80 );
//                // TODO setPosition !
//
//
//                //engine()->_device->getCursorControl
//                //engine()->getMousePosition()
//                sprite->setPosition( position2di (event.MouseInput.X,event.MouseInput.Y ) );
//
//                //
//                _sprites.push_back(sprite);
            }
            break;
        //case EET_MOUS

    /////////////////////////////////////////////////////
    ////    Change model
    /////////////////////////////////////////////////////
    case EET_KEY_INPUT_EVENT:
        if(!event.KeyInput.PressedDown){
            return false;
        }

        break;

	    case EET_GUI_EVENT:
 {
        IGUIElement* caller = event.GUIEvent.Caller;
		s32 id = event.GUIEvent.Caller->getID();
		//IGUIEnvironment* env = gui();



		switch(event.GUIEvent.EventType){


        //case EGET_ELEMENT_LEFT: break;

//        case EGET_ELEMENT_FOCUSED:
//        case EGET_ELEMENT_FOCUS_LOST :
        case EGET_ELEMENT_HOVERED:
            if(caller->getType() == EGUIET_BUTTON){

                _INFO << "button hovered";

                if(_hoverSound){
    //                _INFO << "Button hovered caller [" << caller << "] menu [" << _menu << "] editbox [" << _editBox << "]";
                    _hoverSound->stop();
                    _hoverSound->play();
                }
                else {

                    _LOG_WARNING << "Could not play sound on mouse over";
                }
            }


            break;

		case EGET_ELEMENT_CLOSED:
		    if(id == NGuiIds::CreditsWindow){
                //_menuState = NGuiIdsState::MainMenu;
                 changeInternalState(NGuiIdsState::MainMenu );
                // Prevents irrlicht from deleting window
                return true;
		    }
		    break;

		case EGET_BUTTON_CLICKED:
			switch(id){

                case NGuiIds::QuitGame:
                    //_INFO << "closing game";
                    _INFO << "user asked to quit";
                    engine()->Quit(); //device->closeDevice();
                    return true;

                case NGuiIds::Play:
                    {
                        //TGameStatePtr fight(new CSinglePlayerState());
                        replaceThisState( NStateId::Solo);
                        //engine()->ChangeState(fight,"Changing to playing state");
                    }

                    return true;

                case NGuiIds::Credits:
                    // faire defiler du texte
                    {

                        //_menuState = NGuiIdsState::Credits;
                        changeInternalState(NGuiIdsState::Credits);
                        //engine()->popupMessage();
                        //conf::CREDITS_STRING
                        //engine()->popupMessage(L"Credits", L"LOL");
//                        bool visible = !_editBox->isVisible();
//                        _editBox->setVisible(visible);
                    }

                    break;


                case NGuiIds::ViewScores:
                    //_overallSet->setAlignment( EGUIA_SCALE, EGUIA_SCALE, EGUIA_SCALE, EGUIA_SCALE);
                    // On se place dans un cas special de cet etat false,
                    {
//                        TGameStatePtr scoreState(new CScoreState( irr::core::rectf(0.2f,0.2f,0.8f,0.8f) ) );
//                        engine()->PushState( scoreState );
                    }
                    break;

                case NGuiIds::Options:
                    // afficher a gauche en surbrillance le truc
                    //," adding options state"
                    {
                        pushState( NStateId::Options );
                        //TGameStatePtr optionState(new COptionState(core::rectf(0.3f, 0.2f,0.9f,0.8f)));
                        //engine()->PushState(optionState);
                    }

                    break;

                case NGuiIds::SetModelToYF21:
                    //engine()->smgr,
                    engine()->getPlayer()->setupAsModel(  NWalkyrieModel::YF21);
                    break;

                case NGuiIds::SetModelToYF19:
                    engine()->getPlayer()->setupAsModel(  NWalkyrieModel::YF19);
                    break;

                default:
                    return false;
			}
			break;

		default:
			break;
    }
	}
	default: break;


}
    return false;
}



/// \function Draw()
void
CMenuState::Draw(){

    //_LOG_DEBUG << "starting drawing menu scene [" << scene() << "]";
    //postProcessingFramework()->update();

// Xeffect hack
    engine()->driver()->setMaterial( engine()->driver()->getMaterial2D() );
    //CGameEngine::getSpriteManager()->draw2Dsprites();
//
//    switch(_menuState){
//
//        case NGuiIdsState::Credits:
//            _INFO << "Credits";_editBox->draw();break;
//
//        case NGuiIdsState::MainMenu: _menu->draw(); break;
//        default:
//            break;
//    }

    _editBox->draw();
    _menu->draw();


    // Display 2D sprites of where clicked
    for(TSpritesMap::iterator i( _sprites.begin() ), end(_sprites.end());i != end;++i){

        i->draw( engine()->driver() );
    }


    _buildInfoText->draw();
//drawAll
}



/// mettre a jouer la camera ici
void
CMenuState::Update(){

    // TODO a deplacer
    _LOG_DEBUG << "Start updating CMenuState";

    const TTimeUnit elapsedTime = engine()->getElapsedTime();

    engine()->getPlayer()->update( elapsedTime );
    engine()->getPlayer()->processTransformations();

    /////////////////////////////////////////////////
    /// Update sprites
    /////////////////////////////////////////////////
    //boost::is_null(

    for(TSpritesMap::iterator i( _sprites.begin() ), end(_sprites.end());i != end;++i)
    {

        //C2DSprite* sprite = i;

        // si explosion terminee
        if( i->update(elapsedTime) ){
            //i.release();
            //delete sprite;
            i = _sprites.erase(i);
            //continue;
            _INFO << "sprite To Remove";
        }

    }
}


/**** Function Cleanup() ****/
void
CMenuState::CleanUp(){

    _menu->remove();
    engine()->getSoundManager()->collectGarbage();
    //engine()->guienv->clear();
    //engine()->smgr->clear();
};


/// Create main menu ( = 1st to be displayed )
// Faire un menu de taille dynamique
void
CMenuState::GUI_CreateMainMenu() {


    ////////////////////////////////////////////////////////////////
    ////           Create Credits window
    ////////////////////////////////////////////////////////////////

    _editBox =

    gui()->addEditBox (
                       conf::CREDITS_STRING, //text
                       core::recti(200,0,500,300),
                       //engine()->getAbsoluteRectangle( 0.2f, 0.2f,0.8f,0.8f ),
                       true //border

                       );


    //gui()->setFocus(0);
    _editBox->setRelativePositionProportional(  core::rectf(0.2f,0.2f,0.8f,0.8f) );
    _editBox->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER );


    //_editBox->setEnabled(false);
    /*
                gui()->addWindow(

                    core::recti(200,0,300,500),
                    false,   //modal
                    conf::CREDITS_STRING, //text
                    0,  //parent
                    NGuiIds::CreditsWindow    // id
                    );*/
    //
//    _editBox->setAutoScroll(true);
//    _editBox->setMultiLine(true);
    //
//setOverrideColor
    //_editBox->setVisible(false);



    ////////////////////////////////////////////////////////////////
    ////           Create main buttons
    ////////////////////////////////////////////////////////////////
    gui::IGUIElement* elem = gui()->getRootGUIElement();
//    _INFO << "Root ELement rect" << elem->getAbsoluteClippingRect().UpperLeftCorner.X
//            << "/" << elem->getAbsoluteClippingRect().LowerRightCorner.X;

    _menu 	= gui()->addTab( irr::core::recti(0,0,0,0), gui()->getRootGUIElement());
    _menu->setRelativePositionProportional( core::rectf(0.1f,0.4f,1.f,1.f));
    _menu->setDrawBackground(true);




    recti rectButton( conf::_MENU_BUTTON_RECT );

	// faudriat les mettre dans un mm container
	gui()->addButton(rectButton, _menu,
                    NGuiIds::Play,
                    L"Play",
                    L"Launches a new game");

    rectButton += conf::_BUTTON_GAP;

    gui()->addButton(rectButton, _menu,
                    NGuiIds::Options,
                    L"Options",
                    L"Tweak graphics, sound & controls");


    rectButton += conf::_BUTTON_GAP;
    gui()->addButton(rectButton, _menu,
                    NGuiIds::ViewScores,
                    L"Scores",
                    L"View scores");
    rectButton += conf::_BUTTON_GAP;

    //rect<s32>(0,3*_HEIGHT_DELTA,110,3*_HEIGHT_DELTA + 32)
    gui()->addButton(rectButton, _menu,
                    NGuiIds::Credits,
                    L"Credits",
                    L"Staff members");
    rectButton += conf::_BUTTON_GAP;

//rect<s32>(0,4*_HEIGHT_DELTA,110,4*_HEIGHT_DELTA + 32)
	gui()->addButton(rectButton, _menu,
                    NGuiIds::QuitGame,
                    L"Quit",
                    L"Exits Program");

    //rectButton.Lowern

    decal( rectButton, 100, 50);
	gui()->addButton(rectButton, _menu,
                    NGuiIds::SetModelToYF19,
                    L"YF-19",
                    L"Change plane");

    //rectButton.

    xDecal( rectButton, 30);
	gui()->addButton(rectButton, _menu,
                    NGuiIds::SetModelToYF21,
                    L"YF-21",
                    L"Change plane");



    ////////////////////////////////////////////////////////////////
    ////           Create text displaying build version
    ////////////////////////////////////////////////////////////////
 // todo faut que ca s'adapte a la taille de la fenetre pr tenir sur une ligne !!!
    stringw desc(L"v");
    desc += conf::_GAME_VERSION;
    desc += __DATE__;
    desc += "\nLuabind version: ";
    desc += LUABIND_VERSION;
    //desc += " at ";
    //desc += __TIME__;


    IGUIStaticText* text = gui()->addStaticText  ( desc.c_str(),rect<s32>(0,0,300,80));
    //text->setMinSize(core::dimension2du(text->getTextWidth(),text->getTextHeight()));
    core::position2di pos(engine()->getScreenSize().Width-text->getTextWidth(),engine()->getScreenSize().Height-text->getTextHeight());
    text->setRelativePosition(pos);
    text->setWordWrap(false);

    _buildInfoText = text;



}

