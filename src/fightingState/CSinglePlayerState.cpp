/**
* \file single.cpp
*/
#include "CSinglePlayerState.hpp"
#include <cmath>
#include <irrlicht.h>
#include "../entities/player.hpp"
#include "../config.hpp"
#include "../game_engine.hpp"
#include "../states/CMenuState.hpp"
#include "../states/COptionsState.hpp"
#include "../states/CScoreState.hpp"
#include "../states/CErrorState.hpp"
#include "../states/CTransitionState.hpp"
#include "../states/IdList.hpp"
#include "../utils/CParticleManager.hpp"
#include "../utils/CBitSet.hpp"
#include "../entities/IMultiModeTransformer.hpp"
#include <fusion/scripting/CLuaThread.hpp>
#include <fusion/scripting/CLuaVM.hpp>
#include <fusion/maths/macros.hpp>
#include <fusion/core/string.hpp>
#include "../utils/CFadingImage.hpp"
#include "../CSpeech.hpp"


const int _OSCILLATION_NUMBER = 3;


using namespace irr;
using namespace video;
using namespace core;
using namespace scene;



//bindGlobalVarToLua(){
//
//}
//

// Passer le nom du script en parametre ?
//CGameEngine* engine
//! Constructor
CSinglePlayerState::CSinglePlayerState() :
_camera(0),
_pauseMenu(0),
_shakingTimer(0),
_world(0),
_dialogTab(0),
_gameOverMenu(0),
_lastPlayerReply(0),
_editorTab(0),
//_playState( NPlayState::InitializingScriptingEngine ),
_initialized(false)
{

    //_script.reset( new fus::CLuaThread( &(engine()->_vm) ) );
    //_script = make_shared<fus::CLuaThread>( new fus::CLuaThread( engine()->getScriptingVM() ) );

    _playState[0]= NPlayState::Playing ;
    _playState[1]= NPlayState::Playing ;

    //
    _updateFunctions[ NPlayState::Cinematic ]                   = &CSinglePlayerState::updateCinematic;
    _updateFunctions[ NPlayState::Playing ]                     = &CSinglePlayerState::updatePlaying;
    _updateFunctions[ NPlayState::Dialog ]                      = &CSinglePlayerState::updateDialog;
    _updateFunctions[ NPlayState::EndingLevel ]                 = &CSinglePlayerState::updateEndingLevel;
    _updateFunctions[ NPlayState::StartingLevel ]               = &CSinglePlayerState::updateStartingLevel;
    _updateFunctions[ NPlayState::Menu ]                        = &CSinglePlayerState::updateMenu;
    //_updateFunctions[ NPlayState::InitializingScriptingEngine ] = &CSinglePlayerState::initializingScriptingEngine;


    _player = engine()->getPlayer();



    ///////////////////////////////////
    /////   Setup cameras   ///////////
    ///////////////////////////////////
    setupCameras();



    // TODO a deplacer dans le state fourre tt
    GUI_CreatePauseMenu();
    GUI_CreateGameOverMenu();
    GUI_CreateDialogTab();
    GUI_CreateEditorTab();

    _pauseMenu->setVisible(false);
    _gameOverMenu->setVisible(false);
    _dialogTab->setVisible(false);
    _editorTab->setVisible(false);


    engine()->showCursor(true);
};



//! Destructor
CSinglePlayerState::~CSinglePlayerState(){
    //_world->remove();
//    delete _script;
}





float
CSinglePlayerState::getUpperProgression() const {
    //return smgr->getActiveCamera()->getPosition().Z;
    return _upperProgress;
}




// TODO rebommer en CBatteryModel
/*
CModel*
CGraphicalLevel::createBatteryModel(const char* filename,const int& life,const int& bonus,const float& range)
{
    //createBatteryModel
    //CGameEngine* engine = CGameEngine::getInstance();
    //CGameEngine* engine = ENGINE;
    irr::scene::IAnimatedMesh* mesh = scene()->getMesh(filename);

    if(!mesh){
        _LOG_WARNING << "could not load mesh [" << filename << "]";
        return 0;

    }

    CModel *model = new CModel();

    model->_mesh = mesh;
    model->_bonus= bonus;
    model->_range = range;
    model->_life = life;
    return model;
}
*/

