#ifndef CBITSET_HPP_INCLUDED
#define CBITSET_HPP_INCLUDED

#include <boost/logic/tribool.hpp>  // header only
#include <irrlicht.h>

namespace blo = boost::logic;

void switchBit(bool& bit,const blo::tribool& enable);

void decal(irr::core::recti& pos,const int& x,const int& y);
void yDecal(irr::core::recti& pos,const int& y);
void xDecal(irr::core::recti& pos,const int& x);
//void decal(irr::core::recti& pos,const irr::core::position2di&);

#endif // CBITSET_HPP_INCLUDED
