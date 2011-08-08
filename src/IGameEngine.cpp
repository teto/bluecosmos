/**
* \file GameEngine.cpp
*
*/
#include "IGameEngine.hpp"

#include "config.hpp"
#include <fusion/core/CStringBuilder.hpp>
#include "utils/CBitSet.hpp"




bool
IGameEngine::SwitchBit(const NBit::EId& bit,blo::tribool enable) {

//     switchBit( mBitSet[bit]);
//    return mBitSet[bit];

    if(indeterminate(enable)){

        mBitSet.flip(bit);// = !mBitSet[bit];
    }
    else {
        mBitSet.set(bit,enable);
    }

    return mBitSet[bit];
}

// Function Init()
IGameEngine::IGameEngine() :
_internalState(NEngineState::Uninitialized)
   // mRenderingMode(Fill)
{


}


IGameEngine::~IGameEngine(){

}

