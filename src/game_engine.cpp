/**
* \file GameEngine.cpp
*
*/
#include "game_engine.hpp"
#include "IEngineConfig.hpp"
#include "config.hpp"
#include <fusion/core/CStringBuilder.hpp>
#include <fusion/core/string.hpp>
#include "audio/ISound.hpp"
#include "config.hpp"
#include "entities/player.hpp"
#include "CGraphicalLevel.hpp"
#include <utf8.h>
#include "utils/CParticleManager.hpp"
//#include "audio/CFModExDriver.hpp"
#include "audio/ISoundManager.hpp"
#include "audio/IAudioDriver.hpp"
#include "entities/IMultiModeTransformer.hpp"
#include "states/IGameState.hpp"
#include "states/IdList.hpp"
#include "events/CInputManager.hpp"
#include "utils/IGUIConsole.hpp"
#include  <xeffects/XEffects.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace fus;


//fus::NLogLevel::EId CGameEngine::_irrlichtLogLevelsMap[irr::ELL_NONE + 1];

//void
//updatePlayersDescriptors( const SIngameConfig::TMapping& mapping, CPlayer& player) {
//
//    //player.setDescriptors()
//    //BOOST_FOREACH()
//    for ( auto i = 0; i < NPlayerInput::Count;++i ){
//        player._mappingSet.addBind( static_cast<NPlayerInput::EId>(i), mapping[i]);
//    }
//}


CGameEngine::TParticleManager CGameEngine::_particleManager;
CGameEngine::TSpriteManager CGameEngine::_spriteManager;
//CGameEngine::TSoundManager CGameEngine::_soundManager;

//
CGameEngine::TBiMap CGameEngine::_videoDrivers;




// Function Init()
CGameEngine::CGameEngine() :
IGameEngine(),
_device( 0 ),   // nullptr
_debugDataElement(0),
_fpsCamera(0),
mLastTime(0),
_driver(0),
_smgr(0),
_inputManager( new CInputManager()),
_console(0),
mElapsedTime(0),
IStateManager(),
//_postProcessingEffect(0),
// TEMPORAIRE:audio::CFModExDriver::instance()
_soundManager( 0 ),
_messageBoxesTab(0)
//_internalState(NEngineState::Uninitialized)
   // mRenderingMode(Fill)
{

    //createIrrlichtDevice();
    //registerGUIElementFactory
    EngineConfig.DriverType = conf::_DEFAULT_VIDEO_DRIVER;
}


bool
CGameEngine::isCursorShown() const {

    return _device->getCursorControl()->isVisible();
}


void
CGameEngine::setLogLevel( const fus::NLogLevel::EId& level ) {

    Logger::reportingLevel() = level;
    //getLogger()->setLogLevel();
    _device->getLogger()->setLogLevel( convertFusionLogLevel( level ) );
}


fus::NLogLevel::EId
convertIrrlichtLogLevel( const  irr::ELOG_LEVEL& level ){

    switch(level){


        case irr::ELL_WARNING:      return fus::NLogLevel::Warning;
        case irr::ELL_ERROR:        return fus::NLogLevel::Error;
        case irr::ELL_NONE:         return fus::NLogLevel::None;
        case irr::ELL_INFORMATION:
        default:                    return fus::NLogLevel::Notice;

    };
}

irr::ELOG_LEVEL
convertFusionLogLevel( const fus::NLogLevel::EId& level ){

    switch( level ){


        case fus::NLogLevel::Warning:      return irr::ELL_WARNING;
        case fus::NLogLevel::Error:        return irr::ELL_ERROR;
        case fus::NLogLevel::None:         return irr::ELL_NONE;
        case fus::NLogLevel::Notice:
        default:                           return irr::ELL_INFORMATION;
    };
}



//const char* str,
//int
//CGameEngine::Run(TLoadConfigFromFileFunction fn){
//
//    //irr::SIrrlichtCreationParameters irrlicht;
//    //SIngameConfig&,const SAudioParameters&
//    try {
//    if( *fn( EngineConfig, GameConfig, AudioConfig ) == false){
//
//        _LOG_ERROR << "Could not load config";
//        return EXIT_FAILURE;
//    }
//    }
//    return Run();
//}



