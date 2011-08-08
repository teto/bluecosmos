/**
* \file
*/
#ifndef SPLINE_CATMULL_H_INCLUDED
#define SPLINE_CATMULL_H_INCLUDED

#include "ISpline.hpp"


FUSION_NAMESPACE_BEGIN


class CSplineCatmull : public ISpline {

public:

    void Update();
    TVectorf Calculate(const float& t) const;
    static bool Export(ISpline* spline);

    ESplineType GetType() const;
    CSplineCatmull();
    ~CSplineCatmull();
//protected:
    float mTendance,mContinu,mTension;;

};

FUSION_NAMESPACE_END

#endif
