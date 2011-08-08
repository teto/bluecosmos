#ifndef CINTRUSIVELIST_HPP
#define CINTRUSIVELIST_HPP



template<class C>
class CHook {
    CHook() : _next(0), _previous(0) {

    }
//
//    unlink(){
//
//    }
//
    C* _next;
    C* _previous;
};

class CStaticBattery;

//template<class C>
class CIntrusiveList
{
    public:
        CIntrusiveList();
        virtual ~CIntrusiveList();

        //void push_back(CStaticBattery* );
        void push_front(CStaticBattery* );
        CStaticBattery* pop_front();

        void remove(CStaticBattery*);

        void print();

        bool empty() const {
            return (_root == 0);
        }

        CStaticBattery* front() { return _root;};

    /// Pouvoir passer un clear() & destroy
        void clear();

    protected:
        int _size;
        CStaticBattery* _root;

    private:
};

#endif // CINTRUSIVELIST_HPP
