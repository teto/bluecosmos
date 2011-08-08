/**
* \file menu.cpp
*
* utiliser la camera de gameengine ou la sienne propre ?
*/

#include "CScoreState.hpp"
#include "COptionsState.hpp"
#include "../fightingState/CSinglePlayerState.hpp"
#include "../game_engine.hpp"
#include <vector>
#include "IdList.hpp"
#include <fstream>
#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <fusion/core/string.hpp>

using namespace irr;

//const bool& savingScore,
CScoreState::CScoreState(const core::rectf& pos) :
//TGameState("Score interface"),
_menu(0),
_pos(pos),
_editBox(0),
_scoreToRegister(-1)
{
    //_scores.reserve(_NB_OF_SCORES);
    resetScores();

    //_INFO << "taille du vecteur au score" << _scores.size();
}


CScoreState::~CScoreState(){
    _menu->remove();
    saveScores();
}



void
CScoreState::sortScores()
{
    std::sort ( _scores.begin(),_scores.end() );
}


void
CScoreState::resetScores(){



    //BOOST_FOREACH(TScore j,_scores)
    for(int i = conf::_NB_OF_SCORES-1; i >= 0 ; --i)
    {
        _scores[i] = i*100;

    }
}


bool
CScoreState::saveScores(){

    _INFO << "saving scores to file (TODO)";

#if 0
    std::wofstream file( _SCORES_FILENAME );

    try {

        if(file.good()){

            fus::TCharStringBuilder text("<scores>\n");

            BOOST_FOREACH(TScore j,_scores)
            {
                _INFO << "ajout d'un score au fichier XML";
                text("<score pseudo=\"")("Your pseudo")("\" value=\"")(j)("\" />\n");
            }



            // fin du fichier
            text("\n</scores>");

            file << text.str().c_str();

        }
    }
    catch(...){
        _LOG_ERROR << "erreur lors de la sauvegarde des scores";
        return false;
    }
    file.close();

#endif
    return true;
}


void
CScoreState::onResume() {
    /// Show again the cursor
    engine()->showCursor(true);
}


void
CScoreState::onHold() {

}




bool
CScoreState::loadScores(){


    _INFO << "Loading of configuration file...";
#if 0

    pugi::xml_document doc;

    const char* filename = conf::_SCORES_FILENAME;
    pugi::xml_parse_result result = doc.load_file( filename );

    //
    if(!result){
        _LOG_ERROR << "Impossible to load config file [" << filename << "]: \n" << result.description();
        _LOG_ERROR << "Error offset: " << result.offset;
        return false;
    }

    pugi::xml_node root = doc.child(L"scores");
    if(!root){
        _LOG_ERROR << "Could not find [scores] node in [" << filename << "]";
        return false;
    }

    //////////////////////////////////////////////////////////////////
    /////   Load each bind
    //////////////////////////////////////////////////////////////////
    //for (pugi::xml_node bind = player.child("bind"); bind; bind = bind.next_sibling("bind")){
    int i = 0;
    for (pugi::xml_node_iterator it = root.child(L"score").begin(); it != root.end(); ++it,++i) {
        //_scores[i] = it->attribute(L"player").value();
        _scores[i] = it->attribute(L"value").as_int();
    }



#endif
    return true;
}


/**** Function Init() ****/
void
CScoreState::init(){

    //TGameState::Init( game );



//    /// Create initial menu

//    loadScores();
    GUI_CreateMainMenu();

}


void
CScoreState::addScore( const std::string& pseudo, const int& newScore){

//    int i = 0;
//    do {
//        if(newScore > _scores[i])
//    }
//    for(; i < _NB_OF_SCORES;++i)

// TODO find lowest score
// TODO inserer le score
    //sortScores();
    //_scores.back() = newScore;

    // TODO enregistrer le pseudo + tard
//    _scores[i] = newScore;
}


bool
CScoreState::OnEvent(const SEvent& event){


	switch (event.EventType){

        //case EET_MOUSE_INPUT_EVENT:break;

	    case EET_GUI_EVENT:
            {

            s32 id = event.GUIEvent.Caller->getID();
            //gui::IGUIironment* env = engine()->device->getGUIEnvironment();

            switch(event.GUIEvent.EventType){


                case EGET_BUTTON_CLICKED:
                    switch(id){

                        // if pushed button
                        case NGuiIds::SaveScore:
                            // Button clicked
                            {
                                std::string result;
                                fus::convertIntoNarrowString(_editBox->getText(),result);
                                addScore( result , _scoreToRegister);
                            }
                            //this->remove();
                            popThisState();
                            return true;

                        case NGuiIds::QuitGame:
                            _INFO << "user asked to quit";
                            engine()->Quit(); //device->closeDevice();
                            return true;

                        default:
                            return false;
                    }
                    break;

                //!< when window
                case EGET_ELEMENT_CLOSED:
                    popThisState();

                    // IMPORTANT: si on retourne false alors irrlicht va vouloir traiter un event
                    // lie a un objet qui n'existe plus => bug
                    return true;

            default:
                break;
            }
            }

        /// Traiter le cas ou on a appuyer sur enter
        //case


	default: break;


}
    return false;
}



