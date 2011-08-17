#include "startup_config.hpp"
#include <irrlicht.h>
#include "events/CBindCollection.hpp"

using namespace irr;
using namespace input;

SIngameConfig::SIngameConfig() :
    EnableBloomShader(false)
    , EnableMotionBlurShader(false)
    , EnableDialogs(false)
    , MappingPlayer1(new TMappingSet() )
{


//////////////////////////////////////////////////////////////////////////
/////       Reset keymap
//////////////////////////////////////////////////////////////////////////

try {
    CBindDescriptor temp;
    TMappingSet::TOptionalFullId ret;

//temp.Mode = mode;
// TODO verifier qu'il y ait pas de doublons
    #define ADD_BIND(id,param,mode,no) { auto fullId = std::make_pair(id,no); \
                                        CBindDescriptor temp; \
                                        temp.setup(param); \
                                        temp.Mode = mode; \
                                        ret = MappingPlayer1->containBind( temp ); \
                                        \
                                        if(ret && (*ret) != fullId ){ \
                                            _LOG_ERROR << "Descriptor already registered with id " << ret->first << "/" << ret->second ; \
                                        } \
                                        else { \
                                            MappingPlayer1->setBind(fullId,temp);\
                                        } \
                                        }


    //ret = boost::none;
    //ret =
    //MappingPlayer1->addBind(NPlayerInput::MoveLeft, temp);
    //.Mode = ETapMode::Pressed;
    // si on ne precise pas le param alors c'est 0;
    ADD_BIND(NPlayerInput::MoveLeft,L"Left",ETapMode::JustPressed,0);
    ADD_BIND(NPlayerInput::MoveRight,L"Right",ETapMode::JustPressed,0);

    /*MappingPlayer1->addBind( NPlayerInput::MoveLeft, CBindDescriptor(ETapMode::Pressed) );
    MappingPlayer1->addBind( NPlayerInput::MoveLeft, CBindDescriptor(L"Left") );
    MappingPlayer1->addBind( NPlayerInput::MoveLeft, CBindDescriptor(L"q") );
*/
//    TMappingSet::TIdDescriptors binds ;
//    _LOG_WARNING << "descriptors.size : "<< MappingPlayer1->getDescriptors(NPlayerInput::MoveLeft,binds);

    /*
    Keymap1[NPlayerInput::MoveLeft].setup(L"Left");
    Keymap1[NPlayerInput::MoveRight].setup(L"Right");
    Keymap1[NPlayerInput::MoveForward].setup(L"Up");
    Keymap1[NPlayerInput::MoveBackward].setup(L"Down");
    Keymap1[NPlayerInput::MainShoot].setup(L"w");
    Keymap1[NPlayerInput::SecondShoot].setup(L"x");
    Keymap1[NPlayerInput::ModeUp].setup(L"q");
    Keymap1[NPlayerInput::ModeDown].setup(L"s");
    */
}
catch(std::out_of_range& e){
    _LOG_ERROR << "Error" << e.what();
}

//"joystick"
/*
Keymap2[NPlayerInput::MoveLeft].setup(EInputType::Joystick,"left");
Keymap2[NPlayerInput::MoveRight].setup(EInputType::Joystick,"right");
Keymap2[NPlayerInput::MoveForward].setup(EInputType::Joystick,"up");
Keymap2[NPlayerInput::MoveBackward].setup(EInputType::Joystick,"down");
Keymap2[NPlayerInput::MainShoot].setup(EInputType::Joystick,"w");
Keymap2[NPlayerInput::SecondShoot].setup(EInputType::Joystick,"x");
Keymap2[NPlayerInput::ModeUp].setup(EInputType::Joystick,"q");
Keymap2[NPlayerInput::ModeDown].setup(EInputType::Joystick,"s");
*/


}