//const TEngineParameters& engineParam,const SIngameConfig& gameConfig,const SAudioParameters& audioParam
// TODO renvoyer un int avec plusieurs codes d'erreurs ?
int
CGameEngine::Run() {

//    if( _internalState == NEngineState::Uninitialized ){
//
//        // TODO alors ici on initialise avec les valeurs par defaut !!
//        //-supprimer les dependances XML, tout gerer avec lua
//        _LOG_ERROR << "You have to initialize the engine first";
//        return false;
//    }


    try {
        //createIrrlichtDevice(engineParam);
        InitEngine();

        this->synchronize();


        /// While irrlicht engine active and state available
        while( _device->run() && !isStackEmpty() ){

            this->synchronize();

            this->Update();
            this->Flush();
        }
        return true;
    }
    catch(std::bad_alloc& e){

    }
    catch(std::runtime_error& e){
        _LOG_ERROR  << "Runtime error" << e.what();
    }
    //std::invalid_argument
    //luabind::error
    //
    catch(std::exception& e){
        //exit()
        _LOG_ERROR << e.what();
    }
    catch(...){
        //_LOG_ERROR [ "Uncatched exception"  << "test" ]
        _LOG_ERROR << "Uncatched exception" ;
    }

    //TODO
    //this->CleanUp();

    return false;
};



//bool
//CGameEngine::switchConsoleState() {
//
//    if( switchBit(NBit::Console) ) {
//
//
//    }
//}
//


//void
//CGameEngine::pushCustomEvent(const int& userData1,const int& userData2) {
//
//    TGameStateEvent event(eventType);
//    //event.UserData1 = ;
//    event.UserData2 = userData2;
//
//
//    _device->postEventFromUser(event);
//}

// helper function/wrapper for utf8
void
CGameEngine::popupMessage(const wchar_t* shortDescription,const std::string& longDescription){

    std::wstring temp;
    fus::convertIntoWideString(longDescription,temp);
    popupMessage(shortDescription, temp.c_str() );
}




void
CGameEngine::popupMessage(const wchar_t* caption,const wchar_t* longDescription){

    _internalState = NEngineState::Error;


    gui::IGUIWindow* window = gui()->addMessageBox(
                                        caption,            // title
                                        longDescription,    // description
                                        true,               // modal
                                        gui::EMBF_OK,        // type
                                        //EMBF_OK|EMBF_CANCEL
                                        _messageBoxesTab                //parent
                                        );
    _messageBoxesTab->addChild(window);
    _messageBoxesTab->setVisible(true);


    // Put it in front of others
    gui()->getRootGUIElement()->bringToFront(_messageBoxesTab);

    //_INFO << "Popping up  message box [" << window << "]";
    //const wchar_t*
    _LOG_ERROR << "Messagebox error:" << longDescription ;

    this->showCursor(true);
}





//bool startScript(const char* scriptFilename);
void
CGameEngine::getAvailableVideoDriverList(std::vector<std::wstring>& list) {

    list.clear();

    // let => int, right => wstring
    BOOST_FOREACH( TBiMap::right_const_reference p, _videoDrivers.right )
    {
        //p.second <<
//        _INFO << "test" << p.second;
        list.push_back(p.first);
    }


}



// TODO a corriger !!
void
CGameEngine::setCamPos(const float& x,const float& y,const float& z){

    TVector3df vec(x,y,z);
    getCamera()->setPosition( vec );
}


void
CGameEngine::setCamTarget(const float& x,const float& y,const float& z){

    TVector3df vec(x,y,z) ;
    getCamera()->setTarget( vec );
}



//irr::scene::ICameraSceneNode*
//switchFreeFlightCamera() {
//
//}

// Parcourt tous les elements et les autoscale
void
CGameEngine::enableGUIAutoScale(IGUIElement* element) {

//    irr::gui::IGUIElement* root = _gui->getRootGUIElement ();
//    if(root){
//        root->setAlignment( EGUIA_SCALE, EGUIA_SCALE, EGUIA_SCALE, EGUIA_SCALE);
//    }
    //setRelativePositionProportional
    // Left / Right   : Top/Bottom
    //button->setAlignment( EGUIA_SCALE, EGUIA_SCALE, EGUIA_SCALE, EGUIA_SCALE);
}


void
CGameEngine::logDebugInformations()
{


    const irr::IOSOperator* os = _device->getOSOperator();

    _INFO << "Irrlicht version:\t" << _device->getVersion() << "\n"
           << "Type:\t" << _device->getType () << "\n"
           << "OS informations: " << os->getOperationSystemVersion()
           << "Driver info:\t" << _driver->getVendorInfo().c_str() << "\n"
           //COpenGLExtensionHandler
           << "Mipmap enabled" << _driver->queryFeature(EVDF_MIP_MAP )
           << "Liste des drivers supportes: Not available";

//isDriverSupported (video::E_DRIVER_TYPE driver)
//EDT_OPENGL
}




