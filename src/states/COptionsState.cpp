/**
* \file options.cpp
*
*/

#include "COptionsState.hpp"
#include "CMenuState.hpp"
#include "../game_engine.hpp"
//#include "../IEngineConfig.hpp"
#include "../config.hpp"
#include <vector>
#include <algorithm>
#include "../utils/CBitSet.hpp"
#include "CErrorState.hpp"
#include <fusion/core/CStringBuilder.hpp>
//#include <fusion/macros.hpp>
#include <xeffects/XEffects.h>
#include "../events/CBindCollection.hpp"
#include "../events/CBindDescriptor.hpp"
#include "../events/CBindFromEventGenerator.hpp"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace input;

#define GET_MAPPING(numero) (*engine()->GameConfig.MappingPlayer1)
//engine()->GameConfig.
#define GENERATE_DESCRIPTION(keymap)  keymap.generateDescription().c_str()

//template<int id,int numero> struct TRANSLATED_ID() { return (id*1000 + 10000 + numero);};
// Numero should be either 0 or 1
int TRANSLATED_ID(const int& id, const int& numero) { return (id*1000 + 10000 + numero);};


std::pair<NPlayerInput::EId,int>
UNTRANSLATE_ID(const int& id) {
    //button1->setText( GET_MAPPING(1)[std::make_pair(id,0)].generateDescription().c_str() );
    int iId = static_cast<int>(id);
    int numero = iId%2;

    return std::make_pair( static_cast<NPlayerInput::EId>( (iId - numero -10000)/1000 ) , numero );
}

/*
inline std::pair<NPlayerInput::EId,std::size_t>
UNTRANSLATE_ID(const int& translatedId) {

    std::pair<NPlayerInput::EId,std::size_t> ret;

    // Keep just units
    ret.second = translatedId%1000;
    ret.first = static_cast<NPlayerInput::EId>( (translatedId - 10000 - ret.second)/1000 );
    //if(translatedId%1000 != 0){
    return ret;
    //}
}
*/



COptionState::COptionState(const irr::core::rectf& pos) :
_pos(pos),
_buttonToUpdate(0)
{

    /// Create initial menu
    GUI_CreateMainMenu();
}




COptionState::~COptionState(){
    _INFO << "OPTIONS DESTRUCTOR";
    _overallTab->remove();
}



void
COptionState::setButtonValue( NPlayerInput::EId const& id) {


    irr::gui::IGUIButton* button1 = 0, *button2 = 0;

    button1 = static_cast<irr::gui::IGUIButton*>( _tabControl->getElementFromId( TRANSLATED_ID(id,0) ,true) );
    button2 = static_cast<irr::gui::IGUIButton*>( _tabControl->getElementFromId( TRANSLATED_ID(id,1) ,true) );

    button1->setText( GET_MAPPING(1)[std::make_pair(id,0)].generateDescription().c_str() );
    button2->setText( GET_MAPPING(1)[std::make_pair(id,1)].generateDescription().c_str() );

}




// engine->driver
void
COptionState::setToConfigValues()
{

    //selectCurrentVideoMode
    IVideoModeList* list = engine()->device()->getVideoModeList();

    //stringw currentMode = videoModeToText(driver->);
    /////////////////////////////////////////////////////////////////
    ///////     select current resolution
    /////////////////////////////////////////////////////////////////
    for(s32 i = 0; i < list->getVideoModeCount(); i += 1){

        //compares 2 core::dimension2d< u32 >
        //driver->
        if((list->getVideoModeResolution(i) ==  engine()->getScreenSize ()))
        {
            _comboBox->setSelected(i);
        }

    }

// -- Graphic Tab
    /////////////////////////////////////////////////////////////////
    ///////     select current resolution
    /////////////////////////////////////////////////////////////////
//    for(std::size_t i = 0; i < NPlayerInput::Count; ++i)
//    {
//        // get specific mapping
//        CBindDescriptor& key = engine()->GameConfig.Keymap1[i];
//
//        irr::gui::IGUIButton* button = static_cast<irr::gui::IGUIButton*>(_tabControl->getElementFromId( (NGuiIds::Count + i) ,true));
//        button->setText( key.generateDescription().c_str());
//        button->setToolTipText(L"Click to change mapping");
//    }

    /////////////////////////////////////////////////////////////////
    ///////     set Control buttons text
    /////////////////////////////////////////////////////////////////
    setButtonValue( NPlayerInput::MoveForward );
    setButtonValue( NPlayerInput::MoveBackward );

    setButtonValue( NPlayerInput::MoveRight );
    setButtonValue( NPlayerInput::MoveLeft );


    // Update checkbox
    //bool checked= engine->config ? 1 : 0;
    IGUICheckBox* box = dynamic_cast<IGUICheckBox*>(_overallTab->getElementFromId(NGuiIds::FullscreenBox,true));
    box->setChecked( _bufferedParameters.Fullscreen );

// engine()->device->isFullscreen()
//


    /////////////////////////////////////////////////////////////////
    ///////     select current resolution
    /////////////////////////////////////////////////////////////////
}



