/**
* \file level.h
*/
#ifndef LEVEL_H
#define LEVEL_H

#include "../config.h"
#include "enemy.h"
//#include "../utilities/xml.h"
#include "../utilities/skybox.h"
#include "../core/singleton.h"
#include "../o3/omonyom.h"
#include <SFML/System.hpp>



namespace fus{
    class ISpline;
    class CSound;
}





class CLevelManager : public fus::CSingleton<CLevelManager>{

public:
    CLevelManager();
    ~CLevelManager();

    void CreateExplosion();
    bool Update();
    void Draw();
    int GetLevelNumber() const { return mLevelNumber;};


protected:


    friend class fus::CSingleton<CLevelManager>;

    int mLevelNumber;



};

#endif