// Create player preciser index ?
bool
CGameEngine::createPlayer(){

//this,
//config->_mappingSetGameConfig.PlayerKeys

    _player.reset( new CPlayer(  ) );

    //_player->createBoosters();

    return true;
}




// TODO a revoir
// restartGraphicalDevice
void
CGameEngine::closeIrrlichtDevice(){

    // If already exists
    if(_device){

        //serialize world
        _smgr->saveScene(_BC_BACKUP_SCENE);
        //serialize gui
        _gui->saveGUI(_BC_BACKUP_GUI);

        // Sauvegarder la scene avant
        _device->closeDevice();
        _device->run();
        _device->drop();

        _driver = 0;
        _smgr   = 0;
        _gui = 0;

        //_fpsCamera->remove();
    }
}







bool
CGameEngine::setFont(const std::string& fontPath){

    IGUISkin* skin = _gui->getSkin();
    IGUIFont* font = _gui->getFont(fontPath.c_str());
    if (font){
        skin->setFont(font);
        return true;
    }
    else{
        skin->setFont(_gui->getBuiltInFont(), EGDF_TOOLTIP);
        return false;
    }

}

// time in ms
TTimer::TimeType
CGameEngine::getElapsedTime() const
{

    #ifdef _BC_DEBUG
        return 7;
    #endif

    if(getBoolean(NBit::BulletTime) ){
        //TODO a check
        return (mElapsedTime / 10.f);
    }
    return mElapsedTime;
};



// TODO: pouvoir passer le chemin où enregistrer l'image avec boost::filesystem
void
CGameEngine::TakeScreenshot(const std::wstring& name){


    IImage* img = _driver->createScreenShot();

    static int counter = 0;

    counter++;;
    // test =
    irr::io::path filename=fus::TWCharStringBuilder(name)(counter)(".jpg").str().c_str();

    _driver->writeImageToFile(img,filename);
}



/// \function Draw
/// Draw things commun to each state and then draw specific state
void
CGameEngine::Flush(){

    /// Draw FPS when enabled in config file
    //if(CConfigManager->getSetting("show_data")){
/*
        core::stringw str = L"Irrlicht Engine [";
        str += (s32)driver()->getFPS();
        //_gui->addStaticText(L" renderer!",rect<s32>(10,10,260,22), true);
        str +=  "]\nPrimitives:";
        str +=  driver()->getPrimitiveCountDrawn();
        str += "\nPlayer: ";
        str += _player->getPosition().X;
        str += ", ";
        str += _player->getPosition().Y;
        str += ", ";
        str += _player->getPosition().Z;
        ICameraSceneNode* cam =  _smgr->getActiveCamera();
        if(cam){
            str += "\nCam Position:";
            str += cam->getPosition().X;
            str += ", ";
            str += cam->getPosition().Y;
            str += ", ";
            str +=cam->getPosition().Z;
            str += "\nCam Target:";
            str += cam->getTarget().X;
            str += ", ";
            str += cam->getTarget().Y;
            str += ", ";
            str +=cam->getTarget().Z;
            str += "\nCam rotation:";
            str += cam->getRotation().X;
            str += ", ";
            str += cam->getRotation().Y;
            str += ", ";
            str +=cam->getRotation().Z;
            str += "\nElapsed time(ms): ";
            str += mElapsedTime;
            //str += "\nPlayer speed:";
            //str += mElapsedTime;
            //_gui->addStaticText(str.c_str(),rect<s32>(0,0,200,60), true);
            updateDebugData("cam",str);
            //_INFO <<  str.c_str();
        }

    //}

    _debugDataElement->setText(str.c_str());
    _debugDataElement->setRelativePosition (core::position2di(50,0));
*/


//, SColor(255,100,101,140)
// Peut etre a supprimer et a laisser dans les states inferieurs ?
	driver()->beginScene(true, true);


    getCurrentState()->Draw();
    //_spriteManager->draw2Dsprites();

    //_debugDataElement->draw();


    //if( getBoolean(NBit::Console) ){
        //_INFO << "console active";
        //gui()->setFocus(_console);
        //_INFO << "Console isVisible" << _console->isVisible();
        //_INFO << "Console isVisible" << _console->isVisible();
        _console->draw();
        //_INFO << "Drawing console";
    //}


//    if(_internalState == NEngineState::Error){
//        //_INFO << "Drawing error";
        _messageBoxesTab->draw();
//    }


    driver()->endScene();


}


