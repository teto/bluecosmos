/** \file IGameConfig.cpp
 *  \brief Load and save when needed the xml configuration file
**/

/*
A voir si on fait un parseur
-liste des parametres a  passer en ligne de commande:
--nosync : pour eviter synchro avec le timer dans main
--fullscreen : evident :D
--log :html pour avoir un log ecrit en html
	 xml pr l'avoir en xml
--nosound : humhum...

void CConfigManager::ParseCommandLine(const std::string& param){
    //return *mInstance;


}*/

#include <iostream>
#include <fstream>
#include "CConfig.hpp"
#include "game_engine.hpp"
#include "config.hpp"
#include "events/CBindDescriptor.hpp"
#include "events/CMultiBind.hpp"
#include <fusion/core/CStringBuilder.hpp>
#include <fusion/core/string.hpp>
#include "pugixml/pugixml.hpp"
#include "utils/CBitSet.hpp"
//#include <utf8.h>



using namespace pugi;
using namespace irr;
using namespace core;











//(bool& value, newValue)
//bool

void
CConfigManager::enableFullscreen(const blo::tribool& value){
    switchBit(_fullscreen,value);
    //return
}
//CConfigManager::setLoggingLevel()
//CConfigManager::setAudioDriver()

//CConfigManager::setVideoDriver()
//CConfigManager::setDepth()

void
CConfigManager::enableVsync(const blo::tribool& value) {
    switchBit(_vsync,value);
}

//void
//CConfigManager::enableShaders(const blo::tribool& value) {
//    switchBit(_shaders,value);
//}

void
CConfigManager::enableShader(const std::wstring& name, const bool& enable) {

    TShadersList::iterator it = _shaders.find(name);
    if(it != _shaders.end() ){

        it->second = enable;
    }
}




void
CConfigManager::setAntialiasingLevel(const int& value){

    //
    _antialiasing = value;
}


void
CConfigManager::getIrrlichtParameters( irr::SIrrlichtCreationParameters& parameters) const {

    parameters.AntiAlias    = _antialiasing;

    parameters.Vsync        = _vsync;
    parameters.Fullscreen   = _fullscreen;
    //parameters.DriverType   =
    parameters.WindowSize.set( getWindowWidth(), getWindowHeight() );
    //parameters.Bits         = ;

}

const int&
CConfigManager::getWindowWidth() const {
    return _width;
};

const int&
CConfigManager::getWindowHeight() const {
    return _height;
};

//const irr::core::dimension2du&
//CConfigManager::getWindowSize() const {
//    return _parameters.WindowSize;
//};


//



CConfigManager::~CConfigManager(){

    _INFO << "Config destructor called";
}


