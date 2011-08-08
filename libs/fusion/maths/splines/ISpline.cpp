/**
* \file spline.cpp
*
*/
#include <fusion/splines.hpp>
#include <fusion/fusion.hpp>
#include <fusion/config.hpp>

FUSION_NAMESPACE_BEGIN

/*
Define SKey constructors
*/
SKey::SKey(const TVectorf& Point,const TVectorf& Tangent,const float& Time) : v(Point),te(Tangent),time(Time) {
    //te += Tangent;
}

SKey::SKey() : time(0) {
}


void
SKey::Scale(float w,float h,float d){
v.x  /= w;
te.x /= w;
ts.x /= w;
v.y  /= h;
te.y /= h;
ts.y /= h;
v.z  /= d;
te.z /= d;
ts.z /= d;
}


/*
*/
ISpline::ISpline() : mLod(_FUSION_SPLINE_DEFAULT_LOD) {

}

ISpline::ISpline(const std::vector<SKey>& keys) : mLod(_FUSION_SPLINE_DEFAULT_LOD) {
    mKeys = keys;
}

/*
bool Export(const std::string& name){
    return false;
}*/

int ISpline::AddKey(const TVectorf& v,const TVectorf& t,const float& time){
    SKey key(v,t,time);
    return AddKey(key);
}

int ISpline::AddKey(const SKey& key){
    mKeys.push_back(key);
    return (mKeys.size()-1);
}

/// Set Level Of Detail
int ISpline::LOD(int lod){
    if(lod > 3)
        mLod = lod;
    return mLod;
}

FUSION_NAMESPACE_END
