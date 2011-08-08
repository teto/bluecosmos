/**
* \file enemy.h
* \brief
*/
#ifndef ENTITY_ENEMY_HPP
#define ENTITY_ENEMY_HPP

#include "IEntity.hpp"
#include "ship.hpp"
#include <o3/omonyom.hpp>
//#include <fusion/loaders.hpp>
//#include <fusion/maths.hpp>
//class ISpline;









class CResourceShip;



class CEnemy : public IEntity,
                public o3::CBattery {

protected:
    friend class CEntityManager;

    //Ancres + type rattaché a chaque ancre
    fus::ISpline* mTrajectory;//Can remain NULL TODO :CResourcePattern
    //CResourceShip* mShip;
public:
    //int mLife;

    //float mRange;
    //float mSpeed;



    float GetAngle();

    void OnOmonyomEvent(const o3::CAction& action);

    EEntityType GetType() const {return EEntityEnemy;}
    float GetRange() {return Get(o3::Range);}
    int GetLife() {return Get(o3::Life);};
    /// Operator = overloaded
    //CEnemy& operator=(const CEnemy& enemy);

    /// Constructor
    //CEnemy(const int& life,const fus::TVectorf& pos);

    /// Destructor
    ~CEnemy();

    void Init(const o3::CBatteryModel* batteryModel,const fus::TVectorf& pos);

    void AddDamage(const int& iDamage);
    void Update(const float& elapsed);
    void Draw();

};


#endif
