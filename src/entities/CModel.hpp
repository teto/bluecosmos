
#ifndef CMODEL_HPP
#define CMODEL_HPP


#include <irrlicht.h>

class CModel
{
public:
    CModel();
    ~CModel();


//protected:
    int _life;
    float _range;
    int _bonus;
    float _maxSpeed;
    //irr::scene::IAnimatedMeshSceneNode* _node;
    irr::scene::IAnimatedMesh* _mesh;
//Damage,
//Range,
//Resistance
//Bonus
//IAnimatedMesh* _mesh;

// // Copy node
// generateNodeOfThisModel();

};



#endif
