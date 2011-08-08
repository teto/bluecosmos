#ifndef _CACTOR_HPP_INCLUDED
#define _CACTOR_HPP_INCLUDED

#include <string>
#include <irrlicht.h>


class CSpeaker
{


public:
    //fct toString();
    //
    CSpeaker(const std::wstring&,irr::video::ITexture* texture);
    //~CSpeaker();
    const std::wstring& getName() const { return _name;};
    irr::video::ITexture* getTexture() { return _texture;};

protected:
    std::wstring _name;
    irr::video::ITexture* _texture;
// reference a une image bientot
};

// An intervention



#endif
