/**
\file
\author
**/
#ifndef CINTRUSIVEPOOL_HPP
#define CINTRUSIVEPOOL_HPP

//#include "../intrusive.hpp"

//namespace N
enum EArray {
Pool,
Active
};


template<class T>
class CList {



};


/*
could put a virtual function create / configure ?

*/
template<class HOOK,class ELEMENT>
class CIntrusivePool
{
public:
    typedef typename bin::slist< ELEMENT, bin::base_hook< HOOK > , bin::linear<true>, bin::cache_last<true>  > TElementList;

private:
protected:
//link_mode<auto_unlink>
//slist_bin::link_mode<bin::auto_unlink>
    //typedef bin::slist_base_hook< T > TBaseHook;
    //typedef bin::slist_member_hook< T > TMemberHook;
    //typedef bin::base_hook<T, bin::link_mode<bin::auto_unlink> > Hook;
    // cache_last enables quick push_back function
    // linear prevents cyclic

    // si cache last est active alors on ne peut pas utiliser de auto_unlink !


    static TElementList _pool;

public:

    TElementList _activeElements;

    /** Default constructor */
//    CIntrusivePool();
//    /** Default destructor */
//    virtual ~CIntrusivePool();
    typedef typename TElementList::iterator iterator;

//
//    TElementIterator begin() { return TElementIterator(_elements[Active].begin());};
//    TElementIterator end() { return TElementIterator(_elements[Active].end());};

    //getFreeElement

//    inline begin() {
//        return _activeElements.begin();
//    }

    //addElement
    // If == au front


    ELEMENT*
    getFreeElement(){

        // if no pool, then the user will have to eventually allocate one
        if(_pool.empty() ){
            return false;
        }

        ELEMENT* element = &_pool.front();
        _pool.pop_front();

        return element;
    }

//    T*
// on part du principe qu'ajouter a cette liste va retirer de l'autre ?
    void
    addElement(ELEMENT& element){

        // will remove it from current list I hope ?

        //BOOST_ASSERT(!element.is_linked());

        _activeElements.push_back(element);

//        return element;
    }


    std::size_t getPoolSize() const {
        return _pool.size();
    }

    std::size_t getActiveElementsSize() const {
        return _activeElements.size();
    }


    /* T*
    addElement(){

        //T* element = getCachedElement();
        T* element = 0;

        // if still in stock
        if(_pool.empty()){
            element = new T();
//            if(!onElementCreation(element)){
//                delete element;
//                return 0;
//            }

        }
        else {
            // BUG ICI non ? faut le supprimer de la liste correctement sinon ca foire
            // et eviter que la liste soit cyclique
            //pop_front renvoie une const_reference
            element = &_pool.front();
            _pool.pop_front();
        }

        _activeElements.push_back(*element);

        return element;
    }*/

    //virtual bool onElementCreation(T* element) = 0;
//    addActiveElement(){
//    }
//    T* getCachedElement(){
//        // if still in stock
//        // utiliser size sinon
//        if(_elements[Pool].empty()){
//            return 0;
//        }
//        else {
//
//            // BUG ICI non ? faut le supprimer de la liste correctement sinon ca foire
//            // et eviter que la liste soit cyclique
//            element = &_elements[Pool].front();
//            _elements[Pool].pop_front();
//        }
//    }

    //TElementList::iterator
    void
    removeElement(ELEMENT& element){
/* when using auto_unlink_hook
           void unlink()     {  auto_unlink_hook::unlink();  }
   bool is_linked()  {  return auto_unlink_hook::is_linked();  }
   */
        //element.unlink();
        //_pool.push_back(element);

        iterator it = _activeElements.iterator_to(element);
        if(it != _activeElements.end()){
            removeElement( it );
        }
        else {
            return;
        }
        // Todo try to use the static version
//        iterator i =
//        _activeElements.erase (
//            _activeElements.iterator_to(element)
//        );
//        _activeElements.erase
//
//        _pool.push_front(element);
        //return i;
    }


    iterator
    removeElement(iterator& it){

        // Todo try to use the static version
        //it =
        ELEMENT& element = *it;
        iterator temp = _activeElements.erase (
            //_activeElements.iterator_to(element)
            it
        );

        _pool.push_front(element);
        return temp;
    }


    void clearPool(){

        // Destroy le pool
    }

};


template<class HOOK,class ELEMENT>
typename CIntrusivePool<HOOK,ELEMENT>::TElementList

CIntrusivePool<HOOK,ELEMENT>::_pool;


#endif // CINTRUSIVEPOOL_H
