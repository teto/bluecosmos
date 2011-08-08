/**
* \file
*
*/
#include <fusion/maths.hpp>
#include <SFML/System.hpp>

FUSION_NAMESPACE_BEGIN

/*
void
COrthogonalDirectBase::D() {
    std::cout << "forward  " << y << std::endl;
    std::cout << "right " << x.x << "/" << x.y << "/" << x. << std::endl;
    std::cout << "up  " << z.x << "/" << z.y << "/" << z. << std::endl;

}


void COrthogonalDirectBase::RotateAroundAxis(){
}
*/

COrthogonalDirectBase::COrthogonalDirectBase(){
    x.Set(1,0,0);
    y.Set(0,1,0);
    z.Set(0,0,1);
}

void
COrthogonalDirectBase::RotateAroundForwardVector(const double& angle){

    z = z * std::cos(angle) + x * std::sin(angle);
    x = y ^ z;
}


void
COrthogonalDirectBase::RotateAroundRightVector(const double& angle){

    y = y * std::cos(angle) + z * std::sin(angle);
    z = x ^ y;
}

void
COrthogonalDirectBase::Normalize(){
    x.Normalize();
    y.Normalize();
    z.Normalize();
}

TVectord
COrthogonalDirectBase::LocalTranslate(const TVectord& v){
    return(  y * v.x + x * v.y + z * v.z );
}

TVectord
COrthogonalDirectBase::LocalTranslate(const double& vx,const double& vy,const double& vz){
    return LocalTranslate( TVectord(vx,vy,vz));
}

/*
void
COrthogonalDirectBase::Rotate(const EAxe& axe,const double& angle) {


}*/


void
COrthogonalDirectBase::RotateAroundUpVector(const double&  angle){

    y = y * std::cos(angle) + x * std::sin(angle);
    x = y ^  z;

}

FUSION_NAMESPACE_END
