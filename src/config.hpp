/** \file config.h
 *  \brief Defines all default values ( that is starting with an underscore "_" )
**/
#ifndef _BC_CONFIG_HPP
#define _BC_CONFIG_HPP

#include <string>
#include <irrlicht.h>

// Comment next line to disable some debug comments during the game
#define _BC_DEBUG 1
/*
#ifndef TIXML_USE_STL
    #define TIXML_USE_STL 1   //!< TellTInyXml to use STL
#endif
*/
// Si on veut lier dynamiquement SPARK faut definir la suite
//#define SPK_IMPORT
namespace conf {
/// Default configuration,in case the config file were to be erased
//extern const
//extern const std::string _BUILD_NUMBER = 0.2b1;
extern const wchar_t* _GAME_VERSION;
extern const char* _LUA_STARTER_SCRIPT;
extern const char* CONFIG_FILENAME;


extern const wchar_t* CREDITS_STRING;


extern const std::string _BC_SCRIPT_FILE;
extern const std::string _GUI_FONT;
extern const float _SIDE_BAND_PERCENTAGE; //!< Largeur des bandes noires de chaque cote en %
//const float _SIDE_BAND_ABSOLUTE = 50; //!< Largeur des bandes noires de chaque cote en %


/// Matrix variables
/// \todo ne retenir que 2 constantes ( soit on part de 0 soiton fait -_X_MAX)
extern const float _X_MAX;
extern const float _X_MIN;
extern const float _Z_MAX;
extern const float _Z_MIN;

extern const float DEFAULT_ROTATION_SPEED;
////////////////////////////////////////////
////    DISPLAY/GRAPHICS CONFIG
////////////////////////////////////////////
#define _COMBOBOX_WIDTH 200
#define _COMBOBOX_HEIGHT 20
extern const int _WINDOW_MARGIN_LEFT;// 10
extern const int _WINDOW_DEFAULT_WIDTH;
extern const int _WINDOW_DEFAULT_HEIGHT;
extern const int _WINDOW_MARGIN_TOP; // 10
const bool _BC_CONFIG_VSYNC         = false;
const bool _BC_CONFIG_FULLSCREEN    = false;
extern const unsigned int _NB_OF_SCORES;
extern const int _BUTTON_HEIGHT;
extern const int _CONSOLE_HEIGHT;
extern const irr::video::E_DRIVER_TYPE _DEFAULT_VIDEO_DRIVER;

//const irr:: _BUTTON_GAP_VERTICAL   = 10;
//const int _BUTTON_GAP_HORIZONTAL = 32;
extern const irr::core::position2di _BUTTON_GAP;
//const irr::core::recti _MENU_RECT_BUTTON();


extern const int _BUTTON_WIDTH;
const irr::core::recti _MENU_BUTTON_RECT(0,0,_BUTTON_WIDTH,_BUTTON_HEIGHT);


////////////////////////////////////////////
//// DIALOG
////////////////////////////////////////////
extern const irr::core::dimension2du _PORTRAIT_SIZE;



////////////////////////////////////////////
////    GAMEPLAY CONFIG
////////////////////////////////////////////
extern const int _DEFAULT_STOCK_OF_MISSILES ;
extern const int _BC_PLAYER_MAX_HEAT        ;      //!< max Inclinaison
extern const float _BACKSPEED_MODIFICATOR   ;      //!< max Inclinaison
extern const float _PLAYER_BULLET_RANGE     ;      //!< max Inclinaison
extern const float _PLAYER_MISSILE_RANGE    ;      //!< max Inclinaison
// TOdo a revoir
extern const irr::u32 _BC_BULLET_LIFETIME_MS;
extern const irr::u32 _SHAKING_LENGTH;
extern const int _LOWER_LIMIT;
extern const int _UPPER_PART;
extern const int _DEFAULT_LIVES;
extern const float _COOLING_DELTA           ;
extern const int _SHOT_HEAT_VALUE           ;


////////////////////////////////////////////
//// PROGRAM CONFIG
////////////////////////////////////////////


extern const wchar_t* _WINDOW_TITLE;
//const irr::fschar_t* _BC_BACKUP_GUI = "temp_gui.irr";

extern const char* _SCORES_FILENAME;
//extern const char* _SCORES_FILENAME;



const float _MIN_RADIUS = 30;          //!< Distance from the camera to point (Xmax/2,Ymax/2,0)
#define _BC_BACKUP_GUI "temp_gui.irr"
#define _BC_BACKUP_SCENE "temp_world.irr"


extern const char* _YF19_MESH_FILENAME;
extern const char* _YF19_BOOSTER_LEFT_NAME;
extern const char* _YF19_BOOSTER_RIGHT_NAME;

extern const char* _YF21_MESH_FILENAME;
extern const char* _YF21_BOOSTER_LEFT_NAME;
extern const char* _YF21_BOOSTER_RIGHT_NAME;

//#define _LIMIT_FRAMERATE 60     //!< Spare CPU and battery
//#define _EXPLOSION_TIME 4000    //!< In milliseconds
//#define _PLAYER_ANIMATION_LENGTH 6   //!< temps de l'animation totale en secondes
extern const int _PLAYER_BLINKS;   //!< temps de l'animation totale en secondes
extern const irr::u32 _PLAYER_BLINK_LENGTH;   //!< temps de l'animation totale en secondes



/// Number of entitites to pre-allocate
//extern const std::size_t _RESERVE = 50;
//#define _RESERVE 50
//#define _RESERVE_EXPLOSIONS 5

//std::string path = ((std::string)getenv("APPDATA")) + "\\OpenAlchemist";
//const std::string _FILE_SCORE  = "scores.xml";
extern const char* _CONFIG_FILENAME;
extern const char* _FILE_SCORES;
//const std::string _FILE_LEVEL = "levels.lxml";
//const char* _BC_FILE_HUDFONT = "images/hud.xml";
extern const char* _BC_FILE_HUDFONT;



#define _BC_FOR_64BITS true

//#if _BC_FOR_64BITS
//    // Compile squirrel for 64 bits platform
//    #define _SQ64
//#endif

// to use squirrel 16bits strings
#define SQUNICODE

//Define the different directories to make it easier
//to make bc relocalisable
#if defined(_WIN32) || defined(__WIN32__)
const std::string _DIR_DATA   = "data/";
const std::string _DIR_SOUND  = "sounds/";
const std::string _DIR_IMAGES = "images/";
const std::string _DIR_MESHES = "models/";

#elif defined(linux) || defined(__linux)
const std::string _DIR_DATA   = "data/";
const std::string _DIR_SOUND  = "sounds/";
const std::string _DIR_IMAGES = "images/";
const std::string _DIR_MESHES = "models/";
#else
    #error Unsupported platform
#endif

}

#endif
