/**
 * \file entity_enemy.cpp
 * \todo gerer courbes de bézier pour definir un mouvement
*/

#include "enemy.hpp"
#include "entity_manager.hpp"
#include <o3/omonyom.hpp>

/*
// Surcharge de l'operateur =
CEnemy& CEnemy::operator=(const CEnemy& enemy){


    mLife    = enemy.GetLife();
    //CResourcePattern* mTrajectory;//Can remain NULL
    //mProgression = ;
    mShip = enemy.mShip;
    mAnchors = enemy.mAnchors;
    return *this;
}

void
CEnemy::AttachAnchor(const SAnchor& anchor){
    mAnchors.push_back(anchor);
}
*/



float
CEnemy::GetAngle() {
    return Get(o3::Angle);
}



void
CEnemy::Init(const o3::CBatteryModel* batteryModel,const fus::TVectorf& pos){

    CBattery::Init(batteryModel,0);

// Chercher mModel depuis les infos de batteryModel
    //mModel =
    //mLife    = life;
    mPosition     = pos;
    mLocked  = 0;

}


CEnemy::~CEnemy(){
}


//! Add damage
void
CEnemy::AddDamage(const int& iDamage){

    Get(o3::Life) -= iDamage;
}


//! Update position and shoot if timer elapsed
void
CEnemy::Update(const float& elapsed){

// TODO remplacer cette update par celui de la batterie associee !
    if(!mTrajectory){
        mPosition.y -= Get(o3::Speed) * elapsed;
    }
    else{
            //TODO: progression through the curve
            //mProgression += mShip->mSpeed
    }

}


void
CEnemy::OnOmonyomEvent(const o3::CAction& action) {


    switch (action.Type){

    	case o3::CAction::StraightType:
    	//o3::CBattery(*this)mPosition
            CEntityManager::GetInstance()->CreateBullet(this,action.StraightShoot.Id,this->Get(o3::Angle));
    		break;

    	default:
    		break;
    };


}


//! Draw
void
CEnemy::Draw(){

    //faire des glrotate etc...

    mModel->Draw();

    /// \todo dessiner moteur
    /*
    for(std::vector<SBooster>::iterator i = mBoosters.begin();i != mBoosters.end();i++){
        //position = mShip->GetPos()+i->pos;
        i->system.Draw(position);
    }
    */

}

