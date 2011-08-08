/**
* \file
*/
#ifndef _FUSION_SPRITE_HPP_INCLUDED
#define _FUSION_SPRITE_HPP_INCLUDED





//#include <fusion/maths/macros.hpp>
#include <irrlicht.h>


//template<typename TEXTURE>
class ISprite
{

public:
    ISprite();
    virtual ~ISprite();

    virtual bool init(irr::video::ITexture* texture,const irr::s32& nb_largeur,const irr::s32& nb_hauteur);

    void setFrameTime(const irr::u32& frameTime) { _frameTime = frameTime;};
    void setLoopMode(const irr::s32& start,const irr::s32& end);
    void enableLoop(const bool& loop) { _loop = loop;};

    irr::s32 getCurrentCol() { return(_currentFrame%_horizontal);};
    irr::s32 getCurrentLine() { return((_currentFrame-getCurrentCol())/_vertical); };
    virtual bool update(const irr::u32& elapsedTime);

    //const irr::core::position2d< irr::s32 > &  destPos,
    //virtual void draw(irr::video::IVideoDriver* driver) = 0;

    irr::s32 getFramesNumber() const;


protected:
    irr::video::ITexture *_texture;
    void setFrameNumbers(const irr::s32& horizontal,const irr::s32& vertical);

    //bool mRepeat;
    irr::s32 _startFrame,_endFrame,_currentFrame;
    irr::s32 _horizontal,_vertical;//horizontal & vertical nb
    irr::u32 _frameTime;
    irr::u32 _timeElapsedSinceLastFrame;


    bool _loop;

    irr::core::dimension2di _clippingSize;
};



#endif // SPRITE_HPP_INCLUDED
