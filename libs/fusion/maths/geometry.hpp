/**
* \file geometry.h
*/
#ifndef _FUSION_GEOMETRY_HPP_INCLUDED
#define _FUSION_GEOMETRY_HPP_INCLUDED

#include "vector.hpp"

FUSION_NAMESPACE_BEGIN

enum EAxe{
EAxeX = 0,
EAxeY = 1,
EAxeZ = 2
};

//ttes les fct d'1 base
class COrthogonalDirectBase {
/*Draw / Rotate => utiliser des enum
*/
public:
COrthogonalDirectBase();
void RotateAroundRightVector(const double& angle);
void RotateAroundUpVector(const double& angle);
void RotateAroundForwardVector(const double& angle);
//void Rotate(const EAxe& axe,const double& angle);
// translate according to local repair
TVectord LocalTranslate(const TVectord& v);
TVectord LocalTranslate(const double& vx,const double& vy,const double& vz);
void Normalize();

TVectord x,y,z;
//TVectord axes[3];
};



FUSION_NAMESPACE_END

#endif // GEOMETRY_H_INCLUDED