bool
CGameEngine::eventToMainHandler(const SEvent& event){


    // Pass onto player eventsss
//    _player->OnEventForPlayer(event);

    //HandleEvents(){
    switch (event.EventType ){

        case EET_GUI_EVENT:
            {


            //s32 id = event.GUIEvent.Caller->getID();
            gui::IGUIElement* caller = event.GUIEvent.Caller;
            const gui::IGUIElement* element = event.GUIEvent.Element;
            //->getParent();

            switch(event.GUIEvent.EventType){

/*
                case gui::EGET_ELEMENT_HOVERED:
                    //EGUIET_WINDOW
                    //EGUIET_MESSAGE_BOX
//                    if(caller->getType() == EGUIET_MESSAGE_BOX){
//
//                        _INFO << "messagebox hovered [" << caller << "]";
//                    }
                    //caller->getDebugName()
                    //_INFO << "Element hovered [" << caller << "] of type [" << caller->getType() << "messageBox [" << _messageBoxesTab << "]";
                    break;
*/
                case gui::EGET_ELEMENT_FOCUSED:
                    // EGUIET_MODALSCREEN ->getType()

                    //_INFO << "caller" << caller->getText();
//                    _INFO << "caller" << caller->getTypeName();
                    {
                        std::string result;
                    convertIntoNarrowString( caller->getText(), result);

                    //_INFO << "caller" << caller;
                    _INFO << "caller text" << result;
                    //_INFO << "caller debug name" << caller->getDebugName ();
                    //_INFO << "caller debug name" << caller->getTypeName();
                    _INFO << "caller ID" << caller->getID ();
                    //_INFO << "caller type" << caller->getID ();
                    }
//                    if(element){
//                        _INFO << "element" << element->getTypeName();
//                    }
                    break;

                case gui::EGET_EDITBOX_ENTER:
                    _INFO << "EVENT EGET_EDITBOX_ENTER RECEIVED";
                    /// verifier que ca vient de la console
                    if(caller->getID() == NGuiIds::Console){
                        std::string temp;
                        // TODO ne pas flusher l'editbox avant
                        // distinguer commande de leur resultat ?
                        convertIntoNarrowString(caller->getText(),temp);
                        _INFO << "Running command [" << temp << "]...\r\n";
                        const bool ret = _vm.RunCommand( temp.c_str() );
                        if(ret){
                            dynamic_cast<IGUIConsole*>(caller)->flushCommand();
                        }
                        else {
                            // TODO on genere une erreur
                            // popupMessage
                        }
                    }
                    break;

                case gui::EGET_MESSAGEBOX_OK:

                    _INFO << "Message box ok detected";
                    // TODO checker qu'il n'y a plus d'enfant
                    // if( _messageBoxesTab->isMyChild (caller)) {
                    if( (caller->getParent() == _messageBoxesTab) ){

                        _INFO << "caller is child of messageBox";
                        //caller->remove()

                        if( _messageBoxesTab->getChildren ().empty() ){

                            //
                            _internalState = NEngineState::Running;
                            _messageBoxesTab->setVisible(false);
                        }
                        return false;
                    }


                    break;



                default:
                    //_INFO << "GUI EVENT NOT HANDLED";
                    break;
            };
            }
            break;

        /// En cas de Log
//        case EET_LOG_TEXT_EVENT:
//            // TODO checker pk ca marche pas
//            //{
//                //const fus::ELogLevel level = convertIrrlichtLogLevel(event.LogEvent.Level);
//                _INFO << "IRRLICHT EVENT";
//                fus::ILogger::Log(convertIrrlichtLogLevel(event.LogEvent.Level)) << event.LogEvent.Text;
//            //}
//            return true;


        case EET_KEY_INPUT_EVENT :
            if(!event.KeyInput.PressedDown)
                return false;

            //if()

            // et checke si elle est pressee
            switch (event.KeyInput.Key){

//                case irr::KEY_ESCAPE: // switch wire frame mode
//                    //Quit(ELL_INFORMATION,"escape pressed");
//                    SwitchBit(NBit::Pause);
//                    //return true;

                case KEY_F1:
                    // Activate console !
                    _INFO << "Switch console";
// TODO la mettre sous forme de state ?
                    // TODO
                    //_internalState = NEngineState::Console;
                    //bool result =
                    _console->setVisible( SwitchBit(NBit::Console) );
                    //gui()->setFocus(_console);
//                    if( SwitchBit(NBit::Console) ){
//                        gui()->setFocus( _console );
//                    }


                    return true;

//                case KEY_F2:
//
//                    _INFO << "Switch freeflight camera";
//                    // si on vient d'activer le mode free camera
//                    if(SwitchBit(NBit::FreeFlight)){
//
//                        // pauses game
//                        //SwitchBit(NBit::Pause,true);
//                        scene::ICameraSceneNode* cam = _smgr->setCamera();
//                        _cameras.push(cam);
//
//                        _smgr->setActiveCamera(_mainCamera);
//                        _mainCamera->setPosition(cam->getPosition());
//                        _mainCamera->setTarget(cam->getTarget());
//
//                    }
//                    else {
//                        // resumes game
//                        //SwitchBit(NBit::Pause,false);
//                        if(_cameras.size()){
//                            if(_cameras.top()){
//                                _smgr->setActiveCamera(_cameras.top());
//                                _cameras.pop();
//                            }
//                        }
//                    }
//                    break;

                case KEY_F3:
                    // Activate bullet time !
                    _INFO << "Switch bullet time";
                    SwitchBit(NBit::BulletTime);

                    return true;


                case KEY_F5:

                    _INFO << "switchin' to fullscreen mode (disabled)";
                    SwitchBit(NBit::Fullscreen);
                    //_INFO << "new fullscreen/test" << fullscreen << "/" << test;

                    //createIrrlichtDevice(EDT_OPENGL);
                    return true;


                case KEY_F6:
                case KEY_F7:
                //
                    {


                    SwitchBit(NBit::DebugData);
                    //_debugDataElement->setVisible( );
                    }
                    return true;

                // TODO wireframe mode
                case KEY_F8:
                    {

                    _INFO << "switching between wireframe mode etC.. ";
                    const bool wireframe = SwitchBit(NBit::WireFrame);
                    if(wireframe){
                        //_smgr->getRootSceneNode()->setMaterialFlag(video::EMF_WIREFRAME,wireframe);
                        _player->_node->setMaterialFlag(video::EMF_WIREFRAME,wireframe);
                        //_player->_animatedNode->setMaterialFlag(video::EMF_POINTCLOUD, false);
                    }
                    else {
                        //_smgr->getRootSceneNode()->setMaterialFlag(video::EMF_WIREFRAME,wireframe);
                        _player->_node->setMaterialFlag(video::EMF_WIREFRAME,wireframe);
                        //_smgr->getRootSceneNode()->setMaterialFlag(video::EMF_POINTCLOUD, true);
                    }
                    }
                    return true;

                // TODO Afficher les hitboxes
                case KEY_F9:
                    //
                    _INFO << "switching display of hitboxes";
                    SwitchBit(NBit::DisplayHitCircles);
                    return true;

                // afficher les BB
                case KEY_F10:
                    return true;

                case KEY_F12:
                    TakeScreenshot(L"screenshot");
                    return true;


                default:
                    // Si jamais la console est activee

                    break;
            };

            break;



        default:
            break;
    }


    return false;
}