//CStaticBattery*
//CGraphicalLevel::getNextTarget()
//{
//    //
//    //if(_enemyFleet.){
//// TBulletPool::TElementIterator
//    // TODO return 0 if liste empty
//        return 0;
//        //&(*_enemyFleet._staticBatteries.begin() );
//    //}
//    //return 0;
//}





// setupLuaThread/context
bool
CSinglePlayerState::setupLuaThread(){
//->createThread()

    TScriptingVM& vm = engine()->getScriptingVM();

    _script.reset( new fus::CLuaThread( vm.getVM() ) );
    //TScriptingVM& vm = engine()->

    try {

        luabind::object global_vars;
        _script->getGlobals(global_vars);

        global_vars["Engine"] = engine();
        global_vars["Player"] = _player;
        global_vars["MainState"] = this;
        global_vars["Logger"] = fus::Logger::instance();
    //TODO
        //global_vars["SoundManager"] = engine()->getSoundManager();

    }
    catch(std::exception &e){
        _LOG_DEBUG << e.what();
    }


    // TODO faire en sorte que le message d'erreur s'affiche jusqu'à ce qu'il
    // soit resolu
    // quitter le jeu
    const char* filename = conf::_LUA_STARTER_SCRIPT;


    bool ret =  vm.RunFile(filename);
    if( !ret ){

        _LOG_ERROR << " script [" << filename << "] not loaded";

        engine()->popupMessage(L"Main Lua script error",vm.getErrorDescription() );
        return false;
    }

    return true;
}





void
CSinglePlayerState::launchCinematic(){

//scene()->createFollowSplineAnimator (s32 startTime, const core::std::array< core::vector3df > &points)
                                       //, f32 speed=1.0f, f32 tightness=0.5f, bool loop=true, bool pingpong=false)=0

    //changeState( NPlayState::Cinematic );
}





void
CSinglePlayerState::updateMenu(){

    // Does nothing
}




// backup last state
void
//CSinglePlayerState::changeState( const NPlayState::EId& newState ){
CSinglePlayerState::changeState( NPlayState::EId newState ){

    _playState[1] = _playState[0];
    _playState[0] = newState;
    _INFO << "Changing from state" << _playState[1] << "to state" << getInnerState();
}




//
//int
//CSinglePlayerState::onMessageClose() {
//
//
//    //return lua_resume( engine()->_vm.getVM(), 0);
//
//
//    return
//}




void
CSinglePlayerState::restorePreviousState( ) {
    //
    //_INFO << "restore previous state" << _playState[1];
    changeState( _playState[1]);
}


void
CSinglePlayerState::addSimpleExplosion(const TVector3df& position) {

    ISceneNode* node = CGameEngine::getParticleManager()->createExplosion();
    node->setPosition( position );
    node->setParent( scene()->getRootSceneNode() );
    node->setScale( TVector3df( 4,4,4) );
    //

}





/// Function Update()
void
CSinglePlayerState::Update()
{


    _LOG_DEBUG << "starting updating CSinglePlayerState with mode [" << getInnerState() << "]";

    (this->*_updateFunctions[ getInnerState() ])();
//callm

}



