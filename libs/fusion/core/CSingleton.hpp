/**
* \file singleton.h
**/
#ifndef FUSION_SINGLETON_H
#define FUSION_SINGLETON_H

#include <fusion/fusion.hpp>
//#include <string>
// hack
//#include <iostream>

namespace fus {

template<typename CLASS>
class CSingleton {

private:
    static CLASS* mInstance;

    ///Interdit la copie
    CSingleton(CSingleton&);
    void operator =(CSingleton&);

protected:
    CSingleton(){};
    ~CSingleton(){};

public:
    // TODO a supprimer
    static CLASS* getInstance(){
        if(mInstance == 0){
            mInstance = new CLASS;
            //std::cout << "Creating new class " << std::endl;
        }
        return( mInstance);
    };

    static CLASS& instance(){
        if(mInstance == 0){
            mInstance = new CLASS;
        }
        return( *mInstance);
    };

    static void Destroy(){
        if(mInstance != 0){
            delete mInstance;
            mInstance = 0;
        }
    };
};

template <typename CLASS>
CLASS* CSingleton<CLASS>::mInstance = 0;

}

#endif
