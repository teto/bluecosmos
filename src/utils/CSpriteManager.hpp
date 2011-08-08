/**
\file
\author
**/
#ifndef CSPRITEMANAGER_HPP_INCLUDED
#define CSPRITEMANAGER_HPP_INCLUDED


#include "ISprite.hpp"
#include <list>
#include <irrlicht.h>

class C2DSprite;
class CBillboardSprite;
//class CGameEngine;



class CSpriteManager
{
public:
    // passer ici un irr::IrrlichtDevice
    irr::IrrlichtDevice *_device;

    CSpriteManager(irr::IrrlichtDevice *);

    //ISprite* addSprite(ISprite* );
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */

    C2DSprite* add2Dsprite(irr::video::ITexture* texture,const irr::s32& nb_largeur,const irr::s32& nb_hauteur,const bool& autoUpdated);



    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */

    CBillboardSprite* addBillboardSprite(irr::video::ITexture* texture,const irr::s32& nb_largeur,const irr::s32& nb_hauteur);

    //void update(const irr::u32&);

    // Does nothing
    //void draw2Dsprites();

    virtual ~CSpriteManager();

protected:

private:


};

#endif // CEXPLOSIONS_HPP_INCLUDED