/// \function Draw()
void
CScoreState::Draw()
{
    scene()->drawAll();
    _menu->draw();
}



/// mettre a jouer la camera ici
void
CScoreState::Update()
{


}



bool
CScoreState::getScoreAsString(std::wstring& baseString,const int& entier)
{

    try {
        //
        //utiliser wformat
        boost::wformat formattedScore(L"%1$08d");
        formattedScore%entier;
        baseString.append(formattedScore.str().c_str()  );
        return true;
    }
    //formattedScore.exceptions(boost::io::all_LOG_ERROR_bits)
    //catch(...){
    catch(boost::io::format_error& e){
        _LOG_ERROR << "erreur lors du formattage" << e.what();
        return false;
    }
}


// Score = score à enregistrer
void
CScoreState::displayAddScore(const int& score)
{
    _scoreToRegister = score;
    //if(!_editBox)
    //_optionalElements->setText(L"Your name");
    _INFO << "u may register your score";
    _optionalElements->setVisible(true);
    _optionalElements->setEnabled(true);


}

int
CScoreState::getMinScore()
{
    // Vu que c'est trie:
    int lowestScore =  _scores[ conf::_NB_OF_SCORES-1];
    _INFO << "Score le plus bas: " << lowestScore;
    return lowestScore;
}



/// Create main menu ( = 1st to be displayed )
// Faire un menu de taille dynamique
//const irr::core::rectf& pos
void
CScoreState::GUI_CreateMainMenu() {

    irr::core::recti fakeRect(0,0,0,0);
    _menu = gui()->addWindow( fakeRect , true, L"LAWL",gui()->getRootGUIElement() );
    _menu->setRelativePositionProportional( _pos );
    //getCloseButton()->setVisible(false) ;
    _menu->setDrawTitlebar(false);
    _menu->setDraggable(false);
// TODO creer un tableau
//    core::recti pos;
//    table->setRelativPosition();






    irr::core::rectf size(0.2f, 0.2f, 0.8f, 0.8f);
    gui::IGUITable* table = gui()->addTable( fakeRect );
    _menu->addChild( table );
    table->setRelativePositionProportional( size );
    table->addColumn ( L"Name");
    table->addColumn ( L"Score");
    table->setResizableColumns(true);
    table->setColumnWidth(0,100);
    table->setColumnWidth(1,100);
    //table->setDrawBackground(true);

    loadScores(  );
    std::wstring strScore;
    for(int i = 0; i < conf::_NB_OF_SCORES; ++i)
    //video::SColor
    //irr::u32
    //BOOST_FOREACH(TScore i,_scores)
    {
        _INFO << "info added" << i;
        table->addRow(i);
        //El creator
        table->setCellText (i,0, L"El creator", video::SColor (255,0,0,0));
        //boost::format();
        getScoreAsString( strScore , _scores[i]);
        table->setCellText (i, 1, strScore.c_str() );
        strScore.clear();
    }


    // Partie optionnelle a montrer seulement pr ajouter un score
    //_staticText =
    //irr::gui::IGUIStaticText* staticText = gui()->addStaticText(L"Your score",core::recti(0,30,220,100));
    _optionalElements = gui()->addTab(fakeRect);
    _menu->addChild(_optionalElements);
    _optionalElements->setRelativePositionProportional( core::rectf(0.f,0.f,1.f,1.f) );
    _INFO << "taille de optional elements";

    //_optionalElements->setDrawBackground(true);
    //_optionalElements->setBackgroundColor(video::SColor(255,255,255,0));

    _editBox = gui()->addEditBox(L"EDIT BOX",
                                 core::recti(10,10,200,40),
                                 false  //!< border
                                 );

    gui::IGUIButton* button = gui()->addButton( recti(220,10,300,40), 0,NGuiIds::SaveScore, L"Save score",L"Save your stats into file" );

    _optionalElements->addChild( _editBox );
    _optionalElements->addChild( button );

//_editBox->created;
    _optionalElements->setVisible(false);
    _optionalElements->setEnabled(false);

}

