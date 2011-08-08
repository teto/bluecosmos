#include "config.hpp"
#include "utils/TClock.hpp"


namespace conf {


const wchar_t* CREDITS_STRING   = L"=== Staff === \n\nTeto (Lead coder & chief project)\nGeekShadow (Webmaster)\nTheEsound (Music)\nThePunch aka Simon (Game designer)\nNoctisLucisCaelum (HUD designer)\n";



const wchar_t* _GAME_VERSION = L"0.2b1";

const char* _LUA_STARTER_SCRIPT = "scripts/init_engine.lua";
const char* CONFIG_FILENAME = "config.lua";




const irr::core::dimension2du _PORTRAIT_SIZE(250,250);

//#ifdef __YF19__
const char* _YF19_BOOSTER_LEFT_NAME  = "booster_left";
const char* _YF19_BOOSTER_RIGHT_NAME = "booster_right";
const char* _YF19_MESH_FILENAME = "models/animated/yf19.b3d";
//#else
const char* _YF21_BOOSTER_LEFT_NAME  = "Bone.047";
const char* _YF21_BOOSTER_RIGHT_NAME = "booster_right";
const char* _YF21_MESH_FILENAME = "models/animated/yf21.b3d";
//#endif


const irr::u32 _SHAKING_LENGTH = 3000;
const int _LOWER_LIMIT          = -23;
const int _UPPER_PART           = 80;


const float DEFAULT_ROTATION_SPEED= 5.f;
//_DEFAULT_STOCK_OF_MISSILES

const int _CONSOLE_HEIGHT = 100;

const std::string _GUI_FONT         = "font.ttf";
const std::string _BC_SCRIPT_FILE   = "game.lua";
const float _SIDE_BAND_PERCENTAGE = 0.15f;

const float _X_MAX = 20.f;
const float _X_MIN = -_X_MAX;
const float _Z_MAX = 200.f;
const float _Z_MIN = -200.f;


const int _BUTTON_HEIGHT   = 32;
const int _BUTTON_WIDTH     = 180;
const irr::core::position2di _BUTTON_GAP = irr::core::position2di (5,_BUTTON_HEIGHT + 10);


const unsigned int _NB_OF_SCORES = 10;

const char* _CONFIG_FILENAME = "config.xml";
const char* _FILE_SCORES = "scores.xml";


const int _PLAYER_BLINKS  = 5;

const int _BC_SCORE_LENGTH  = 8;

////////////////////////////////////////////
////    GAMEPLAY CONFIG
////////////////////////////////////////////
const int _DEFAULT_STOCK_OF_MISSILES    = 20;
const int _BC_PLAYER_MAX_HEAT           = 100;      //!< max Inclinaison
const float _BACKSPEED_MODIFICATOR      = 3.f;      //!< max Inclinaison
const float _PLAYER_BULLET_RANGE        = 2.f;      //!< max Inclinaison
const float _PLAYER_MISSILE_RANGE       = 2.f;      //!< max Inclinaison

// This is lifetime of a battery once out of a quad
// if 0 then it will ignore squad
const irr::u32 _BC_BULLET_LIFETIME_MS   = 100;
const int _DEFAULT_LIVES                = 3;
const float _COOLING_DELTA              = 3;
const int _SHOT_HEAT_VALUE              = 10;


////////////////////////////////////////////
////    VIDEO    CONFIG
////////////////////////////////////////////
extern const irr::video::E_DRIVER_TYPE _DEFAULT_VIDEO_DRIVER = irr::video::EDT_OPENGL;


////////////////////////////////////////////
//// PROGRAM CONFIG
////////////////////////////////////////////
//const bool __YF19__ = false;



const int _WINDOW_MARGIN_LEFT = 10;
const int _WINDOW_MARGIN_TOP  = 10;
const int _WINDOW_DEFAULT_WIDTH = 640;
const int _WINDOW_DEFAULT_HEIGHT = 480;

const char* _BC_FILE_HUDFONT = "images/hud.xml";
const wchar_t* _WINDOW_TITLE = L"Blue Cosmos rocks your soul";
//const irr::fschar_t* _BC_BACKUP_GUI = "temp_gui.irr";


const char* _SCORES_FILENAME = "scores.xml";


const TTimer::TimeType _PLAYER_BLINK_LENGTH = 100;   //!< temps de l'animation totale en secondes

}
