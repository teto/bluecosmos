/**
* \file macros.h
* Define macros
*/
#ifndef _FUSION_MATHS_MACROS_HPP_INCLUDED
#define _FUSION_MATHS_MACROS_HPP_INCLUDED


#include <algorithm>
//#include <cmath>

const float PIperso = 3.14159265358979323846;

template<typename T>
inline T TO_RAD(const T& x) {


    return (((x)* PIperso)/180.f );
}

//#define TO_RAD(x) ((x)*M_PI)/180.f        //!< Convert degrees to radians
#define TO_DEG(x) ((x)*180)/PI   //!< The opposite

//#define CLAMP(value,bottomLimit,upLimit) std::min(bottomLimit, std::max(upLimit,value))


//#define _FUSION_POW2(x) (x)*(x)

template<typename T>
inline T _FUSION_POW2(const T& x) {
    return ( (x)*(x)  );
}


template<typename T>
inline T _FUSION_POW3(const T& x) {
    return ( (x)*(x)*(x) );
}
//
//template<typename T>
//inline T clamp(const float& ratio,const float& param1,const float& param2) {
//
//    return ( (x)*(x)*(x) );
//}
//
//template<typename T>
//inline T interpolate(const float& ratio,const float& param1,const float& param2) {
//
//    return ( (x)*(x)*(x) );
//}

#define FUS_PI			3.14159265358979323846
#define FUS_EPSILON			0.0000000000000000001




// set float to 0 if within tolerance
//#define ZERO_CLAMP(x)	( (EPSILON > fabs(x)) ? 0.0f :(x) )

// float equality test s'assure que x compris entre v - epsilon et v + epsilon
//#define WITHIN_RANGE(x,v)	( ((v) - EPSILON) < (x) && (x) < ((v) + EPSILON) )
#define WITHIN_RANGE(x,v)	( std::abs(v-x) < FUS_EPSILON )

template<typename T>
inline float sign(const T& a) {
    return ( (a)/fabs(a));
}

#define EPSILON(x) std::numeric_limits<x>::epsilon()


#endif // MACROS_H_INCLUDED
