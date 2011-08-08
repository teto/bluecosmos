#include "CBitSet.hpp"


void
switchBit(bool& bit,const blo::tribool& enable) {

    if(indeterminate(enable)){

        //mBitSet.flip(bit);// = !mBitSet[bit];
        bit = !bit;
    }
    else {
        bit = enable;
        //mBitSet.set(bit,enable);
    }

    //return bit ;//mBitSet[bit];
}


void decal(irr::core::recti& pos,const int& x,const int& y) {
//driverName
    pos += irr::core::position2di(x,y);
}

void yDecal(irr::core::recti& pos,const int& y) {
    decal(pos,0,y + pos.getHeight() );
}

void xDecal(irr::core::recti& pos,const int& x) {
    decal(pos,x + pos.getWidth() , 0);
}


//void decal(irr::core::recti& pos,const irr::core::position2di& vec) {
//    //decal(pos,x + pos.getWidth() , 0);
//    pos += vec;
//}
