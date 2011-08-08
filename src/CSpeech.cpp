
#include "CSpeech.hpp"
#include <fusion/core/string.hpp>
#include <fusion/fusion.hpp>


//
//CSpeech::CSpeech(const std::string& message,const char* sound){
//
//    setMessage(message);
//    _soundFilename = sound;
//}


CSpeech::CSpeech(const std::wstring& message,CSound* sound){

    //setMessage(message);
    _message = message;
    //_soundFilename = sound;
    _sound = sound;
}


void
CSpeech::setMessage(const std::string& message) {
    fus::convertIntoWideString(message,_message);
}


bool
CSpeech::setAudio(const std::string& audioFilename) {

    CSound* sound = 0;

    //if( audioFilename.size() ){
        _LOG_DEBUG << "Loading audio filename [" << audioFilename << "]";
        //_sound = ENGINE->getSoundManager()->getSound( audioFilename );
    //}
    return (_sound != 0);
}



void
CSpeech::addAnswer(const std::string& answer,const TPlayerReply& returnValue){

    std::wstring wanswer;
    fus::convertIntoWideString(answer,wanswer);
    _answers.push_back( boost::make_tuple(wanswer,returnValue)  );
}




//CSpeech::CSpeech(CSpeaker* actor,const std::wstring& msg,CSound* sound) :
//_speaker(actor),
//_sound(sound)
//{
//    //constructor
//    _message = msg;
//}


CSpeech::~CSpeech()
{
    //dtor
}


#if 0
void
CSpeech::play()
{
    //dtor
    if(_sound){
        _sound->play();
    }
}

void
CSpeech::stop()
{
    if(_sound){
        _sound->stop();
    }
}




void
CDialogState::init()
{
    //_currentEvent = 0;
    if(_events.size()){
        _INFO << "first event playing";
        _events.front().play();
        //
    }

}


// passer un 3ieme parametre = fct lua a appeler qd eve realise
//wchar_t
void
CDialogState::AddSpeech(CSpeaker* actor,const std::string& msg,const std::string& audioFilename){

    CSound* sound = 0;

    if( audioFilename.size() ){
        _INFO << "Loading audio filename" << audioFilename;
        sound = CGameEngine::getSoundManager()->loadSound( audioFilename.c_str() , false );
    }

//    std::string text(msg);
//    _events.push_back(std::make_pair(actor,std::wstring()));
    CSpeech speech(actor,std::wstring(msg.begin(),msg.end()),sound);
    _events.push_back(speech);
}

void
CDialogState::CleanUp(){
}

//bool
void
CDialogState::Update(){

    if(_events.empty()){
        // supprimer cet etat du game engine
        // TODO solution temporaire qui marche plus si on empile un gamestate sur ce dialogue
        this->remove();
        //return false;
    }
}



// TODO ici obtenir qque chose independant de la resolution
void
CDialogState::Draw(){

/*
virtual void  draw2DRectangle (SColor color, const core::rect< s32 > &pos, const core::rect< s32 > *clip=0)=0
  Draws a 2d rectangle.

virtual void  draw2DRectangleOutline (const core::recti &pos, SColor color=SColor(255, 255, 255, 255))=0
  Draws the outline of a 2D rectangle.

*/
    if(_events.empty()){
        return;
    }
    irr::gui::IGUIFont* font = gui()->getFont (_BC_FILE_HUDFONT);

//    gui::IGUIFont* font = engine->guienv->getFont("images/fonthaettenschweiler.bmp");
    const CSpeech& speech = _events.front();

    if(font){

        //engine()->smgr->drawAll();

        // Creation of displayed text, first add name of the interlocutor
        std::wstring text = speech._speaker->_name;
        text += L":\n";
        // then his/her speech


        text += speech._message;
        font->draw(
            text.c_str(),
            core::recti(300,10,500,50),
            video::SColor(255,255,255,255)
        );
    }


    irr::video::ITexture* texture = speech._speaker->_texture;
    if(texture){
        irr::core::recti  srcRect(irr::core::position2di(0,0),texture->getOriginalSize());
        engine()->driver->draw2DImage(
            texture,
            core::position2di(10,10),
            srcRect,
            0,              // clipRect
            video::SColor(255,255,255,255),
            true                // useAlphaChannelOfTexture
            );

    }
}



#endif
