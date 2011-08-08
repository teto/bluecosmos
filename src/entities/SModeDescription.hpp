/**
* \file player.hpp
* \todo regourper tous les input pour les passer en parametre ? dans les update
*/
#ifndef SMODEDESCRIPTION_HPP
#define SMODEDESCRIPTION_HPP

#include <irrlicht.h>
#include <array>

class CPlayer;


class IMode {

public:
    virtual int getFrame() const = 0;
    //
};


//////////////////////////////////////////////
////   Describe fighter/gerwalk/battloid modes
//////////////////////////////////////////////
struct SModeDescription : public IMode

//class IMode
// TODO faire les accesseurs
{
public:
    enum ESpeed {

    Lateral = 0,
    Forward,
    DefaultForward,
    Backward,
    Roll,
    Yaw,
    SpeedsCount // Should remain last
    };

    // TODO rename
    //TVector3df
    irr::core::vector3df _cameraRecul;

protected:
    //friend class CPlayer;



    typedef std::array<float,SpeedsCount> TSpeedList;
    TSpeedList Speed;     // laterale,devant,derriere,rotation speed



    float YAngle;  //angles de tir,lock
    float ZAngle;  //angles de tir,lock
    //irr::core::vector3df AngleLimits;
    //float LockAngle;
    float Range;        // ptet la hitbox de l'appareil ?
    int Frame;
    irr::f32 AnimationSpeed;

    // TODO deplacer dans IPlayerMode
    typedef void (CPlayer::*TProcessMoveFunction)(void);

public:
    TProcessMoveFunction processMoveFunction;

    SModeDescription();

    //SModeDescription& operator=(const SModeDescription& mode);

    SModeDescription&
    setupSpeeds(const float& lateralSpeed,
                const float& forwardSpeed,const float& defaultForward,
                const float& backwardSpeed,const float& rollingSpeed,
                const float& yawSpeed);

    SModeDescription&
    setAngleBounds(const float& rollingLimit,const float& yawLimit);

    SModeDescription&
    setRange(const float& range);

    const float& getRange() const { return Range;};

    /**
    *
    */
    SModeDescription&
    setCameraRecul(const float x,const float& y,const float& z){
        _cameraRecul.set(0,y,z);
        return *this;
    }



    //const float getCruiseSpeed() const { return };

    SModeDescription&
    defineAnimation(const int& noFrame,const irr::f32& animationSpeed);

//    SModeDescription
//    inline getInterpolated(const float& progress,const SModeDescription& objective) const {
//
//        SModeDescription mode = *this;
//        mode.interpolate(progress,objective);
//        return mode;
//    }


//    static SModeDescription interpolate(const float& progress,const SModeDescription& start,const SModeDescription& objective);

    void interpolate(const float& progress,const SModeDescription& start,const SModeDescription& objective);

    SModeDescription& interpolate(const float& progress,const SModeDescription& );


    const float& getYawLimit() const {
        return YAngle;
    }

    const float& getSpeed(const ESpeed& speedId) const {
        return this->Speed[speedId];
    }

    // A deplacer ?
    inline int getFrame() const { return Frame;};

    void getAngleLimits(float& yAngle,float& zAngle) const {

        yAngle = this->YAngle;
        zAngle = this->ZAngle;
    };

    void printMode() const;

};

//
//
//class IPlayerMode : public SModeDescription
//{
//  boost::mem_ref
//      typedef void (CPlayer::*TProcessMoveFunction)(void);
//};


#endif
