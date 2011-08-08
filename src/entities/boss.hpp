/**
* \file boss.hpp
* \brief
*/
#ifndef ENTITY_BOSS_HPP
#define ENTITY_BOSS_HPP

       //chargement des ancres
       /*
       SAnchor anchor;
       for(std::multimap<std::string,fus::TVectorf>::const_iterator i = batteries.begin();i != batteries.end();i++)
       {
            //temporaire a cause CreateBattery
            anchor.pos     =  pos + i->second;
            //vraie valeur de anchor.pos
            anchor.pos     = i->second;

            anchor.battery = o3::CRunner::GetInstance()->CreateBattery(i->first ,enemy);

            // si ca a bien ete cree
            if(anchor.battery){
                enemy->AttachAnchor(anchor);
                //anchor.battery->SetRelativPosition( anchor.pos.x,anchor.pos.y,anchor.pos.z );
            }
            else {
                fus::ILogger::Log(EWarning) << "No battery created !";
            }
       }*/
/*
class CAnchor : public o3::CBattery {
fus::TVectorf pos;
};

class CBoss {
    //Ancres + type rattaché a chaque ancre
    std::vector<SAnchor> mAnchors;
    // update les differents attaches
    void AttachAnchor(const SAnchor& anchor);
    // Met a jour les tirs des batteries
    /*for(std::vector<SAnchor>::size_type i = 0; i < mAnchors.size();i++){
        mAnchors[i].battery->Update(this);
    }
};
*/

#endif
