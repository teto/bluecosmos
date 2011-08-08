/**
* \file
* http://www.programmationworld.com/php/cours/index.php?page=cours&id_cours=64&affichage=2
*/
#include "CSplineBezier.hpp"
#include <fusion/core.hpp>
#include <fusion/splines.hpp>
//#include <qwxml/qwxml.hpp>


FUSION_NAMESPACE_BEGIN

CSplineBezier::CSplineBezier(){

}

CSplineBezier::~CSplineBezier(){

}

ESplineType
CSplineBezier::GetType() const{
    return ESplineBezier;
}


TVectorf
CSplineBezier::Calculate(const float& t) const {

    fus::TVectorf v;

    if(mKeys.size() < 4)
        return v;

	float b[4],T;
	T = 1.f - t;
	b[0] = t*t*t;
	b[1] = 3*t*t*T;
	b[2] = 3*t*T*T;
	b[3] = T*T*T;

    v = mKeys[0].v*b[0]+mKeys[1].v*b[1]+mKeys[2].v*b[2]+mKeys[3].v*b[3];
    return v;
}

/*
format de fichier xml:
<spline type="bezier">
    <key x="" y="" z="" time="" />
    <key>
    ...
</spline>

Pour type catmull,mettre les tangentes internes/externes + ...
*/
bool
CSplineBezier::Export(const std::string& name){

/*
//autoriser le lancement d'exceptions
    static int number = 0;
    try {

        qwxml::CXmlDocument doc;
        TiXmlElement* elem = doc.CreateRootElement("spline");
        doc.SetAttribute(elem,"type","bezier");
        TiXmlElement* key = NULL;
        for(std::vector<SKey>::size_type i = 0; i < mKeys.size();i++){
            key = doc.AddElement(elem,"key");
            doc.SetAttribute(key,"x",mKeys[i].v.x );
            doc.SetAttribute(key,"y",mKeys[i].v.y );
            doc.SetAttribute(key,"z",0);//mKeys[i].v.z);
            doc.SetAttribute(key,"time",mKeys[i].time);
        }
        doc.Save(CStringBuilder("pattern")(number)(".pxml"));
        number++;
    }
    catch(SLoadingException &e ){
        // a traiter
        return false;
    }
    catch(...){
        return false;
    }
*/


    return true;
}

void
CSplineBezier::Update(){
/*
    for(){
        mBase[0] = 3*2*1/();
        mBase[0] = 3*2*1/();
        mBase[0] = 3*2*1/();
        mBase[0] = 3*2*1/();
    }*/
}

FUSION_NAMESPACE_END
