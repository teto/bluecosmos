/**
* \file
*/
#ifndef _FUSION_CSPLINEB_HPP_INCLUDED
#define _FUSION_CSPLINEB_HPP_INCLUDED

#include "ISpline.hpp"

FUSION_NAMESPACE_BEGIN

class CSplineB : public ISpline {

void Update();
fus::TVectorf Calculate(const float& t) const;
CSplineB();
~CSplineB();


};

FUSION_NAMESPACE_END

#endif