void
CSinglePlayerState::updateCamera(){

    TVector3df posCamera = _player->_walkyrie->_cameraRecul;


    if(_shakingTimer){

        _shakingTimer->update( engine()->getElapsedTime() );
        if( _shakingTimer->reached() ){
        //if(_shakingTimer->update( engine()->getElapsedTime() )){
            //cam->getTarget() + core::vector3df(0,-4,+20)
            //_CAM_POS
            //_camera->setPosition( _camPosBackup );
            delete _shakingTimer;
            _shakingTimer = 0;
            _LOG_DEBUG << "END SHAKING";
        }
        else {
//1.f/_shakingTimer->getElapsedTime()
            double ratio = _shakingTimer->getAdvancement();
            // Le mettre
            double intensite = 20.f*_FUSION_POW2(1.f-ratio);
            //float coeff = _SHAKING_LENGTH/(_OSCILLATION_NUMBER*M_PI);
            // Le ratio est cense etre compris entre 0 et 1

            //getElapsedTime()/_SHAKING_LENGTH;
            intensite *= std::sin( 4* PIperso * ratio );
            _INFO << "shaking d'intensite/ratio " << intensite << "/" << ratio;

            TVector3df decalage(intensite,0,0);


            //_camera->setPosition(_camPosBackup + decalage);
            posCamera += decalage;
            //cam->setPosition();
        }
    }
    // if player transforming
    //else

    /////////////////////////////////////////////////////
    //////  Debug des specs
    /////////////////////////////////////////////////////
    _camera->setPosition( posCamera );
}



void
CSinglePlayerState::shakeCamera(){

    _INFO << "shaking camera";
    // If already shaking
    if(_shakingTimer){
        _shakingTimer->restart();
    }
    else {
        _shakingTimer = new TTimer( conf::_SHAKING_LENGTH);
        //
        _camPosBackup = _camera->getPosition();
    }

}






void
CSinglePlayerState::onResume() {
    //_levelMgr.newGame();
    //getLevelManager()._playState = CGraphicalLevel::Playing;
    _player->setupForNewGame();
}

//void  CSinglePlayerState::onHold() ;




void
CSinglePlayerState::DrawRightHUD(const core::position2di& upperLeft){

    video::IVideoDriver* driver = engine()->driver();

    // draw heating infos
    //video::ITexture * heatImg = driver->getTexture("images/icon.bmp");//crosshair_test.png
    //driver->draw2DImage  ( heatImg,core::position2di(400 ,40));

    SColor heatColor(255,255,255,0);


    ////////////////////////////////////////////
    ///// Heat
    ////////////////////////////////////////////
//_BC_PLAYER_MAX_HEAT-
    driver->draw2DRectangle(
                heatColor,//color
                core::recti( upperLeft, core::dimension2du(10,_player->_cannonHeat ))       //pos
    );



    ////////////////////////////////////////////
    /////   Missiles
    ////////////////////////////////////////////
    driver->draw2DRectangle(
                heatColor,
                core::recti( upperLeft + core::vector2di(40,0), core::dimension2du(10, _player->_missilesLeft * 3 ))       //pos
            );

}



void
CSinglePlayerState::DrawLeftHUD(const core::position2di& upperLeft){


    video::IVideoDriver* driver = engine()->driver();



    //core::stringw score();
    gui::IGUIFont* font = gui()->getFont( conf::_BC_FILE_HUDFONT);

    std::wstring strScore(L"Score:\n");
    CScoreState::getScoreAsString( strScore , _player->getScore());
    font->draw(strScore.c_str(), recti( upperLeft, core::position2di(60,30)) ,SColor(255,255,255,255));
    video::ITexture * iconImg = driver->getTexture("images/life2.jpg");//crosshair_test.png

    const int iLivesLeft = _player->getLivesLeft();

    int livesHeight = 200;
    video::SColor fontColor(255,255,255,255);

    core::stringw strLivesLeft("X");
    strLivesLeft += iLivesLeft;
    core::recti pos( position2di( 10 + iconImg->getSize().Width,livesHeight)  ,core::dimension2du(200,100));
    //pos += upperLeft;
    font->draw(strLivesLeft.c_str(), pos , fontColor);


    core::stringw progress("Progress:\n");

//    if( _levelMgr) {
//
//        progress += getLevelManager().getUpperProgression();
//    }


    pos += position2di(0,40);

    font->draw(progress.c_str(), pos ,video::SColor(255,255,255,255) );

    // juste a cote faut ecrire x (nombre of lives)
    driver->draw2DImage  ( iconImg, core::position2di(10, livesHeight) );

}



