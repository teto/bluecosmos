#ifndef REFPOLICY_H_INCLUDED
#define REFPOLICY_H_INCLUDED

namespace fus {


// Comptage de référence externe
template <class T>
class CRefCount {

public :

    // Constructeur par défaut
    CRefCount() : mCounter(new int(1)) {}

    // Clone la ressource
    T* Clone(T* Ptr) {

        ++*mCounter;
        return Ptr;
    }

    // Gère la libération de la ressource
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