/*
 EGET_MESSAGEBOX_YES,
 EGET_MESSAGEBOX_NO,
 EGET_MESSAGEBOX_OK,
 EGET_MESSAGEBOX_CANCEL,
*/
/**
* Handle generic actions first ( that is common to every state ) and then state-specific events

**/
bool
CGameEngine::OnEvent(const SEvent& event){

    //_device->getTimer()->getTime()
    if(_inputManager->handleEvent(  event)){
        return true;
    }


    if(event.EventType == EET_LOG_TEXT_EVENT ){


            fus::NLogLevel::EId level  = fus::NLogLevel::Notice;
            switch(event.LogEvent.Level){
                case irr::ELL_INFORMATION:  level = fus::NLogLevel::Notice; break;
                case irr::ELL_WARNING:      level = fus::NLogLevel::Warning; break;
                case irr::ELL_ERROR:        level = fus::NLogLevel::Error; break;
                case irr::ELL_NONE:         level = fus::NLogLevel::None; break;
            };

    //        _INFO << "IRRLICHT EVENT";
            fus::Logger::Log(level) << event.LogEvent.Text;

            return true;
    }



//    // If console enabled
//    if(mBitSet[NBit::Console]){
//
//        return eventToConsoleHandler(event);
//
//    }
//    // else
//    else
//
    if(eventToMainHandler(event)){
        _INFO << "Event processed by main handler";
        return true;
    }
    else if(!isStackEmpty()){

        // If there is an active state


        // let state handle it
        if(getCurrentState()->OnEvent(event)){
            _INFO << "Event processed by state";
            return true;
        }

    }



    //let irrlicht handles event
    return false;
}//end of function




