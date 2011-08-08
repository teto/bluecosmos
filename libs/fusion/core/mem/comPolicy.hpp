#ifndef RESOURCEPOLICY_H_INCLUDED
#define RESOURCEPOLICY_H_INCLUDED

namespace fus {

/*
Les fonctions de nos polices peuvent �tre statiques ou non, cela ne change en rien leur utilisation.
Pour les polices ne comportant aucune donn�e membre, il vaudra mieux tout mettre en static, ainsi on �conomisera un
 chou�a en performances (dans les fonctions statiques, l'objet implicite this n'est pas trimball� en interne).
*/
// Objets COM et ressources du moteur - comptage de r�f�rence intrusif
template <class T>
class CCOMPolicy {
public :

    // Clone la ressource
    static T* Clone(T* Ptr) {

        if (Ptr)
            Ptr->AddRef();
        return Ptr;
    }

    // G�re la lib�ration de la ressource
    static void Release(T* Ptr) {

        if (Ptr)
            Ptr->Release();
    }

    // Echange deux instances - aucune donn�e membre : ne fait rien
    static void Swap(CCOMPolicy&) {}
};

}

#endif // RESOURCEPOLICY_H_INCLUDED
