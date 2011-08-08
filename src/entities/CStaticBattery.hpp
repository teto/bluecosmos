/**
* \file bullet.h
* Fichier dans dossier "engine"

* bullet
**/
#ifndef BC_ENTITY_BULLET_HPP
#define BC_ENTITY_BULLET_HPP

//#include "../utils/IClock.hpp"
#include "../utils/TClock.hpp"
#include <irrlicht.h>
#include <array>
#include <list>
#include <luabind/lua_include.hpp>
//#include <luabind/operator.hpp>
#include "../def.hpp"




namespace NParameters {
enum EId {
Spinning = 0,
Angle,
Speed,
Damage,
Range,
KillAllChildren,
OrientationSpeed,
Life,
LateralSpeed,
ForwardSpeed,
Count       // doit rester en dernier
};
}

class CMissile;
class CBullet;
class CStaticBattery;
class CGraphicalLevel;
class CFleet;


float normalizeAngle(const float& angle);

void getVectorFromAngle(const float& angle,TVector3df& vectorToRotate);

inline
TVector3df getPlayerForwardVector(){
    return TVector3df (0.f,0.f,1.f);
}

inline
TVector3df getEnemyForwardVector(){
    return TVector3df (0.f,0.f, -1.f);
}



/// Describe a bullet
// TODO faire deriver de luabind::wrap_base
class CStaticBattery
{
//private:
public:
    irr::scene::IAnimatedMeshSceneNode* _node;

    CStaticBattery* _target;

    float _range;
    int _life;
    int _bonus;
    bool _withinScreen;     // if out of screen add a timer, if recome into screen, reset timer
    int _damageInflictedOnCollision;
    //TTimer _timer;
    int _numberOfFramesSinceOutOfScreen;
    CFleet* _fleet;

    float _rotationSpeed;

    // CMissile
    typedef std::list<CStaticBattery*> TMissileList;
    TMissileList _trackingMissiles;

    TVector3df _previousPos;      //!< Entity's 3D position, useful to compute collisions


public:




    void setTarget(CStaticBattery* );

    TVector3df computeLastFrameSpeedVector() const { return (this->getPosition() - _previousPos); };
    TVector3df predictPositionIn(const TTimeUnit&) const ;


    void setWithinScreen(const bool& value);

    //void setMesh(irr::scene::IAnimatedMesh* mesh);
    // Il faudrait
    void setMesh(const char* pathToModel);

    CFleet* getFleet() { return _fleet; };
    void setFleet(CFleet* );

    /**
    **/
    bool checkCollision(CStaticBattery*);

    void addTrackingBattery(CStaticBattery*);
    void removeTrackingBattery(CStaticBattery*);

    virtual const NEntityType::EId getType() const { return NEntityType::Battery; } ;



    //bool operator==(const CStaticBattery&) const;

    void setup(
               //const char* model,
               const float& range,
               const int& life,
               const int& damage,
               const int& bonus
               );



    // Range setter/getter
    //void setRange(const float& range) { _range = range;};
    virtual float getRange() const { return _range;};

    // Life
    //void setLife(const int& life) { _life = life;};
    virtual int getRemainingLife() const { return _life;};

    // Bonus
    //void setBonus(const int& bonus) { _bonus = bonus;};
    virtual float getBonus() const { return _bonus;};


    void setRotationSpeed(const float& rotationSpeed) {
        _rotationSpeed = rotationSpeed;
    };


    //const bool& getCollision() const { return _collision;};

    /**
    Every function about position
    **/
    const int& getDamage() const { return _damageInflictedOnCollision;};
    void setPosition(const float& x,const float& y,const float& z) { setPosition(TVector3df (x,y,z)); }
    void setPosition(const TVector3df& );
    void exportPositionToLua(lua_State* L) const;
    const TVector3df&  getPosition() const { return _node->getPosition(); };
    void translate(const float&,const float&,const float&);

    /**
    Every function about rotation
    **/
    const TVector3df&  getRotation() const { return _node->getRotation(); };
    TVector3df computeAnglesToFaceBattery(CStaticBattery* target) const;
    void setRotation( const TVector3df& rotation );
    void updateRotation();

    //bool onShoot(const o3::CShooting& id);

    void addDamage(const int& damage);


    /**
    virtual functions
    **/
    //virtual void updateRotation();
    //virtual void updatePosition();
    virtual void onTimeoutDisparition();
    virtual void onDeath();





    CStaticBattery();
    ~CStaticBattery();



//CStaticBattery*
    CBullet*
    shootBullet(const char* model,const float& deviation);


    //void reset();


    /**
    * \param Time elapsed
    * \return True if should die
    **/
    virtual bool update(const TTimer::TimeType&);

    bool outOfScreenTimeout() const;

    virtual void kill();


    /// Single linked list
    CStaticBattery* _next;
    CStaticBattery* _previous;


    virtual void onCollision(CStaticBattery*);

    friend std::ostream& operator<<(std::ostream&, const CStaticBattery& );

protected:


private:


};



#endif