//updateBindDescription()

/**** Function HandleEvents() ****/
bool
COptionState::OnEvent(const irr::SEvent& event){

    if( this->waitingNewBind() )
    {

        if( (event.EventType == EET_KEY_INPUT_EVENT) && (event.KeyInput.Key == irr::KEY_ESCAPE))
        {
            // TODO
            //stopWaiting();
            _INFO << "ESCAPE touche, devrait stopper tout bind" ;
        }
//        if( _descriptorGenerator->baseliningBind() )
        else
        {
            //
            //_descriptorGenerator.check();
            if( _descriptorGenerator->processEvent(
                                                      engine()->device()->getTimer()->getTime(),
                                                      event
                                                      )
               )
               {
                   // Eat the event
                   return true;
               }
        }
        //! Means this is a unhandled event type

    }


    if( event.EventType == EET_GUI_EVENT)
	{
	    //event.GUIEvent.Caller->getID();
		s32 callerId = event.GUIEvent.Caller->getID();

        switch(event.GUIEvent.EventType){
            case EGET_COMBO_BOX_CHANGED:
                break;

            case EGET_BUTTON_CLICKED:
                _INFO << " id clicked :" << callerId;

                // If we clicked on a bind button, we want to update it
                if(callerId >= NGuiIds::Count){

                    if( !waitingNewBind() ){

                        _descriptorGenerator.reset ( new CBindFromEventGenerator(  ) );

                        _buttonToUpdate = static_cast<IGUIButton*>( _tabControl->getElementFromId( callerId, true ) );
                        _buttonToUpdate->setText(L"Waiting...");

                        return true;
                    }
                }

                switch(callerId){

                    case NGuiIds::BackToMenu:
                        OnClickBack();
                        return true;

                    case NGuiIds::ResetConfig:
                        //engine()->ResetConfig();
                        setToConfigValues();
                        break;

                    case NGuiIds::SaveConfig:
                        return OnClickSaveButton();
                    //
                    default:

                        break;
                };
                break;


            case EGET_CHECKBOX_CHANGED:

                    switch(callerId){

                        case NGuiIds::Antialiasing:
                            break;
                        case NGuiIds::VSync:
                            break;
                        case NGuiIds::FullscreenBox:
                            break;
                        //case NGuiIds::Shaders:
                            break;


                    };

                    break;
            //case :
                        default: break;

            }


        } // endif

//        IGUITab* tab = _tabControl->getTab(_tabControl->getActiveTab());
//        EOptionTab activeTab = static_cast<EOptionTab>(tab->getID());
//        (this->*_processingFunctions[activeTab])(event.GUIEvent);
//
//    if( waitingNewBind() && !_descriptorGenerator->baseliningBind() )
//    {
//        _INFO << "Waiting for new bind";
//
//
//        // generated a valid descriptor event
//        //boost::optional<CBindDescriptor> ret =
//        return _descriptorGenerator->processEvent( engine()->device()->getTimer()->getTime(), event);
//
//    }

    return false;
}



