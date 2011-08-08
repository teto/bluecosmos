/**
\file
\author
**/
#ifndef FUSION_CBITSET_HPP_INCLUDED
#define FUSION_CBITSET_HPP_INCLUDED

#include <bitset>
#include <boost/logic/tribool.hpp>  // header only




namespace fus {

//typename DESCRIPTOR,
template<int SIZE>
class CBitset
{
    public:
        CBitset() {}
        virtual ~CBitset() {}

        bool
        SwitchBit(const int& bit,blo::tribool enable) {

            if(indeterminate(enable)){
                _bitset[bit].flip();
            }
            else {
                _bitset[bit] = enable;
            }

            return _bitset[bit];
        }
    protected:
    private:
        //std::array<CBindDescriptor,NPlayer::Count>;
        std::bitset<SIZE> _bitset;
};

}

#endif // FUSION_CBITSET_HPP_INCLUDED
