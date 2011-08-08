/**
* \file menu.h
* Utiliser std::tr1
**/
#ifndef _BC_CSCORESTATE_HPP_INCLUDED
#define _BC_CSCORESTATE_HPP_INCLUDED


#include "IGameState.hpp"
#include "../config.hpp"
#include <irrlicht.h>
#include <array>
//#include "../pugixml/pugixml.hpp"


class CScoreState :
    public IGameState<NStateId::Score,true>
{

public:
//    enum EMode {
//    Modification,
//    NoGraphics,
//    Consultation
//    };
//const bool& savingScore,
    CScoreState(const irr::core::rectf& pos);
    ~CScoreState();

	void init();
	//void CleanUp();

    bool loadScores();
    bool saveScores();

	void Update();
	void Draw();

	void resetScores();

    void onResume();
    void onHold();

    bool OnEvent(const irr::SEvent& event);


static bool getScoreAsString(std::wstring& baseString,const int& entier) ;
    void displayAddScore(const int& score);
    int getMinScore();


    void addScore( const std::string& pseudo, const int& newScore);

protected:
//const irr::core::rectf& pos
    void GUI_CreateMainMenu();              //!< Create main (home) menu
    void sortScores();

    std::string _filename;
    int _scoreToRegister;


    // REmpalcer ici par un TScoreDescriptor
    typedef int TScore;
    //typedef std::array<TScore,_NB_OF_SCORES> TScoreMap;
    // TODO _NB_OF_SCORES
    typedef std::array<TScore,10> TScoreMap;
    TScoreMap _scores;

    irr::gui::IGUIWindow* _menu;
    irr::gui::IGUIEditBox* _editBox;
    irr::gui::IGUIStaticText* _staticText;
    irr::gui::IGUITab* _optionalElements;

    irr::core::rectf _pos;

    //qwxml::CXmlDocument _file;

};


#endif
