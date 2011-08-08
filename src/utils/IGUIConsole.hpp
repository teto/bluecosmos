#ifndef _IGUICONSOLE_HPP_INCLUDED
#define _IGUICONSOLE_HPP_INCLUDED

#include <irrlicht.h>

namespace irr {

namespace gui {


//struct SConsoleShortcut {
//    SConsoleShortcut ();
//    gui::IGUIButton* Button;
//    core::stringw AssociatedCommand;
//};



class IGUIConsole :
    //public IGUITab
    public IGUIElement
{
public:

    //IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle
    IGUIConsole(
                IGUIEnvironment* environment,
                const core::recti& rectangle,
                IGUIElement* parent,
                s32 id = -1
                );



    void setBackgroundColor(const video::SColor& c);
    const video::SColor& getBackgroundColor() const;
    virtual void draw();

    // setCommand from index
    // Pour permettre d'enregistrer le resultat de la commande
    //virtual void addResult();
    virtual void setCommand(const u32&);
    virtual void setCommand(const wchar_t*);
    virtual void flushCommand();
    //virtual void setCommand(const s32&);
    const wchar_t* getText() const {
        return _editBox->getText();
    }
    virtual bool OnEvent(const SEvent&);

    // Associated command is tooltip
    bool addButton(const wchar_t* name,const wchar_t* associatedCommand);
    bool removeButton(const wchar_t* name);

private:
    s32 _currentIndex;
    IGUIEditBox* _editBox;
    core::array<gui::IGUIButton*> _buttons;
    //IGUIToolbar*
    //associatedToolbar

    // Transformer le listbox en staticText et enregistrer les commandes dans un core aray a part
    IGUIListBox* _listBox;
    video::SColor BackColor;
    //IGUIStaticText* _text;
    //core::std::array<core::stringw> _commandLists;
};

}

}
#endif