CSpeaker*
CSinglePlayerState::createActor(const std::string& name,const std::string& file)
{
    //get texture
    video::ITexture* texture = ENGINE->driver()->getTexture(file.c_str());

    // convert it into wide charcter
    std::wstring wname;
    utf8::utf8to16(name.begin(),name.end(), std::back_inserter(wname) );
    //_actors.push_back( );
    //return _actors.back();
    return new CSpeaker( wname,texture);//_actors.back();
}


//,const std::string& audioFilename
CSpeech*
CSinglePlayerState::createSpeech(const std::string& message){

    CSound* sound = 0;
//
//    if( audioFilename.size() ){
//        _LOG_DEBUG << "Loading audio filename [" << audioFilename << "]";
//        sound = ENGINE->getSoundManager()->getSound( audioFilename );
//    }

    std::wstring temp;
    fus::convertIntoWideString(message, temp);

    CSpeech* speech = new CSpeech( temp, sound );
    return speech;
}



// TODO deplacer ca dans lua
//const float& playerAdv,
//, CSinglePlayerState* _state
/*
void
CSinglePlayerState::update(const TTimer::TimeType& elapsedTime){




//    _layer->getMaterial(0).getTextureMatrix(0).setTextureTranslate(0.f,-percievedSpeed);




    speed = _player->_walkyrie->getSpeed(SModeDescription::DefaultForward)/100.f;

    // plus on est eloigne du bas de l'ecran plus la sensation de vitesse
    float ecart = (_player->getPosition().Z- conf::_LOWER_LIMIT);
    ecart /= (conf::_UPPER_PART - conf::_LOWER_LIMIT);
    // Comme ca on a un ecart < 1

    //_INFO << "ecart " << ecart;
    speed += ecart/1000.f;// /10.f


    //_INFO << "upper progress" << _levelMgr._upperProgress/100.f;

    percievedSpeed += (speed);

    // TOOOOOOODOOOO : a retirer !!
    //BUG
    getLevelManager().updatePlayerProgress(percievedSpeed);


    //_INFO << "speed" << translation;

    // Selon l'avancement du joueur, incliner plus ou moins la camera
    this->updateCamera();


}
*/


//setUp cameras
void
CSinglePlayerState::setupCameras(){

    //irr::core::dimension2du dim =  engine()->driver->getScreenSize();
    //_cameras[Scene] =
    _camera = scene()->addCameraSceneNode();
                    /*0,  //!< parent
                    //_CAM_POS, //!< cam pos
                    //core::vector3df(0, 0, 0)    //!< lookat

                    );*/

    _camera->setPosition( _player->_walkyrie->_cameraRecul );

    scene()->setActiveCamera(_camera);

}



