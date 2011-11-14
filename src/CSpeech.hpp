/**
* \file
    //multiplayer
    //if(game->mMultiPlayer)
    //    mPlayer[1] = CEntityManager::GetInstance()->CreatePlayer(_DIR_DATA + "ship.sxml",vertex,true,anchors,CConfigManager::GetInstance()->GetKeyMapOfPlayer1());
deriver CSinglePlayer en creant dans CSinglePlayer des fonctions
s'occupant d'un unique joueur
ou bien faire en sorte que le joueur soit dealt with by levels.cpp ?
*/
/**
* \file single.h
**/
#ifndef CSpeech_HPP_INCLUDED
#define CSpeech_HPP_INCLUDED


//#include "IGameState.hpp"
//#include <irrlicht.h>
#include <list>
#include <string>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include "def.hpp"
//#include "../utils/CBindDescriptor.hpp"
//#include "CSpeaker.hpp"
//
//class CSpeaker;

class CSound;


// Une liste d'assoce
//CSpeaker / Cspeech,

class CSpeech
{

protected:


public:
    typedef TPlayerReply TReturnType;

    CSpeech(const std::wstring&,CSound* sound);
    ~CSpeech();

    void setMessage(const std::string& message);
    bool setAudio(const std::string&);


    void addAnswer(const std::string& message,const TPlayerReply&);

    // retour = int ou bien fonction lua ?
    typedef boost::tuple<std::wstring, TPlayerReply> TAnswer;
    typedef std::vector< TAnswer > TAnswersList;

    TAnswersList Answers;

    const std::wstring& getMessage() const { return _message;};

    //CSpeaker* _speaker;
    std::wstring _message;
    //std::string _soundFilename;
    CSound* _sound;
};

#endif
