/**
* \file single.h
**/
#ifndef CDialogState_HPP
#define CDialogState_HPP

#include "../states/IGameState.hpp"
#include "../entities/player.hpp"
#include <map>
#include <boost/weak_ptr.hpp>

#include <list>
#include <irrlicht.h>
#include <memory>
#include "../utils/IClock.hpp"

namespace fus
{
    class CLuaThread;
    class CLuaVM;
}

//class CSpeaker;
class CSpeech;
//class CFadingImage;


using namespace irr;
using namespace gui;
using namespace scene;
using namespace core;

void enableMenu(irr::gui::IGUITab* , const bool&);



class CDialogState :
    public IGameState<NStateId::Solo,true>
{
private:

    //typedef std::pair<CSpeaker*,CSpeech*> TDialog;
    TPlayerReply _lastPlayerReply;

    irr::gui::IGUITab* _dialogTab;


    gui::IGUIListBox* _answers;

protected:

    void GUI_CreateDialogTab();


    bool setupLuaThread();

    //! Creer un animator

    CPlayer* _player;//vont etre geree via entitymanager

public:
    // partie dialogue
    void showMessage(CSpeaker* speaker, CSpeech* speech);
    TPlayerReply getUserReply() const;


    // TODO la je passe forcement le nom du niveau a charger
    CDialogState();
    ~CDialogState();


	void Update();


    void onResume();
    void onHold();

	void CleanUp();

	void Draw();
	bool OnEvent(const irr::SEvent&);


    boost::scoped_ptr<fus::CLuaVM> _script;


//    CSpeaker* createActor(const std::string&,const std::string&);

    static CSpeech* createSpeech(const std::string& );


    void update( const TTimer::TimeType&);


protected:
};

#endif