void
CConfigManager::reset()
{


//////////////////////////////////////////////////////////////////////////
/////       Reset keymap
//////////////////////////////////////////////////////////////////////////
//CBindDescriptor* mapping = 0;
const int moveMask = NInputType::KEY | NInputType::JOY_POV | NInputType::JOY_AXIS_PLUS | NInputType::JOY_AXIS_MINUS;
const int actionMask = NInputType::KEY | NInputType::JOY_BTN | NInputType::MOU_BTN;

CBindEntry* mapping = 0;

// NPlayerInput::MoveLeft
mapping = &_mappingSet->getMapping(NPlayerInput::MoveLeft);
mapping->setBind( NInputType::KEY, KEY_LEFT );
mapping->setName(L"Left");
mapping->setMask( moveMask );
mapping->setRepeatDelay(10);
mapping->enableRepeat(true);



mapping = &_mappingSet->getMapping(NPlayerInput::MoveRight);
mapping->setBind(NInputType::KEY,KEY_RIGHT);
mapping->setName(L"Right");
mapping->setMask( moveMask );
mapping->setRepeatDelay(10);
mapping->enableRepeat(true);

mapping = &_mappingSet->getMapping(NPlayerInput::MoveForward);
mapping->setBind(NInputType::KEY,KEY_UP);
mapping->setName(L"Forward");
mapping->setMask( moveMask );
mapping->setRepeatDelay(10);
mapping->enableRepeat(true);

mapping = &_mappingSet->getMapping(NPlayerInput::MoveBackward);
mapping->setBind(NInputType::KEY,KEY_DOWN);
mapping->setName(L"Backward");
mapping->setMask( moveMask );
mapping->setRepeatDelay(10);
mapping->enableRepeat(true);

mapping = &_mappingSet->getMapping(NPlayerInput::MainShoot);
mapping->setBind(NInputType::KEY,KEY_KEY_W);
mapping->setName(L"Main shoot");
mapping->setMask( actionMask );
mapping->setRepeatDelay(10);
mapping->enableRepeat(true);

//_mappingSet->getMapping(NPlayerInput::EnableSpin).setup(NInputType::KEY,KEY_KEY_Z);

mapping = &_mappingSet->getMapping(NPlayerInput::SecondShoot);
mapping->setBind(NInputType::KEY,KEY_KEY_X);
mapping->setName(L"Secondary shot");
mapping->setMask( actionMask );
mapping->enableRepeat(true);
mapping->setRepeatDelay(40);


mapping = &_mappingSet->getMapping(NPlayerInput::ModeUp);
mapping->setName(L"Mode up");
mapping->setMask( actionMask );
mapping->setBind(NInputType::KEY,KEY_KEY_Q);

mapping = &_mappingSet->getMapping(NPlayerInput::ModeDown);
mapping->setName(L"Mode down");
mapping->setMask( actionMask );
mapping->setBind(NInputType::KEY,KEY_KEY_S);

/*
//mapping = &_mappingSet->getMapping(NPlayerInput::MoveLeft);
mapping->init(L"Left",NInputType::KEY,KEY_LEFT);
mapping->setRepeatDelay(10);
mapping->enableRepeat(true);

mapping = &_mappingSet->getMapping(NPlayerInput::MoveRight);
mapping->init(L"Right",NInputType::KEY,KEY_RIGHT);
mapping->setRepeatDelay(10);
mapping->enableRepeat(true);

mapping = &_mappingSet->getMapping(NPlayerInput::MoveForward);
mapping->init(L"Forward",NInputType::KEY,KEY_UP);
mapping->setRepeatDelay(10);
mapping->enableRepeat(true);

mapping = &_mappingSet->getMapping(NPlayerInput::MoveBackward);
mapping->init(L"Backward",NInputType::KEY,KEY_DOWN);
mapping->setRepeatDelay(10);
mapping->enableRepeat(true);

mapping = &_mappingSet->getMapping(NPlayerInput::MainShoot);
mapping->init(L"Main shoot",NInputType::KEY,KEY_KEY_W);
mapping->setRepeatDelay(10);
mapping->enableRepeat(true);

//_mappingSet->getMapping(NPlayerInput::EnableSpin).setup(NInputType::KEY,KEY_KEY_Z);

mapping = &_mappingSet->getMapping(NPlayerInput::SecondShoot);
mapping->init(L"Secondary shot",NInputType::KEY,KEY_KEY_X);
mapping->enableRepeat(true);
mapping->setRepeatDelay(40);


_mappingSet->getMapping(NPlayerInput::ModeUp).init(L"Mode up",NInputType::KEY,KEY_KEY_Q);
_mappingSet->getMapping(NPlayerInput::ModeDown).init(L"Mode down",NInputType::KEY,KEY_KEY_S);
*/

_width =  conf::_WINDOW_DEFAULT_WIDTH;
_height = conf::_WINDOW_DEFAULT_HEIGHT;
_fullscreen = conf::_BC_CONFIG_FULLSCREEN;
_antialiasing = 0;
//_shaders = 0;

_shaders.clear();
_shaders.insert( std::pair<std::wstring,bool>( L"Motion blur", false) );
_shaders.insert( std::pair<std::wstring,bool>( L"Bloom", false) );

_vsync = 0;
_videoDriver = L"opengl";
_audioDriver = L"fmodex";
}


//! Constructor
CConfigManager::CConfigManager() :
_width(conf::_WINDOW_DEFAULT_WIDTH),
_height(conf::_WINDOW_DEFAULT_HEIGHT),
_fullscreen(conf::_BC_CONFIG_FULLSCREEN)
{



    //
     _mappingSet.reset( new TMappingSet() );
     //_mappingSet.reset( new CBindCollection<NPlayerInput::Count>() );


//    TDictionary& audio = _dictionaries[AudioDriverType];
//    audio["null"] = 0;
//    audio["fmodex"] = 1;
}


//Fullscreen