//! Render a frame
// en gros l'ecran a une taille de 60
void
CSinglePlayerState::Draw(){

    _LOG_DEBUG << "starting drawing CSinglePlayerState";

    const irr::core::dimension2du& dim =  engine()->getScreenSize();
    TVector3df start , end;

    irr::core::recti area;//(core::position2di(0,0),dim);

//    video::ITexture* warningImg = engine->driver->getTexture("images/warning.jpg");
//

    // d'abord on dessine la scene
    int bandWidth = conf::_SIDE_BAND_PERCENTAGE*dim.Width;
    area.UpperLeftCorner = position2di(bandWidth,0);
    area.LowerRightCorner  = position2di(dim.Width-bandWidth,dim.Height);
    engine()->driver()->setViewPort(area);
    //engine->smgr->setActiveCamera(_cameras[Scene]);


    // Draw scene
    scene()->drawAll();

    _pauseMenu->draw();
    //_gameOverMenu->draw();

    switch( getInnerState() ){
        case NPlayState::Dialog:

            // affiche le texte
            //_dialog.second.getMess
            //_INFO << "drawing dialogTab" ;
            _dialogTab->draw();
            break;


        case NPlayState::StartingLevel:
        case NPlayState::EndingLevel:
            _levelTransitionImage->draw( ENGINE->driver() );
            break;

        case NPlayState::Menu:
            //_INFO << "Displaying menu";
            //enableMenu(_pauseMenu,true);
            //_pauseMenu->draw();
            break;

        case NPlayState::GameOver:
            _gameOverMenu->draw();
            break;
        default:
            break;
    };


    // Left HUD
    //area.UpperLeftCorner    = ;
    //area.LowerRightCorner   = core::position2di(dim.Width,dim.Height);
    engine()->driver()->setViewPort(core::recti(core::position2di(0,0),core::position2di(dim.Width,dim.Height )));
    //DrawLeftHUD(core::recti(core::position2di(0,0), core::position2di(bandWidth,dim.Height )));
    DrawLeftHUD(core::position2di(0,0));
    //DrawRightHUD(core::recti(core::position2di(dim.Width-bandWidth,0), core::position2di(dim.Width,dim.Height )));
    DrawRightHUD(core::position2di(dim.Width-bandWidth,0));


// TODO
/*
    if(  engine()->paused() ){
        _INFO << "menu de pause visible";

        _pauseMenu->setVisible(true);
        _pauseMenu->setEnabled(true);
        _pauseMenu->draw();

        //gui()->setFocus(_pauseMenu);
    }
    else {
//        _pauseMenu->setVisible(false);
//        _pauseMenu->setEnabled( false );
    }

    _gameOverMenu->draw();
//    if(engine()->paused()){
//        // TODO lui donner le focus !
//        gui()->setFocus(_pauseMenu);
//        _pauseMenu->setEnabled(_pauseMenu);
//
//    }
*/

    _LOG_DEBUG << "ending drawing CSinglePlayerState";
}




//_player->getScore()






void
CSinglePlayerState::onHold(){


}


/// Create main menu ( = 1st to be displayed )
// Faire un menu de taille dynamique
// Ptet ajouter un bouton restart ?
void
CSinglePlayerState::GUI_CreatePauseMenu() {

    //irr::core::recti tmp(0,0,600,400);
    irr::core::recti tmp(0,0,0,0);
    core::recti rectButton = conf::_MENU_BUTTON_RECT;//(0,0,_BUTTON_WIDTH,_BUTTON_HEIGHT);
//,gui()->getRootGUIElement()
    _pauseMenu 	= gui()->addTab(tmp);
    _pauseMenu->setRelativePositionProportional(core::rectf(0.4f,0.4f,1.f,1.f));



	// faudriat les mettre dans un mm container
	gui()->addButton(rectButton, _pauseMenu, NGuiIds::BackToGame,
			L"Back to game", L"Back to game");
//    _MENU_DECAL_RECT(rectButton);
    rectButton += conf::_BUTTON_GAP;

    gui()->addButton(rectButton, _pauseMenu, NGuiIds::Options,
			L"Options", L"Go to options");
    rectButton += conf::_BUTTON_GAP;
//	gui->addButton(rect<s32>(10,320,110,320 + 32), 0, NGuiIds::Credits,
//			L"File Open", L"Opens a file");

	gui()->addButton(rectButton, _pauseMenu, NGuiIds::QuitGame,
			L"Quit game", L"Exits game");
}


void
CSinglePlayerState::GUI_CreateEditorTab() {



    irr::core::recti rect(0,0,0,0);
    core::recti rectButton = conf::_MENU_BUTTON_RECT;//(0,0,_BUTTON_WIDTH,_BUTTON_HEIGHT);

    _editorTab 	= gui()->addTab(rect, gui()->getRootGUIElement() );
    _editorTab->setRelativePositionProportional(core::rectf(0.2f,0.2f,0.8f,0.8f));


//const wchar_t *text, const core::rect< s32 > &rectangle, bool border=true, IGUIElement *parent=0, s32 id=-1)=0
    gui()->addEditBox (L"Editor", rect, true, _editorTab );

//addTabControl (const core::rect< s32 > &rectangle, IGUIElement *parent=0, bool fillbackground=false, bool border=true, s32 id=-1)=0
	// faudriat les mettre dans un mm container
	// Sauver / Fermer
	//gui()->addButton(rectButton, _gameOverMenu, NGuiIds::ContinueGame,L"Continue", L"Continue game");
    //rectButton += conf::_BUTTON_GAP;



}



