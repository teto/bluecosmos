/**
* \file intro.h
*/

#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include "IGameState.hpp"
#include <irrlicht.h>
#include <boost/scoped_ptr.hpp>

#include "../utils/IClock.hpp"

class CFadingImage;


class CTransitionState :
    public IGameState<NStateId::Score,true>
{

public:
// overallTime in millisecond
//irr::video::ITexture* texture,const irr::u32& overallTime = 2000
    CTransitionState(const std::string& , const std::string& );
    ~CTransitionState();
	void init();

    //void ChangeState();


	void Update();
	void Draw();
    bool OnEvent(const irr::SEvent& event);
    //void CleanUp();

protected:

    boost::scoped_ptr<CFadingImage> _img;
    std::string _filename;
};

#endif
