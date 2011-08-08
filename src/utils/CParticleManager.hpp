/**
\file
\author
**/
#ifndef CParticleManager_HPP_INCLUDED
#define CParticleManager_HPP_INCLUDED



#include <list>
#include <irrlicht.h>
//#include <irrlicht.h>

// SPARK lib
#include <SPK.h>
#include <SPK_IRR.h>

//class IObserver;
class IParticleManager {

};
// renommer en CParticleManager

class CParticleManager : public IParticleManager
//public IObserver
{
public:
    // passer ici un irr::IrrlichtDevice
    irr::IrrlichtDevice *_device;

    CParticleManager(irr::IrrlichtDevice *);

    //void handleMessage ( const CMessage& message );

    SPK::IRR::IRRSystem* createExplosion(const bool& autoRemove =false);
    //irr::scene::ISceneNode*
    SPK::IRR::IRRSystem* createBooster(const bool& autoRemove =false);
    //void createBooster();

    virtual ~CParticleManager();


    void update();

protected:
    void createBaseExplosion();
    void createBaseBooster();
    void registerSystem(SPK::IRR::IRRSystem*);

private:

    SPK::SPK_ID _explosionID;
    SPK::SPK_ID _boosterID;

    typedef SPK::IRR::IRRSystem*  TSystem;
    typedef std::list<TSystem> TParticleSystems;

    TParticleSystems _systems;
};

#endif // CEXPLOSIONS_HPP_INCLUDED