void
CSinglePlayerState::GUI_CreateGameOverMenu() {

    irr::core::recti tmp(0,0,0,0);
    core::recti rectButton = conf::_MENU_BUTTON_RECT;//(0,0,_BUTTON_WIDTH,_BUTTON_HEIGHT);

    _gameOverMenu 	= gui()->addTab(tmp,gui()->getRootGUIElement());
    _gameOverMenu->setRelativePositionProportional(core::rectf(0.4f,0.4f,1.f,1.f));



	// faudriat les mettre dans un mm container
	gui()->addButton(rectButton, _gameOverMenu, NGuiIds::ContinueGame,
			L"Continue", L"Continue game");
    rectButton += conf::_BUTTON_GAP;


    gui()->addButton(rectButton, _gameOverMenu, NGuiIds::SaveScore,
			L"Save score", L"Save score");
    rectButton += conf::_BUTTON_GAP;
//	gui->addButton(rect<s32>(10,320,110,320 + 32), 0, NGuiIds::Credits,
//			L"File Open", L"Opens a file");

	gui()->addButton(rectButton, _gameOverMenu, NGuiIds::QuitGame,
			L"Quit game", L"Exits game");
}










void
enableMenu( irr::gui::IGUITab* tab, const bool& enable)
{
    //
//    _INFO << "Enable menu [" << tab << "] or not: [" << enable << "]";
    tab->setVisible(enable);
    //tab->setEnabled(enable);
    //engine()->showCursor(enable);
}


