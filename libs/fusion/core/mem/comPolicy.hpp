#ifndef RESOURCEPOLICY_H_INCLUDED
#define RESOURCEPOLICY_H_INCLUDED

namespace fus {

/*
Les fonctions de nos polices peuvent être statiques ou non, cela ne change en rien leur utilisation.
Pour les polices ne comportant aucune donnée membre, il vaudra mieux tout mettre en static, ainsi on économisera un
 chouïa en performances (dans les fonctions statiques, l'objet implicite this n'est pas trimballé en interne).
*/
// Objets COM et ressources du moteur - comptage de référence intrusif
template <class T>
class CCOMPolicy {
public :

    // Clone la ressource
    static T* Clone(T* Ptr) {

        if (Ptr)
            Ptr->AddRef();
        return Ptr;
    }

    // Gère la libération de la ressource
    static void Release(T* Ptr) {

        if (Ptr)
            Ptr->Release();
    }

    // Echange deux instances - aucune donnée membre : ne fait rien
    static void Swap(CCOMPolicy&) {}
};

}

#endif // RESOURCEPOLICY_H_INCLUDED
