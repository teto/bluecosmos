/**
* \file spline.h
*
* \todo enregistrer l'echelle dans le fichier ? ou bien faire fonctio scale de la spline qui rescale tous les points
*
*/
#ifndef _FUSION_ISPLINE_HPP_INCLUDED
#define _FUSION_ISPLINE_HPP_INCLUDED


#include <cmath>
#include <vector>
//#include "../../core/resource.h"
#include <fusion/maths/vector.hpp>
//#include "../../maths/vector.h"

FUSION_NAMESPACE_BEGIN

////////////////////////////////////////////////////////////
/// Allow switching between different loggers
///
/// \param Pointer to a certain instance derivated from ILogger
///
////////////////////////////////////////////////////////////
enum ESplineType {
ESplineHermit,
ESplineBezier,
ESplineCatmull

};


////////////////////////////////////////////////////////////
/// Allow switching between different loggers
///
/// \param Pointer to a certain instance derivated from ILogger
///
////////////////////////////////////////////////////////////
struct SKey{
TVectorf v;//point
TVectorf te;//TVectorf t;//tangente entrante
TVectorf ts;//tangente sortante
float time;
SKey();
SKey(const TVectorf& Point,const TVectorf& Tangent,const float& Time = 0);
/**
* \function Scale
* \param w Width
* \param h Height
* \param d Depth
**/
void Scale(float w,float h = 1,float d = 1);
};
//typedef std::vector<SKey>::size_type TSizeType;

class ISpline {

public:

    ////////////////////////////////////////////////////////////
    /// Allow switching between different loggers
    ///
    /// \param Pointer to a certain instance derivated from ILogger
    ///
    ////////////////////////////////////////////////////////////
    int AddKey(const TVectorf& v,const TVectorf& t,const float& time = 0);

    ////////////////////////////////////////////////////////////
    /// Allow switching between different loggers
    ///
    /// \param Pointer to a certain instance derivated from ILogger
    ///
    ////////////////////////////////////////////////////////////
    int AddKey(const SKey& key);



    ////////////////////////////////////////////////////////////
    /// Allow switching between different loggers
    ///
    /// \param Pointer to a certain instance derivated from ILogger
    ///
    ////////////////////////////////////////////////////////////
    template <class C>
    static C FlipVertically(C spline){
        C flipped_spline(spline.mKeys);
        for(std::vector<SKey>::size_type i = flipped_spline.mKeys.begin(); i < flipped_spline.mKeys.size();i++){
            flipped_spline.mKeys[i].v.x = 1-flipped_spline.mKeys[i].v.x;
            flipped_spline.mKeys[i].te.x = 1-flipped_spline.mKeys[i].te.x;
            flipped_spline.mKeys[i].ts.x = 1-flipped_spline.mKeys[i].ts.x;
        }
        return flipped_spline;
    }

    ////////////////////////////////////////////////////////////
    /// Allow switching between different loggers
    ///
    /// \param Pointer to a certain instance derivated from ILogger
    ///
    ////////////////////////////////////////////////////////////
    template <class C>
    static C FlipHorizontally(C spline){
        C flipped_spline(spline.mKeys);
        for(std::vector<SKey>::size_type i = flipped_spline.mKeys.begin(); i < flipped_spline.mKeys.size();i++){
            flipped_spline.mKeys[i].v.y = 1-flipped_spline.mKeys[i].v.y;
            flipped_spline.mKeys[i].te.y = 1-flipped_spline.mKeys[i].te.y;
            flipped_spline.mKeys[i].ts.y = 1-flipped_spline.mKeys[i].ts.y;
        }
        return flipped_spline;
    }


    //A supprimer certainement
    int LOD(int lod);


    ////////////////////////////////////////////////////////////
    /// Allow switching between different loggers
    ///
    /// \param Pointer to a certain instance derivated from ILogger
    ///
    ////////////////////////////////////////////////////////////
    virtual inline bool Export(const std::string& name) { return false; };
    virtual TVectorf Calculate(const float& t) const = 0;
    virtual ESplineType GetType() const = 0;

    ////////////////////////////////////////////////////////////
    /// Allow switching between different loggers
    ///
    /// \param Pointer to a certain instance derivated from ILogger
    ///
    ////////////////////////////////////////////////////////////
    ISpline();


    ISpline(const std::vector<SKey>& keys);

    virtual ~ISpline() {};


    std::vector<SKey> mKeys;
protected:
    int mLod;//level of definition
    TVectorf mScale;

};

FUSION_NAMESPACE_END


#endif