/// \function HandleEvents
bool
CSinglePlayerState::OnEvent(const irr::SEvent& event){



//    if(engine->_player->_input.update(event)){
//        return false;
//    }

//    if( _playState== NPlayState::Dialog){
//        //gauche
//        //droite
//        //bas
//        //haut
//
//        // Go to next questions
////        if( _player->_input->getState(NPlayerInput::MainShoot ) ){
////
////        }
//        return true;
//    }


    //! According to event type
    switch(event.EventType){

        // Handle keys
        case EET_KEY_INPUT_EVENT :

            // check that's no key up
            if(!event.KeyInput.PressedDown)
                return false;

            switch (event.KeyInput.Key){



                case irr::KEY_ESCAPE:

                    if(getInnerState() == NPlayState::Menu){
                        _INFO << "restorePreviousState";
                        restorePreviousState();
                    }
                    else {

                        _INFO << "change state";
                        changeState(NPlayState::Menu);
                    }



                    //_INFO << "Pause";
        //_pauseMenu->setEnabled(_pauseMenu);
//!_pauseMenu->isVisible()
//                    if(engine()->SwitchBit(NBit::Pause)){
//
////                        _pauseMenu->setVisible(true);
////                        _pauseMenu->setEnabled(true);
//                        //gui()->setFocus(_pauseMenu);
//                        enableMenu( _pauseMenu , true );
//                    }
//                    else {
//                        enableMenu( _pauseMenu , true );
////                        _pauseMenu->setVisible(false);
////                        _pauseMenu->setEnabled( false );
//                    }
                    return true;

                // Cree une explosion
                // sous forme de sprite
                // Activate editor
                case irr::KEY_KEY_E:

                    _INFO << "activate editor";
                    _INFO << "add sprite explosion (disabled)";
                    //_levelMgr.addSpriteExplosion(irr::core::vector3df(5,0,0));

                    break;


                // TODO afficher un shader de blur
                case KEY_KEY_B:
                    _INFO << "TODO: activer shader";
                    break;

                case KEY_F2:

                    _INFO << "Switch freeflight camera";
                    // si on vient d'activer le mode free camera
                    if( engine()->SwitchBit(NBit::FreeFlight)){

                        // pauses game
                        //SwitchBit(NBit::Pause,true);
//                        scene::ICameraSceneNode* cam = smgr->setCamera();
//                        _cameras.push(cam);
                        scene()->setActiveCamera( engine()->_fpsCamera  );

                    }
                    else {
                        scene()->setActiveCamera(_camera  );
                    }
                    break;

                // cree une explosion avec spark
                case irr::KEY_KEY_G:
                    {
                    //boost::any pos;
                    //engine()->addMessage(NMessageType::CreateExplosion,pos);

                    //_levelMgr.addExplosion(irr::core::vector3df(5,0,0));
                        _INFO << "Add spark explosion";
                    //engine()->_particleManager
                        //ISceneNode* node = CGameEngine::getParticleManager()->createExplosion();
                        //node->setParent( scene()->getRootSceneNode() );
                        addSimpleExplosion( TVector3df(0,0,0) );
                        this->shakeCamera();
                    }
                    break;

                case irr::KEY_KEY_N:

                    shakeCamera();

                    break;

                // Tue le joueur
                case irr::KEY_KEY_M:

                    _INFO << "Mort du joueur";
                    _player->kill();
//                    getLevelManager().updateState();
                    break;

                // Reload
                case irr::KEY_KEY_R :
                    if(event.KeyInput.PressedDown){
                        // TODO reload script de base

                        _INFO << "Reloading Lua Context & level...";
                        _initialized = (setupLuaThread() && reloadLevel() );
                        if(_initialized){
                            _INFO << "Reset successful";
                        }
                        else {
                            _LOG_WARNING << "Reseting context failed";
                        }
                    }
                    break;

                // Reload
                case irr::KEY_KEY_D :
                // TODO tuer le joueur
                    //_player.Kill();
                    //_INFO << "setPlay state to dead";
                    //getLevelManager()._playState = CLevelManager::PlayerDead;

                    break;

                default:
                    break;
            }
            break;

        // HAndle GUI events
        case EET_GUI_EVENT:
            if(event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED){
                {
                    _INFO << "button clicked";
                    irr::s32 id = event.GUIEvent.Caller->getID();

                    switch(id) {
                        case NGuiIds::BackToGame:
                            //engine()->SwitchBit(NBit::Pause,false);
                            //_pauseMenu->setVisible(false);
                            break;

                        case NGuiIds::Options:
                            //TGameStatePtr optionsState(new COptionState(core::rectf(0.2f,0.2f,0.8f,0.8f)) );
                            pushState(NStateId::Options);
                            //engine()->pushEvent(NStateEvent::PushState,NStateId::Options);
                            break;

                        case NGuiIds::SaveScore:
                            {
//
//                                this->popThisState();
//                                this->pushState();
/*
                                // donne la possibilité au joueur
                                // d'enregistrer son score
                                this->remove();
                                TGameStatePtr menuState(new CMenuState());
                                engine()->PushState( menuState );
                                //true,

                                CScoreState* scoreState = new CScoreState(core::rectf(0.2f,0.2f,0.8f,0.8f)) ;
                                TGameStatePtr scoreStatePtr(scoreState);
                                engine()->PushState( scoreStatePtr );
                                //if( state->getMinScore() < _player->getScore())
                                scoreState->displayAddScore( _player->getScore() );
                                */
                            }
                            break;

                        case NGuiIds::ContinueGame:
                            // mettre a jour les stats
                            //_player->_stats.Deaths++;
                            //enableMenu(_pauseMenu, false);
                            _player->setupForNewGame();
                            //_player->_stats
                            break;

                        case NGuiIds::QuitGame:
                            _INFO << "Exiting game from singleplayer state";
                            engine()->Quit();

                        default:
                            break;
                    };
                }
            }
            break;

        default:
            break;
    }// end 1nd switch

    return false;
}



