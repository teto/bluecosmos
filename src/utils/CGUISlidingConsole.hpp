#ifndef _CGUISLIDINGCONSOLE_HPP_INCLUDED
#define _CGUISLIDINGCONSOLE_HPP_INCLUDED

#include <irrlicht.h>
#include "IGUIConsole.hpp"

namespace irr {

namespace gui {


class CGUISlidingConsole :
    //public IGUITab
    public IGUIConsole
{
public:

    //IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle
    CGUISlidingConsole(
                IGUIEnvironment* environment,
                const core::recti& rectangle,
                IGUIElement* parent,
                s32 id = -1
                );



    virtual void draw();

};

}

}
#endif
