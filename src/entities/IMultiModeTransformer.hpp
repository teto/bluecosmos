/**
\file transforming.hpp
\brief
todo le rendre transformable

*/
#ifndef IMULTIMODETRANSFORMER_HPP
#define IMULTIMODETRANSFORMER_HPP

//#include "IEntity.hpp"
#include <map>
#include <list>
#include <fusion/macros.hpp>
#include <array>
#include <irrlicht.h>
#include <vector>
#include <fusion/logging/ILogger.hpp>
//#include "SModeDescription.hpp"
#include "ITransformer.hpp"
#include "../def.hpp"




class IMode;



typedef IMode* TMode;

using namespace irr;

/**

en gros g un tableau qui contient tous mes modes avec chacun un ID


Dans cette classe IMultiModeTransformer, j'enregistre juste les ID


**/


// passer en parametre les noms des differents boosters, du mesh, ces caracteristiques
//template<class MODE>
// /TODO renommer en IModeBasedTransformer ?
class IMultiModeTransformer :
    public ITransformer,
    public SModeDescription
{

public:
    typedef std::array<SModeDescription,NWalkyrieModes::Count> TAvailableModes;
    static TAvailableModes _availablesModes;

protected:
    bool _cyclic;



    void transformIntoLastMode();
    void transformIntoFirstMode();

// TODO remplacer par des std::size_t
    bool transformInto(const TModeId&);


    int _currentMode;
    int _targetedMode;


public:

    static void initialize();
    void OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* node);

    bool transformIntoNextMode();
    bool transformIntoPreviousMode();
    //getCurrentMode();


    typedef std::vector<TModeId> TCurrentModes;


    // Enregistre les id des modes qu'on peut utiliser
    TCurrentModes _activeSpecs;







    void enableCyclicTransformation(const bool& enable){
        _cyclic = enable;
    }

    const bool& isCyclic() const { return _cyclic; }

    //typedef TAvailableModes::iterator TMode;


    void forceMode(const TModeId& mode);

    void update();

//IMode* enforcedMode
    //IMultiModeTransformer(irr::scene::IAnimatedMeshSceneNode* node,const TModeId& id);
    IMultiModeTransformer(irr::scene::IAnimatedMeshSceneNode* node,const TModeId& id);
    void load(irr::scene::IAnimatedMeshSceneNode* node,const TModeId& id);

    ~IMultiModeTransformer();

//TODO check why error
    //virtual void onTransformationEnd();
    //virtual void onTransformationEnd() = 0;

    //virtual IMode* getModeFromModeId(const TModeId&) { return 0;};
    // todo passer en static
    static SModeDescription& getModeFromModeId(const TModeId&);

public:
    void clearModes( const TModeId& id );
    // TODO renommer en addMode
    bool allowMode(const TModeId& mode);
//    std::vector<>
};

//
//class ITransformerAdaptor {
// public:
//      virtual void
//};

//#include "transforming.inl"

#endif