/**** Function Update() ****/
void
COptionState::Update()
{

    // If
    if( waitingNewBind() )
    {
        CBindDescriptor result;

//        _descriptorGenerator->check(
//                                engine()->device()->getTimer()->getTime(),
//                                result
//                                    );

        _INFO << "Waiting new bind";

        //! if
        if( _descriptorGenerator->check(engine()->device()->getTimer()->getTime(), result) )
        {
            _INFO << "Generation finished";

            // If already bound
            auto matchingId = std::make_pair( NPlayerInput::MoveLeft,0 );
            auto fullId = UNTRANSLATE_ID( _buttonToUpdate->getID() );

            // If descriptor already used for another bind
//            if( checkForDouble && (*checkForDouble != fullId) ){
            if( GET_MAPPING(1).containBind( result , matchingId) && (matchingId != fullId) )
            {

                fus::TWCharStringBuilder str("Bind [");
                str( result.generateDescription().c_str() )(L"] already bound to other bind [");
//                str( BindNames[ checkForDouble->first ] )
                str( BindNames[ matchingId.first ] )
                ("]")
                ;

                //_INFO << "descriptor Bound with id " << BindNames[checkForDouble->first] << " matching input no " << static_cast<int>(checkForDouble->first);
//                _INFO << "fullId " << fullId->first;

                engine()->popupMessage(L"/!\\ Bind already in use ", str.str().c_str() );

                _buttonToUpdate->setText( GET_MAPPING(1)[ fullId ].generateDescription().c_str()  );
            }
            // TODO set new value
            else
            {

                //std::pair<NPlayerInput::EId,int> res = UNTRANSLATE_ID( _buttonToUpdate->getID() );

                GET_MAPPING(1).setBind( fullId, result);
                //description.append( );
                _buttonToUpdate->setText( result.generateDescription().c_str() );
            }

            // Stop generating descriptor
            _buttonToUpdate = 0;
            _descriptorGenerator.reset(0);
        }
    }
}

bool
COptionState::processEventForSoundTab(const irr::SEvent::SGUIEvent& event){

    return false;
}


bool
COptionState::processEventForGameplayTab(const irr::SEvent::SGUIEvent& event){
//Language
    return false;
}


bool
COptionState::processEventForGraphicTab(const irr::SEvent::SGUIEvent& event){

    s32 id = event.Caller->getID();
    switch(event.EventType){

        case EGET_CHECKBOX_CHANGED:
            //engine->SwitchBit(NBit::Fullscreen, isChecked());
            //engine->
            break;

        default:
            break;

    };

    return false;
}


//CBindEntry*
//int
//COptionState::getMappingId( ){
//    //(elem
//    if(_buttonToUpdate == 0){
//        return -1;
//    }
//    const int mappingId = (_buttonToUpdate->getID() -  NGuiIds::Count);
//
//    return mappingId;
//    //return & (engine()->config->_mappingSet->getMapping( mappingId ) );
//}
//
//








/// Create the options menu
void
COptionState::GUI_CreateMainMenu(){

    IGUIEnvironment* env = gui();


    // parametre le tableau des update
    // TODO utiliser des unary_function ?
    //_processingFunctions[Controls]  = &COptionState::processEventForControlTab;
    _processingFunctions[Graphics]  = &COptionState::processEventForGraphicTab;
    _processingFunctions[Sound]     = &COptionState::processEventForSoundTab;
    _processingFunctions[Gameplay]  = &COptionState::processEventForGameplayTab;


    core::recti rect(0,0,0,0);
    _overallTab = env->addTab( rect,gui()->getRootGUIElement());
    _overallTab->setRelativePositionProportional ( _pos );

    _tabControl = env->addTabControl(rect, _overallTab, true, true);
    _tabControl->setRelativePositionProportional ( core::rectf(0,0,1.f,0.9f));


    //////////////////////////////////////
    //// create control tab
    //////////////////////////////////////

    IGUITab* tab = _tabControl->addTab(L"Controls",Controls);

//    createBindLine( L"Up", NPlayerInput::MoveForward,tab);
//    createBindLine( L"Down", NPlayerInput::MoveBackward,tab);
//    createBindLine( L"Left", NPlayerInput::MoveLeft,tab);
//    createBindLine( L"Right", NPlayerInput::MoveRight,tab);
//    createBindLine( L"Cannon", NPlayerInput::MainShoot,tab);
//    createBindLine( L"Missiles", NPlayerInput::SecondShoot,tab);
//
    createBindLine( NPlayerInput::MoveForward,tab);
    createBindLine( NPlayerInput::MoveBackward,tab);
    createBindLine( NPlayerInput::MoveLeft,tab);
    createBindLine( NPlayerInput::MoveRight,tab);
    createBindLine( NPlayerInput::MainShoot,tab);
    createBindLine( NPlayerInput::SecondShoot,tab);

    //////////////////////////////////////
    //// create graphic tab
    //////////////////////////////////////
    createGraphicTab(   _tabControl->addTab(L"Graphics",Graphics)   );
    createSoundTab(     _tabControl->addTab(L"Sound",Sound)         );
    createGameplayTab(  _tabControl->addTab(L"Gameplay",Gameplay)   );

//b->setAlignment( EGUIA_SCALE, EGUIA_SCALE, EGUIA_SCALE, EGUIA_SCALE);

    // create 3 button
    IGUIButton* button = 0;

    recti box( position2di(0,220), dimension2du(100,32) );
              //0,220,100,220 + 32);

    button = env->addButton( box, _overallTab, NGuiIds::SaveConfig,
			L"Save", L"Save");

    xDecal(box, 5 );
    //recti(200,220,300,220 + 32)
    button = env->addButton( box, _overallTab, NGuiIds::ResetConfig,
			L"Reset", L"Resets configuration");

    xDecal(box, 5 );
    //recti(100,220,200,220 + 32)
    button =  env->addButton( box, _overallTab, NGuiIds::BackToMenu,
			L"Back", L"Back to menu");
    //IGUICheckBox* checkBox =  env->addCheckBox();;



    _bufferedParameters = engine()->EngineConfig;
    //engine()->config->getIrrlichtParameters( _bufferedParameters );
    setToConfigValues();
}