//template<typename T>
//irr::core::vector2d<T>
//CGameEngine::getAbsoluteDimension(const float& x,const float& y) const {
//
//    return irr::core::vector2d<T>(x*driver->getScreenSize().Width,y*driver->getScreenSize().Height);
//}

//getAbsoluterectangle(const irr::core::rect<f32>& rect){
irr::core::rect<s32>
CGameEngine::getAbsoluteRectangle(const float& x,const float& y, const float& x2,const float& y2) const{
    irr::core::rect<s32> tmp;
    tmp.UpperLeftCorner = getAbsoluteDimension<s32>(x,y);
    tmp.LowerRightCorner = getAbsoluteDimension<s32>(x2,y2);
    //tmp.UpperLeftCorner +
    return tmp;
}




irr::core::position2di
CGameEngine::getCenteredPosition(const irr::core::dimension2du& dimRect) const
{

//constrainTo
    const irr::core::dimension2du& screen = _driver->getScreenSize();
// getscreensize() renvoie un dimension2du
    irr::core::position2di pos;//(dimRect.Width);
    if( screen.Width < dimRect.Width ){
        pos.X = -(dimRect.Width -screen.Width);
    }
    else {
        pos.X = screen.Width - dimRect.Width;
    }

    if( screen.Height < dimRect.Height ){
        pos.Y = -(dimRect.Height -screen.Height);
    }
    else {
        pos.Y = screen.Height - dimRect.Height;
    }
   // temp.Y = (driver->getScreenSize().Height - std::max(screen.Height, dimRect.Height));
    pos /= 2;

    return pos;
}



bool
CGameEngine::addVideoDriverIfSupported( const std::wstring& name, const TVideoDriverId& id ){

    if(IrrlichtDevice::isDriverSupported(id)){
        _videoDrivers.insert( TKeyAssociation(id,name) );
        return true;
    }
    return false;
}



//CConfigManager::initializeDictionaries
bool
CGameEngine::getVideoDriverFromName(const std::wstring& wname,TVideoDriverId& id){

    try {
        //TMappings::left_mconst_iterator _keyMap.left.find(keyCode);
        _videoDrivers.right.at( wname );
        return true;
    }
    catch( std::out_of_range & e ) {
        std::string name;

        convertIntoNarrowString(wname,name);
        _LOG_ERROR << "Couldn't find id associated with name [" <<  name << "] in keyCodeToString";
        return false;
    }
}



//void
//CConfigManager::addAudioDriver(){
//
//}


CGameEngine::~CGameEngine(){

    _device->drop();
}



//bool
//CGameEngine::loadConfig(const char* filename) {
//
//    _INFO << "TODO load config from lua scruipt";
//}
//





/// \function CleanUp()
void
CGameEngine::CleanUp(){

    IStateManager::CleanUp();
}




/// \function Update()
void
CGameEngine::Update(){



    ///////////////////////////////////////
    ////  Update timer
    ///////////////////////////////////////
    u32 now = _device->getTimer()->getTime();
    mElapsedTime = (now-mLastTime);
    mLastTime = now;


    if( _internalState != NEngineState::Running){

        return;
    }

    ///////////////////////////////////////
    ////  Update sound
    ///////////////////////////////////////
    getSoundManager()->update();


    ///////////////////////////////////////
    ////  Treat state event queue
    ///////////////////////////////////////
    // fait dans Run
    //synchronize();

    ///////////////////////////////////////
    ////  Update window
    ///////////////////////////////////////
    #ifdef NDEBUG
    //#error test
    if( _device->isWindowActive()) {
    #endif

    // Won't update if on pause or console active
    // TODO that should update but with a time of 0 !
//        if(paused() || consoleEnabled() )
//            return;

        // Otherwise update state
        _LOG_DEBUG << "Updating state";
        getCurrentState()->Update();


        //_spriteManager->update(getElapsedTime());
        getSoundManager()->update();

    #ifdef NDEBUG
    }
    else {
        _device->yield();
    }
    #endif
}






/// \function Quit
/// Log why quitting ( user asked,error... ) and set running to false to break while
// Lui permettre d'interrompre tt type de script ( qui sont lancés alors en thraed ?
void
CGameEngine::Quit(){

    if( _device ){
        _device->closeDevice();
    }
}