//! Loads the file
bool
CConfigManager::load(
                     const char* filename
                     //CConfigManager& config
//                     unsigned int& width,unsigned int& height,
//                     bool& vsync,bool& fullscreen,bool& antialias,
//                     std::stringw& videoDriver,std::stringw& audioDriver
                    ){
//CConfigManager::Load(SIrrlichtCreationParameters& parameters){


    //resetWindowSettings();

    _INFO << "Loading of configuration file...";

    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file(filename);

    if(!result){
        _LOG_ERROR << "Impossible to load config file [" << filename << "]: \n" << result.description();
        _LOG_ERROR << "Error offset [" << result.offset << "]";
        return false;
    }

    // assume loading successful

    //std::cout << "XML [" << source << "] parsed without errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n\n";
    pugi::xml_node config = doc.child(L"config");
    pugi::xml_node mapNode = config.child(L"player").child(L"map");
    if(!mapNode){
        return false;
    }

    //////////////////////////////////////////////////////////////////
    /////   Load each map
    //////////////////////////////////////////////////////////////////
    //for (pugi::xml_node bind = player.child("bind"); bind; bind = bind.next_sibling("bind")){
    int i = 0;
    for (pugi::xml_node_iterator it = mapNode.begin(); it != mapNode.end(); ++it,++i) {
    //for(int i = 0; i < NPlayerInput::Count;){

        //attribute
        CBindEntry& mapping = _mappingSet->getMapping(i);
        //CBindDescriptor bind;
        mapping.setName( it->attribute(L"name").value() );

        bool repeat = it->attribute(L"repeat").as_bool();
        mapping.enableRepeat( repeat );
        if(repeat){

            mapping.setRepeatDelay( it->attribute(L"delay").as_uint() );
        }


        //////////////////////////////////////////////////////////////////
        /////   Load each bind into map
        //////////////////////////////////////////////////////////////////
        //for (pugi::xml_node bind = player.child("bind"); bind; bind = bind.next_sibling("bind")){
        int i = 0;
        pugi::xml_node bindNode = mapNode.child(L"map");

        for (pugi::xml_node_iterator bindIt = mapNode.begin(); bindIt != mapNode.end(); ++bindIt) {

            //bindIt->attribute(L"type").value(), bindIt->attribute(L"value").value()
            CBindDescriptor bind;
            if(bind.setup(bindIt->attribute(L"type").value(), bindIt->attribute(L"value").value()) ){
                mapping.addBind( bind );
            }
            else {

                _LOG_WARNING << "Wrong bind";
            }

//            if( !mapping.addBind( it->attribute(L"type").value(), it->attribute(L"value").value() ) ){
//                return false;
//
//            }

        }




//        if( !mapping.setBind( bind ) ){
//            //throw std::runtime_error("Impossible to setup mapping");
//            //throw std::runtime_exception("Impossible to setup mapping");
//            return false;
//        }


        //mapping
        //bind.next_sibling("bind");

        //bool repeat = false;
        //mapping->Repeat
        //mDoc["repeat"] >> repeat;;// = true;


//        for (pugi::xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ++ait)
//        {
//            std::cout << " " << ait->name() << "=" << ait->value();
//        }
            //if(!mapping.setup( wtype.c_str(), wvalue.c_str() )){

        //

    }


    if( i+1 != NPlayerInput::Count){
        return false;
    }

    //////////////////////////////////////////////////////////////////
    /////   Graphics configuration
    //////////////////////////////////////////////////////////////////
    pugi::xml_node graphics = config.child(L"graphics");
    _width = graphics.attribute(L"width").as_int();
    _height = graphics.attribute(L"height").as_int();
    _vsync = graphics.attribute(L"vsync").as_bool();
    _antialiasing = graphics.attribute(L"antialiasing").as_bool();
    //_shaders = graphics.attribute(L"shaders").as_bool();
    _fullscreen = graphics.attribute(L"fullscreen").as_bool();
    _videoDriver = graphics.attribute(L"driver").value();


    return true;
}




bool
CConfigManager::RawSave(
    const char* filename
//    const unsigned int& width,const unsigned int& height,
//    const bool& vsync,const bool& fullscreen,
//    const bool& enableDialogs,
//    const bool& antialias
)
// peux pas etre const a cause de l'operateur []
// const
{

//    pugi::xml_document doc();
//
//
////pugi::format_raw
//
//    //pugi::xml_node player = doc.append_child(L"config").append_child(L"player");
//
//    fus::TWCharStringBuilder text();
//    for(int i = 0; i < NPlayerInput::Count;++i){
//
//        const CBindDescriptor& map = _mappingSet->getMapping(i) ;
//        map.toXmlString(text);
//    }
//
//    xml_parse_result result = doc.load( text );
//
//    if(!result){
//        _LOG_ERROR << "Impossible to load [" << text << "]: \n" << result.description();
//        _LOG_ERROR << "Error offset: " << result.offset;
//        return false;
//    }
//
//         #if 0
    std::wofstream file( filename);
    try {


    if(file.good()){
        fus::TWCharStringBuilder text(L"<config>\n<player>\n");

        std::wstring temp;
        //_mappingSet.exportToXml(temp);

        text(temp);
        // enregistre le mapping du joueur
        for(int i = 0; i < NPlayerInput::Count;++i){

            const CBindEntry& map = _mappingSet->getMapping(i) ;
            map.toXmlString(text);
            text("\n");
        }

        text("</player>\n");

    // TODO construire window settings
        //text(windowSettingstoXmlString());
        text("<window ")
        ("fullscreen=\"")(_fullscreen)("\" ")
        ("vsync=\"")(_vsync)("\" ")
        ("width=\"")(_width)("\" ")
        ("height=\"")(_height)("\" ")
        ("antialiasing=\"")(_antialiasing)("\" ")
        //("shaders=\"")(_shaders)("\" ")
        // TODO convertir en simplestring
        ("driver=\"")(_videoDriver)("\" ")
        ("audio=\"")(_audioDriver)("\" />")
        ;

        ////////////////////////////////////////////////////////////
        /////   SHADERS
        ////////////////////////////////////////////////////////////
        //motionblur
        //BOOST_FOREACH(){
        for( TShadersList::iterator i(_shaders.begin()),end(_shaders.end()); i != end; ++i){
            text("<shader type=\"")(i->first)("\" enabled=\"")(i->second)("\" />");
        }

        //text("<game dialogs=")(_enableDialogs)(" language=")("french")(" />");


        // fin du fichier
        text("\n</config>");

        file << std::wstring(text);
        //file << text.str();

    }
    }
    catch(...){
        _LOG_ERROR << "erreur lors de la sauvegarde de la conf";
        return false;
    }
    file.close();

    //#endif
    return true;
}


