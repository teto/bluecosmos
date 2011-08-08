/**
* \file
*
*/
//
#include <fusion/splines.hpp>

FUSION_NAMESPACE_BEGIN

void CSplineB::Update(){
}


TVectorf
CSplineB::Calculate(const float& t) const{
    int t0 = 0;
    while(t0 < t )
        t0++;
    t0--;

    float b[4];
    float T = t-t0;
    //remplacer (t-t0) par T
    b[0] = T*T*T/6;
    b[1] = 1+3*T*(1+(t-t0)-(t-t0)*(t-t0));
    b[1] /= 6;
    b[2] = 4-6*(t-t0)*(t-t0)+3*(t-t0)*(t-t0)*(t-t0);
    b[2] /= 6;
    b[3] = 1+3*T*(-1+3*T-T*T);
    b[3] /= 6;

    fus::TVectorf v;
    //v = mKeys[i]*b[0]
    return v;
}

CSplineB::CSplineB(){
}

CSplineB::~CSplineB(){
}

FUSION_NAMESPACE_END
