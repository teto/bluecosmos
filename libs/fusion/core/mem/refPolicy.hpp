#ifndef REFPOLICY_H_INCLUDED
#define REFPOLICY_H_INCLUDED

namespace fus {


// Comptage de r�f�rence externe
template <class T>
class CRefCount {

public :

    // Constructeur par d�faut
    CRefCount() : mCounter(new int(1)) {}

    // Clone la ressource
    T* Clone(T* Ptr) {

        ++*mCounter;
        return Ptr;
    }

    // G�re la lib�ration de la ressource
    void Release(T* Ptr) {

        if (--*mCounter == 0) {
            delete mCounter;
            delete Ptr;
        }
    }

    // Echange deux instances
    void Swap(CRefCount& RefCount) {
        std::swap(RefCount.mCounter, mCounter);
    }

private :
    int* mCounter;
};

}

#endif // REFPOLICY_H_INCLUDED
