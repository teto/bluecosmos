#include "CMissile.hpp"
#include <fusion/fusion.hpp>


CMissile::CMissile()
//: _target(0)CStaticBattery
{
}



bool
CMissile::setup( const char* model, CFleet* fleet, const TVector3df& position,const TVector3df& forward) {

    //
    _forward = forward;
    return true;
    //CStaticBattery::setup(model, fleet, position );
}



/**
getHorizontalAngle()
rotationToDirection
**/
bool
CMissile::update(const TTimer::TimeType& elapsedTime){

    /// check if target
    if(!_target){
        //updatePosition( this->getPosition() + _forward);
        setPosition( this->getPosition() + _forward);
        return CStaticBattery::update(elapsedTime);
    }

  //  TVector3df
    const float maxDelta = 5.f;

//    _forward.getHorizontalAngle();
//    TVector3df rot(90,0,0);
//    this->_node->setRotation( rot );
        //distance au carre
        const TTimeUnit delay = 0.10f;
        const TVector3df targetPosition = _target->predictPositionIn( delay );

//
//        _INFO << "target speed vector  " << _target->computeLastFrameSpeedVector();
//        _INFO << "target previous pos" << _target->_previousPos;
//        _INFO << "target actual pos" << _target->getPosition();

        //const TVector3df toTarget(_target->_node->getAbsolutePosition() - this->_node->getAbsolutePosition());
        const TVector3df toTarget( targetPosition - this->getPosition() );

        //_INFO << "missile aiming for " << targetPosition;
        TVector3df horizontalAngle = toTarget.getHorizontalAngle();
        // HACK TO suppress once model finished
        horizontalAngle.X = 0;
        // clamp values
    //    _INFO << "rot before clamp : " << requiredRotation.Y ;
//    _INFO << "Current rotation: " << getRotation() ;
//    _INFO << "horizontalAngle: " << horizontalAngle.Y ;
    if(horizontalAngle.Y > 180.f){

        horizontalAngle.Y -= 360.f;
    }


/*
        TVector3df rotationDelta =  horizontalAngle - this->getRotation() ;
//        _INFO << "rotation delta: " << rotationDelta.Y ;

        rotationDelta.Y = irr::core::clamp(rotationDelta.Y, - maxDelta ,  maxDelta);
  //      _INFO << "rotation delta after clamp : " << rotationDelta.Y;

        setRotation(rotationDelta + getRotation() );

        rotationDelta.X = 0;

        //rotationToDirection (const vector3d< T > &forwards=vector3d< T >(0, 0, 1)) const
        _forward = getRotation().rotationToDirection ();

        //const float speed =  1.2f- rotationDelta.Y/maxDelta;
        const float speed =  1.f;
        _forward *= speed;

         setPosition( this->getPosition() + _forward);
         */
    return CStaticBattery::update(elapsedTime);
}



#if 0
/**
 * @brief guided missile steering helper function
 *
 * @param missilePosition - current absolute position of the missile
 * @param missileRotation - current absolute rotation of the missile
 * @param targetPosition  - current absolute target position
 * @param oversteer       - oversteer factor in degrees
 *
 * @return targetPitchRoll - delta pitch (x) and delta roll (z) values to the target
 *
 *******************************************************************************************************/
 //http://irrlicht.sourceforge.net/phpBB2/viewtopic.php?t=11333
core::vector3df getToTargetPitchRoll( core::vector3df& missilePosition, core::vector3df& missileRotation, core::vector3df& targetPosition, float oversteer = 0.0f )
{
  core::matrix4 rotMatrix, invRotMatrix;
  rotMatrix.setRotationDegrees( missileRotation );
  core::vector3df targetPitchRoll( 0.0f, 0.0f, 0.0f );
  // get the current missile direction
  core::vector3df currentMissileTargetVec( 0.0f, 0.0f, 1.0f );

  // get the vector to the target (from the missile position)
  core::vector3df missileTargetVec = ( targetPosition - missilePosition ).normalize();
  // invert the rotation matrix to transform the target vector into the missile's local space
  rotMatrix.getInverse( invRotMatrix );
  // transform the target vector into missile's local space
  invRotMatrix.rotateVect( missileTargetVec );
  // compute the roll angle to the target
  float deltaRoll = atan2f( missileTargetVec.Y, missileTargetVec.X ) * core::RADTODEG - 90.0f;
  if( deltaRoll < 0.0f )
    deltaRoll += 360.0f;
  if( deltaRoll >= 360.0f )
    deltaRoll -= 360.0f;

  if( deltaRoll > 180.0f )
    deltaRoll -= 360.0f;

  // compute the pitch angle to the target
  float deltaPitch = acosf( currentMissileTargetVec.dotProduct( missileTargetVec ) )
    * core::RADTODEG + oversteer;

  targetPitchRoll.X = -deltaPitch;
  targetPitchRoll.Z = deltaRoll;

  return targetPitchRoll;
}

#endif



void
CMissile::kill(){



    CStaticBattery::kill();
}



