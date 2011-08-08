/**
\file transforming.hpp
\brief
todo le rendre transformable

*/
#ifndef TRANSFORMING_HPP
#define TRANSFORMING_HPP

//#include "IEntity.hpp"
#include <map>
#include <list>
#include <fusion/macros.hpp>
#include <boost/array.hpp>
#include <irrlicht.h>
#include <vector>
#include <fusion/logging/ILogger.hpp>
#include "SModeDescription.hpp"
using namespace irr;



// passer en parametre les noms des differents boosters, du mesh, ces caracteristiques
//template<std::size_t N>
class CTransformingShip :
//public irr::scene::IAnimatedMeshSceneNode,
public SModeDescription,
public irr::scene::IAnimationEndCallBack
{

public:


protected:
    bool _transforming;
    irr::scene::IAnimatedMeshSceneNode* _animatedNode;

    bool _cyclic;

    bool transformIntoNextMode();
    bool transformIntoPreviousMode();

    void transformIntoLastMode();
    void transformIntoFirstMode();

    TMode _currentMode;
    TMode _targetedMode;

public:
    typedef SModeDescription TSpecsMap[ModesCount];
    typedef int TModeId;
    static TSpecsMap _specs;


    typedef std::vector<EMode> TAvailableModes;
    TAvailableModes _activeSpecs;


    void clearModes();
    // TODO renommer en addMode
    CTransformingShip& allowMode(const EMode& mode);


    void enableCyclicTransformation(const bool& enable){
        _cyclic = enable;
    }

    const bool& isCyclic() const { return _cyclic; }

    //typedef TAvailableModes::iterator TMode;


    void forceMode(const EMode& mode);

    CTransformingShip(irr::scene::IAnimatedMeshSceneNode* node);
    ~CTransformingShip();


//    float getCruiseSpeed();
    float getTransformationAdvancement();

    //bool init(irr::scene::IAnimatedMeshSceneNode*);
    const bool& isTransforming() const {return _transforming;};

    // TODO a supprimer ?
    //bool setBooster(const std::size_t& idBooster,const char*, irr::scene::IParticleSystemSceneNode*);


    void update();
    void Reset();
    bool setTargetedFrame(const int& targetedFrame);


    virtual void OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* node);



};

//#include "transforming.inl"

#endif
