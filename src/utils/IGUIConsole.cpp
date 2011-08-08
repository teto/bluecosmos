#include "IGUIConsole.hpp"
//#include <fusion/logging/ILogger.hpp>
#include <fusion/fusion.hpp>
#include <fusion/core/string.hpp>

#define _TOOLBAR_HEIGHT 30

namespace irr {
namespace gui {

IGUIConsole::IGUIConsole(
                IGUIEnvironment* gui,
                const core::recti& rectangle,
                IGUIElement* parent,
                s32 id
                ) :
    // Type perso
    //IGUITab( gui, parent, id, rectangle),
    IGUIElement(EGUIET_ELEMENT, gui,parent,id, rectangle),
    _editBox(0),
    _listBox(0),
    _currentIndex(-1)
{


    #ifdef _DEBUG
    setDebugName("IGUIConsole");
    #endif


    //_index = -1;

    video::SColor  bgColor(100,255,0,255);
    video::SColor  textColor(255,0,255,0);


    int commandLineHeight = 20;
    int consoleWidth    = rectangle.getWidth();
    int consoleHeight   = rectangle.getHeight();
    //_tab =   gui->addTab (tabPos);

    //rectangle, parent / id /drawBackground
    // 30 ==> hauteur de la barre de boutons
    core::recti listSize(0,0,consoleWidth,consoleHeight-commandLineHeight-_TOOLBAR_HEIGHT);

    _listBox = gui->addListBox(listSize);
    this->addChild(_listBox);

    //_listBox->addItem(L"Console Item 1");

    //  text/rectangle/border /parent/id
    core::recti commandLineSize( 0,consoleHeight-commandLineHeight-_TOOLBAR_HEIGHT,consoleWidth,consoleHeight-_TOOLBAR_HEIGHT );

    ///
    _editBox = gui->addEditBox(L"Console",
                               commandLineSize,
                               false                //!< Enable border
                               );
    this->addChild(_editBox);


    _editBox->setDrawBorder(true);
    _editBox->setMultiLine(false);
    _editBox->setAutoScroll(true);

//    this->setBackgroundColor(bgColor);
//    this->setDrawBackground(true);
//    this->setTextColor(textColor);
    _listBox->setAutoScrollEnabled(true);

//command.c_str()
    _listBox->addItem( L"Test" );
}

/*
	if ( Parent )
	{
        SEvent e;
        e.EventType = EET_GUI_EVENT;
        e.GUIEvent.Caller = this;
        e.GUIEvent.Element = 0;
        e.GUIEvent.EventType = type;

        Parent->OnEvent(e);
	}
	*/



//! draws the element and its children
void
IGUIConsole::draw()
{
	if (!IsVisible)
		return;

	IGUISkin *skin = Environment->getSkin();

//&& DrawBackground
	if (skin)
		skin->draw2DRectangle(this, BackColor, AbsoluteRect, &AbsoluteClippingRect);

	IGUIElement::draw();
}




//! sets the color of the background, if it should be drawn.
void
IGUIConsole::setBackgroundColor(const video::SColor& c)
{
	BackColor = c;
}


//! returns the color of the background
const video::SColor&
IGUIConsole::getBackgroundColor() const
{
	return BackColor;
}



bool
IGUIConsole::addButton(const wchar_t* name,const wchar_t* associatedCommand) {
    //(const core::rect< s32 > &rectangle, IGUIElement *parent=0, s32 id=-1, const wchar_t *text=0, const wchar_t *tooltiptext=0
    //DesiredRect
//
//    if(_buttons.empty()){
//        //
//        rectangle =
//    }
//    else {
//        rectangle = _buttons.back()->
//    }

    core::rect< s32 > rect(0,DesiredRect.getHeight()-_TOOLBAR_HEIGHT,100,DesiredRect.getHeight());
    IGUIButton* button = Environment->addButton(rect,this,-1,name,associatedCommand);
    //this->addChild(button);
    //rectangle.getWidth()
    _buttons.push_back( button );
    return true;
}





bool
IGUIConsole::removeButton(const wchar_t* name) {
    //removeChild
}



void
IGUIConsole::setCommand(const u32& id) {

    if( (id >= 0) && (id < _listBox->getItemCount() ) ){

        _editBox->setText( _listBox->getListItem( id ) );
        _listBox->setSelected ( id );

        // Hack to put caret at the end
        SEvent event;
        event.EventType = EET_KEY_INPUT_EVENT;
        event.KeyInput.PressedDown = true;
        event.KeyInput.Key = KEY_END;
        _editBox->OnEvent(event);
        _currentIndex = id;
    }
}


void
IGUIConsole::flushCommand() {

    // TODO verifier le cas ou c'est vide

    _listBox->addItem( _editBox->getText() );
    _editBox->setText(L"");

//-1
    _currentIndex = _listBox->getItemCount();
//
//    if(  <= 0){
//        _currentIndex = 0;
//    }
//    else {
//
//    }

}



void
IGUIConsole::setCommand(const wchar_t* command ){
    _editBox->setText( command );
    // Envoyer un
}


/// Environment->hasFocus(this)
bool
IGUIConsole::OnEvent(const SEvent& event) {

// /TODO si l'editbox envoie un signal "enter" alors on enregistre la commande et on cree un evenement personnalise


//    if(){
//        return false;
//    }

    //if(IsEnabled){

//    _INFO << "GuiConsole event " << event.EventType;

//    if(Environment->hasFocus(this)){
//
//        _INFO << "we are focused";
//    }

//    if(!Environment->hasFocus(this)) {
//        return false;
//    }
    IGUIElement* caller = 0;

        switch(event.EventType)
        {
            case EET_GUI_EVENT:
                caller = event.GUIEvent.Caller;
                switch(event.GUIEvent.EventType){

                    case EGET_ELEMENT_FOCUSED:
                        // TODO donner le focus a l'editBox
                        Environment->setFocus( _editBox );
                        break;
                    case EGET_ELEMENT_LEFT:
                        break;

                    case EGET_LISTBOX_SELECTED_AGAIN:
                        if(caller == _listBox) {
                            //_INFO << "element chosen from list";
                            //const s32 id =
                            setCommand( _listBox->getSelected () );
                            Environment->setFocus( _editBox );
                            //_editBox->setText( _listBox->getListItem( _listBox->getSelected () ) );

                        }
                        return false;
                    case EGET_BUTTON_CLICKED:
                        // If button belongs to console then
                        if(isMyChild(caller)) {

                            _editBox->setText( caller->getToolTipText().c_str() );

                            // envoyer la commande
                            SEvent transformedEvent             = event;
                            transformedEvent.EventType          = EET_GUI_EVENT;
                            transformedEvent.GUIEvent.EventType = EGET_EDITBOX_ENTER;
                            transformedEvent.GUIEvent.Caller    = this;

                            return IGUIElement::OnEvent(transformedEvent);
                        }
                        //return false;
                        break;

                    case EGET_EDITBOX_ENTER:

                        if (event.GUIEvent.Caller == _editBox)
                        {
                            // std::string result;
                            // fus::convertIntoNarrowString(_editBox->getText(),result);
                            //_INFO << "ENTER !!";
                            SEvent transformedEvent             = event;
                            transformedEvent.EventType          = EET_GUI_EVENT;
                            transformedEvent.GUIEvent.EventType = EGET_EDITBOX_ENTER;
                            transformedEvent.GUIEvent.Caller = this;

                            return IGUIElement::OnEvent(transformedEvent);

                            //flushCommand();

                            //MouseMarking = false;
                            //setTextMarkers(0,0);
                            // alors on envoie un evenement COnsole
                        }
                        break;
                        //return false;

                    default:
                        break;
                }
                break;


            case EET_KEY_INPUT_EVENT:

                if(!event.KeyInput.PressedDown){
                    return false;
                }

                switch(event.KeyInput.Key){

                    case KEY_UP:
                        _INFO << "previousCommand";
                        setCommand( _currentIndex - 1 );

//                        if( setCommand( _currentIndex - 1 )){
//                            _currentIndex -= 1;
//                        }
                        return true;

                    case KEY_DOWN:

                        _INFO << "next console command";
                        setCommand( _currentIndex + 1 );
//                        if( setCommand( _currentIndex + 1 )){
//                            _currentIndex += 1;
//                        }
                        return true;

                    default:
                        return true;
                };
//
//    		case EET_MOUSE_INPUT_EVENT:
//    		    switch (event.MouseInput.EventType)
//    		    {
//    		        case :
//    		            break;
//
//    		        default:
//    		            break;
//    		    }

    			break;




            default:
                break;
        };

    //}

    // check avec le parent
    return IGUIElement::OnEvent(event);
}




//! sets the color of the text
//void
//IGUIConsole::setTextColor(const video::SColor& c)
//{
//	OverrideTextColorEnabled = true;
//	TextColor = c;
//}
//
//
//
//const video::SColor&
//IGUIConsole::getTextColor() const
//{
//	return TextColor;
//}


////! returns true if the tab is drawing its background, false if not
//bool
//IGUIConsole::isDrawingBackground() const
//{
//	_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
//	return DrawBackground;
//}
//

}   //!< end of namespace gui

} //!< end of namespace irr