//wchar_t const* name,
void
COptionState::createBindLine(const NPlayerInput::EId& id,IGUITab* tab){

        // get specific mapping
//        CBindDescriptor& key1 = engine()->GameConfig.Keymap1[id];
//        CBindDescriptor& key2 = engine()->GameConfig.Keymap2[id];

        recti pos( 0,id*20,150,(id+1)*20);

        gui()->addStaticText(
                //name,
                BindNames[id],
                //key._name.c_str(),
                pos,    //rect
                true, //border
                false,    //wordwrap
                tab,      // parent
                -1,       // id
                true //fill bg
            );

        xDecal(pos,5);

        //_buttonIds
        //std::pair<int,int> pairIds;
        IGUIButton* button = 0;
        button = gui()->addButton(
                pos
                , tab
                //, 0
                , TRANSLATED_ID(id,0)
                , L""
                , L"Click to change mapping"
                );

        //_buttonsMap.insert( std::make_pair(button,id) );

        xDecal(pos,5);
        //pos.LowerRightCorner
        // TODO afficher le second
        button = gui()->addButton(
                pos
                , tab
                //, 0
                , TRANSLATED_ID(id,1)
                , L"" //GENERATE_DESCRIPTION( Keymap2[id] )
                , L"Click to change mapping"
                );

}


// TODO renommer en Audio
void
COptionState::createSoundTab(IGUITab* tab){

    recti box( 10, 45, 200, 60);

    IGUIComboBox* comboBox = gui()->addComboBox(box,tab,NGuiIds::Resolution);

    comboBox->addItem(L"Fmodex");
    //comboBox->addItem(L"Null");


    yDecal(box,20);
    IGUIScrollBar* scrollbar = gui()->addScrollBar(true, box , tab, NGuiIds::VolumeControl);
    scrollbar->setMax(100);
    // pr le son





    //t3->addChild(scrollbar);
    // TODO choose driver

}



void
COptionState::createGameplayTab(IGUITab* tab){


    // checkbox that enables ingame dialogs
    IGUICheckBox* checkbox =  gui()->addCheckBox  (
                0,
                irr::core::recti(10,40,200,70),
                tab,
                NGuiIds::SkipDialog,
                L"Skip dialog"
                );


    // list of languages available
    _comboBox = gui()->addComboBox(irr::core::recti( conf::_WINDOW_MARGIN_LEFT,
                                                    conf::_WINDOW_MARGIN_TOP,
                                                    conf::_WINDOW_MARGIN_LEFT + _COMBOBOX_WIDTH,
                                                    _COMBOBOX_HEIGHT
                                                    ),
                                                    tab
                                                    );
    _comboBox->setID( NGuiIds::Language );

    //_comboBox->addItem( L"Francais");
    _comboBox->addItem( L"English");

    //_comboBox->setMinSize(core::dimension2du(200,32));

}