//const TEngineParameters& engineParam,const SIngameConfig&,const SAudioParameters&
bool
CGameEngine::InitEngine(){


    // Ces 3 la suffisent
//    addVideoDriverIfSupported(L"OpenGL",EDT_OPENGL);
//    addVideoDriverIfSupported(L"Direct3D9",EDT_DIRECT3D9);
//    addVideoDriverIfSupported(L"Direct3D9",EDT_DIRECT3D8);

//    // Try to
//    //_LOG_DEBUG << "get irrlicht parameters";
//    config->getIrrlichtParameters(parameters);
//
//    if(!getVideoDriverFromName(config->_videoDriver, parameters.DriverType) || (!irr::IrrlichtDevice::isDriverSupported(parameters.DriverType)) ){
//
//        _LOG_WARNING << "driver [" << parameters.DriverType << "] unsupported";
//        parameters.DriverType = conf::_DEFAULT_VIDEO_DRIVER;
//
//    }
//

    //_INFO << "Using video driver [" << engineParam.DriverType << "] ";



    /////////////////////////////////////
    ///// Initialisation d'irrlicht
    /////////////////////////////////////
    //_LOG_DEBUG << "create irrlicht device";
    if( !createIrrlichtDevice( ) ){
        throw std::runtime_error("Couldn't create irrlicht device");
        //"Could not create device"
        //_LOG_ERROR << "Couldn't create irrlicht device";
        return false;
    }


    /////////////////////////////////////
    ///// Soundmanager Initialisation
    /////////////////////////////////////
    // -- Init audio manager
    //_INFO << "Audio driver" << config->_audioDriver;
    _soundManager = createSoundManager(AudioConfig);
    //_soundManager.reset( new CSoundManager(AudioConfig) );
    //if( !getSoundManager()->init() ){
    if( !_soundManager ){
        _LOG_ERROR << "problem with audio initialization";
    }



    /////////////////////////////////////
    ///// Initialisation of message dispatcher
    /////////////////////////////////////

    if( !bindEverythingToLua( ) ){
        _LOG_WARNING << "Could not initialize lua";
        this->Quit();
        return false;
    }



    // create Player
    // TODO creer le joueur quand on en a besoin ?
    if(!createPlayer()){
        _LOG_WARNING << "Could not create player";
    }

    _internalState = NEngineState::Running;
    _INFO << "Engine created";


    return true;
}



bool
CGameEngine::enableJoysticks(){


//_LOG_WARNING << "test1" << device;
   core::array<SJoystickInfo> joystickInfos;
   // BUG ici
   //_device->activateJoysticks(_joystickInfos);
   //_LOG_WARNING << "test 2";
   if( _device->activateJoysticks(joystickInfos) )
//    if(false)
   {
//        _INFO << "Joystick support is enabled and " << joystickInfo.size() << " joystick(s) are present.";
        _device->getLogger()->log("Joystick support enabled ");
//      for(u32 joystick = 0; joystick < joystickInfo.size(); ++joystick)
//      {
//         std::cout << "Joystick " << joystick << ":" << std::endl;
//         std::cout << "\tName: '" << joystickInfo[joystick].Name.c_str() << "'" << std::endl;
//         std::cout << "\tAxes: " << joystickInfo[joystick].Axes << std::endl;
//         std::cout << "\tButtons: " << joystickInfo[joystick].Buttons << std::endl;
//
//         std::cout << "\tHat is: ";
//
//         switch(joystickInfo[joystick].PovHat)
//         {
//         case SJoystickInfo::POV_HAT_PRESENT:
//            std::cout << "present" << std::endl;
//            break;
//
//         case SJoystickInfo::POV_HAT_ABSENT:
//            std::cout << "absent" << std::endl;
//            break;
//
//         case SJoystickInfo::POV_HAT_UNKNOWN:
//         default:
//            std::cout << "unknown" << std::endl;
//            break;
//         }
//      }
        return true;
   }
   else
   {
      //_INFO << "Joystick support is not enabled.";
      return false;
   }

}

