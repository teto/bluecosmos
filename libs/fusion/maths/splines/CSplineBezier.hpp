/**
* \file
*/
#ifndef SPLINE_BEZIER_H_INCLUDED
#define SPLINE_BEZIER_H_INCLUDED

#include "ISpline.hpp"

FUSION_NAMESPACE_BEGIN


class CSplineBezier : public ISpline {

public:
    CSplineBezier();
    ~CSplineBezier();


    TVectorf Calculate(const float& t) const;
    bool Export(const std::string& name);
    void Update();
    ESplineType GetType() const;

};

FUSION_NAMESPACE_END

#endif // SPLINE_BEZIER_H_INCLUDED
