#include <fusion/splines.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <GL/glu.h>
//#include "../core/vector.h"
//
// http://www.programmationworld.com/php/cours/index.php?page=cours&id_cours=63&affichage=2
// definir cette classe avec coeff à 0 = catmull-rom

/*This piece of code is a Catmull-Rom spline.  I love it because 1) the curved line it describes passes thru the control points, unlike a b-spline, and 2) if you use it for enemy ship paths, it results in nice curves with smooth velocity changes.

It takes four points, and the value t is 0.0 - 1.0, and represents how far you are between the middle two points.

Code:
// *************************************************************************
void PointOnCurve(TPoint &out, float t, TPoint p0, TPoint p1, TPoint p2, TPoint p3)
{
	float t2 = t * t;
	float t3 = t2 * t;
	out.x = 0.5f * ( ( 2.0f * p1.x ) +
		( -p0.x + p2.x ) * t +
		( 2.0f * p0.x - 5.0f * p1.x + 4 * p2.x - p3.x ) * t2 +
		( -p0.x + 3.0f * p1.x - 3.0f * p2.x + p3.x ) * t3 );
	out.y = 0.5f * ( ( 2.0f * p1.y ) +
		( -p0.y + p2.y ) * t +
		( 2.0f * p0.y - 5.0f * p1.y + 4 * p2.y - p3.y ) * t2 +
		( -p0.y + 3.0f * p1.y - 3.0f * p2.y + p3.y ) * t3 );
}
*/

FUSION_NAMESPACE_BEGIN


// 1er & 2nd points = poignees des tangente
CSplineCatmull::CSplineCatmull(){

    mTendance = 0.5;
    mContinu = 0;
    mTension = -3;
}

CSplineCatmull::~CSplineCatmull(){

}


ESplineType CSplineCatmull::GetType() const {
    return ESplineCatmull;
}

TVectorf CSplineCatmull::Calculate(const float& t) const{
    // 0 et 1 = poignees
    int i = 2;
    // pb pour le dernier point non ?
    while(10*(i-2) < t && i < (int) mKeys.size()-1)
        ++i;

    i--;

    TVectorf v;
    v.x = (2*t*t*t-3*t*t+1)*mKeys[i].v.x;
    v.x += (-2*t*t+3*t*t)*mKeys[i+1].v.x;
    v.x += (t*t*t-2*t*t+t)*mKeys[i].te.x;
    v.x += (t*t*t-t*t)*mKeys[i+1].te.x;

// Ici je crois que c'est ts et non te ( à verifier )
    v.y = (2*t*t*t-3*t*t+1)*mKeys[i].v.y;
    v.y += (-2*t*t+3*t*t)*mKeys[i+1].v.y;
    v.y += (t*t*t-2*t*t+t)*mKeys[i].te.y;
    v.y += (t*t*t-t*t)*mKeys[i+1].te.y;
    return v;
}

// 10 sec entre chaque point + corriger tangentes
 void CSplineCatmull::Update(){
        if(mKeys.size() < 3)
            return;

        // Pour chaque point
        for(unsigned int i = 2; i < mKeys.size();i++){

            mKeys[i].time = 10*(i-2);

            /// on pourrait faire un switch ici
            //Si premier point
            if(i == 2){

                TVectorf temp(mKeys[2].v,mKeys[0].v);
                mKeys[2].te = temp*0.5;
            }
            //si dernier point
            else if(i == mKeys.size()-1){

                TVectorf temp(mKeys[i].v,mKeys[1].v);
                mKeys[i].te = temp*0.5;//mTension
            }
            //sinon on met a jour  les tangentes
            else{
                TVectorf temp(mKeys[i-1].v,mKeys[i+1].v);
                mKeys[i].te = temp*0.5f;
                mKeys[i].te = TVectorf(mKeys[i-1].v,mKeys[i].v)*((1-mTension)*(1-mContinu)*(1+mTendance)/(mKeys[i].time-mKeys[i-1].time));
                mKeys[i].te += TVectorf(mKeys[i].v,mKeys[i+1].v)*((1-mTension)*(1+mContinu)*(1-mTendance)/(mKeys[i+1].time-mKeys[i].time));
                mKeys[i].ts =TVectorf(mKeys[i-1].v,mKeys[i].v)*((1-mTension)*(1+mContinu)*(1+mTendance)/(mKeys[i].time-mKeys[i-1].time));
                mKeys[i].ts += TVectorf(mKeys[i].v,mKeys[i+1].v)*((1-mTension)*(1-mContinu)*(1-mTendance)/(mKeys[i+1].time-mKeys[i].time));

                float A = mKeys[i].ts.Length()/(mKeys[i].ts.Length()+mKeys[i].te.Length());
                float B = mKeys[i].te.Length()/(mKeys[i].ts.Length()+mKeys[i].te.Length());
                mKeys[i].te *= A;
                mKeys[i].ts *= B;

            }
        }
}


FUSION_NAMESPACE_END