////////////////////////////////////////
//////  Graphics
////////////////////////////////////////
void
COptionState::createGraphicTab(IGUITab* tab){

    ////////////////////////////////////////
    //////  Resolution tab
    ////////////////////////////////////////

    irr::core::recti box(10,10,200,40);

    _comboBox = gui()->addComboBox(box,tab,NGuiIds::Resolution);
    IVideoModeList* list = engine()->device()->getVideoModeList();

    core::stringw str;

// TODO selectionner le bon existant
// Ne liste que les modes d'un certain type de profondeur
// += 3
    irr::u32 maxLength = 0;
    //engine->getFont()->getDimension();
    for(s32 i = 0; i < list->getVideoModeCount(); ++i){

        str = videoModeToText(list->getVideoModeResolution(i),list->getVideoModeDepth(i));
        _comboBox->addItem(str.c_str(),i);
        maxLength = std::max(maxLength,str.size());
    }
    //engine->getFont()->getDimension()
    _comboBox->setMinSize(core::dimension2du(maxLength,32));
    //setItemHeight();


    decal(box,0,10);



    ////////////////////////////////////////
    //////  Video driver
    ////////////////////////////////////////
    // TODO
    _comboBox = gui()->addComboBox( box, tab, NGuiIds::Resolution );


    std::vector<std::wstring> drivers;
    engine()->getAvailableVideoDriverList(drivers);

    BOOST_FOREACH( std::wstring& driverName, drivers )
    {
        //std::cout << p.first << "-->" << p.second << std::endl;
        //if(IIrrlichtDevice::isDriverSupported(EDT_OPENGL)) {
             _comboBox->addItem( driverName.c_str() );//L"OpenGL"
        //}
    }



    //engine->getFont()->getDimension()
    _comboBox->setMinSize(core::dimension2du(maxLength,32));



    decal(box,0,20);


    // ajouter une tickbox pr le fullscreen
    gui()->addCheckBox  ( 0, box, tab, NGuiIds::FullscreenBox,
                L"Enable fullscreen"
                );

    decal(box,0,10);

    //IGUICheckBox* checkbox =
    gui()->addCheckBox  (
                0,
                box,
                tab,
                NGuiIds::MotionBlurShader,
                L"Enable motion blur shader"
                );

    decal(box,0,10);

    gui()->addCheckBox  (
                0,
                box,
                tab,
                NGuiIds::BloomShader,
                L"Enable bloom shader"
                );

    decal(box,0,10);

    gui()->addCheckBox  (
                0,
                box,
                tab,
                NGuiIds::VSync,
                L"Enable Vsync"
                );

    decal(box,0,10);

    gui()->addCheckBox  (
                0,
                box,
                tab,
                NGuiIds::Antialiasing,
                L"Enable Antialiasing"
                );

}

/**** Function Init() ****/
//void
//COptionState::init(){
//
//    //_indexOfFocusedElement = -1;
//
//}
//


/**** Function Cleanup() ****/
void
COptionState::CleanUp(){

    // Effacer tout ce qui a ete charge
    //engine->guienv->get ->removeChild(_tabControl)
    //_tabControl->remove();
    _overallTab->remove();
};


//modification
void
COptionState::OnClickBack()
{

    //if modification demander a l'user de sauvegarder
    //engine()->PopState();
    //remove();
    popThisState();
}



bool
COptionState::OnClickSaveButton()
{

    //if(!engine->config->RawSave()){
    //if(!engine()->SaveConfig()){
        _LOG_ERROR << "Couldn't save config";

    return true;
}




/// \function Draw()
void
COptionState::Draw()
{

    scene()->drawAll();

    //postProcessingFramework()->update();

    // Xeffect hack
    //engine()->driver()->setMaterial( engine()->driver()->getMaterial2D() );

    _overallTab->draw();
    //gui()->drawAll();//

}




irr::core::stringw
COptionState::videoModeToText(const core::dimension2du& dims,const s32& depth){


    irr::core::stringw str(dims.Width);// + "x" +dims.Height;
    str += " x ";
    str += dims.Height;
    str += " x ";
    str += depth;
    return str;
}



#undef GET_MAPPING