//const irr::video::E_DRIVER_TYPE& driverType,blo::tribool fullscreen,blo::tribool vsync
//TEngineParameters
//TEngineParameters& parameters
bool
CGameEngine::createIrrlichtDevice(){

    TEngineParameters& parameters = EngineConfig;


    //BOOST_ASSERT( irr::IrrlichtDevice::isDriverSupported(parameters.DriverType) );
    if( !irr::IrrlichtDevice::isDriverSupported(parameters.DriverType) ){

        // On passe en BurningVideoSoftware
        parameters.DriverType = EDT_BURNINGSVIDEO;
        _LOG_WARNING << "Driver not supported, trying with BURNINGSVIDEO software driver";
        throw std::runtime_error("Driver not supported");
    }

    bool restart = false;

    _INFO << "using video driver" << parameters.DriverType;

    // If device exists and active
    //&& device->run()
    if(_device ){
        //cleanIrrlichtTiedMembers();
        restart = true;
        closeIrrlichtDevice();
    }


    _device = createDeviceEx(parameters);
//EDT_DIRECT3D9 / EDT_OPENGL / EDT_BURNINGSVIDEO

    if (!_device){
        //_LOG_ERROR << "Could not create device";

        throw std::runtime_error("Could not create device");
        return false;
    }

    // run device once
    _device->run();

    _device->setWindowCaption( conf::_WINDOW_TITLE);
    // Necessaire sinon plante


    //var public
    _driver = _device->getVideoDriver();
    _smgr   = _device->getSceneManager();
    _gui    = _device->getGUIEnvironment();

    // TODO supprimer ce genre de betise ca fait tout foirer
    //recharger la scene
    if(restart){

        if( !_smgr->loadScene(_BC_BACKUP_SCENE)){
            _LOG_ERROR << "Could not load scene";
        }

        if( !_gui->loadGUI(_BC_BACKUP_GUI) ){
            _LOG_ERROR << "Could not load gui";
        }
    }


    irr::core::recti rect(0,0,500,200);


    ///////////////////////////////////////////////////
    ////    Create free flight camera
    ///////////////////////////////////////////////////

    _debugDataElement = _gui->addStaticText(L"Debug data",rect);
    //_debugDataElement->setFont
    _debugDataElement->setVisible(false);


    /////////////////////////////////////
    /////  Setup event reciever
    /////////////////////////////////////
//    CEventManager::setDevice( _device );
    //mEventManager.reset( new CEventManager() );
    //mEventManager.reset( new CInputManager() );

    _device->setEventReceiver( this );
    //mEventManager->AddEventReceiver( this );

    // LogLevel defini dans les parameters normalement
    //_device->getLogger()->setLogLevel( ELL_WARNING ); //EALL_INFO


    ///////////////////////////////////////////////////
    ////    Create console
    ///////////////////////////////////////////////////
    _console = new irr::gui::IGUIConsole(
                                        gui(),
                                        core::recti(0,0, getScreenSize().Width,conf::_CONSOLE_HEIGHT),
                                        gui()->getRootGUIElement(),
                                        NGuiIds::Console
                                        );

    _console->setVisible(false);
    _console->setBackgroundColor( video::SColor(100,100,100,100));

    _console->addButton(L"Test",L"print('Test reussi')");

    // Setup override material
//    SOverrideMaterial& material = driver->getOverrideMaterial();
//    material.Enabled = true;
//    material.EnableFlags = irr::video::EMF_LIGHTING;
//    material.Material.Lighting = false;
//    //setFlag(irr::video::EMF_LIGHTING, false);
//    //E_SCENE_NODE_RENDER_PASS
//    material.EnablePasses = irr::scene::ESNRP_SOLID;
    /////////////////////////////////////
    /////  Setup backup Camera debugCamera
    /////////////////////////////////////
    _fpsCamera = _smgr->addCameraSceneNodeFPS(_smgr->getRootSceneNode(),100.0f,0.05f);
    // changer la vitesse de la camera


    /////////////////////////////////////
    /////  Particle manager
    /////////////////////////////////////
    // #define MessageDispatcher = this
    //this->addListener(this, NMessageType::CreateExplosion);
    //this->addListener(this, NMessageType::CreateExplosion);



    /////////////////////////////////////
    /////  SPrite manager
    /////////////////////////////////////
    _spriteManager.reset( new CSpriteManager( device() ) );

    /////////////////////////////////////
    /////  Particle manager
    /////////////////////////////////////
    _particleManager.reset( new CParticleManager( device() ) );

    /////////////////////////////////////
    /////  Message box setup
    /////////////////////////////////////
    //
//    _messageBoxesTab = gui()->addMessageBox(L"Caption",L"No message",true,gui::EMBF_OK);
// TODO recuperer la surface de l'ecran
    _messageBoxesTab = gui()->addTab( core::recti(0,0,0,0), 0, NGuiIds::ErrorTab );
    _messageBoxesTab->setVisible(false);
    // set whole screen
    _messageBoxesTab->setRelativePositionProportional( core::rectf(0.0f,0.0f,1.f,1.f));

    // TODO a deplacer
    setFont("images/hud.xml");
    return true;
}


