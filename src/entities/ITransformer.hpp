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
#include <array>
#include <irrlicht.h>
#include <vector>
#include <fusion/logging/ILogger.hpp>
#include "SModeDescription.hpp"

using namespace irr;



// passer en parametre les noms des differents boosters, du mesh, ces caracteristiques
//template<std::size_t N>
// TODO Le transformer en Node

class ITransformer : public irr::scene::IAnimationEndCallBack
{

public:
//-render
//-getBoundingBox
//onAnimate

protected:
    bool _transforming;




public:
    // TODO protected
    irr::scene::IAnimatedMeshSceneNode* _animatedNode;

    ITransformer(irr::scene::IAnimatedMeshSceneNode* node = 0);
    ~ITransformer();


//    float getCruiseSpeed();
    float getTransformationAdvancement();

    //bool init(irr::scene::IAnimatedMeshSceneNode*);
    //const bool& isTransforming() const {return _transforming;};

    bool isTransforming() const;


    void load(irr::scene::IAnimatedMeshSceneNode* node);
    bool setTargetedFrame(const int& targetedFrame);


    virtual void OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* node);

};

//#include "transforming.inl"

#endif
