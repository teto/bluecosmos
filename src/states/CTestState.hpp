#ifndef TESTSTATE_H
#define TESTSTATE_H

#include "state.h"
#include "../loaders/md5loader/md5_object.h"
#include <irrlicht.h>
#include <deque>//first in first out ( FIFO )





class CTestState : public IGameState,public fus::CSingleton<CTestState> {

public:

	bool Init(CGameEngine *game);
	void CleanUp();
	bool OnEvent(const irr::SEvent&);
	void Update(CGameEngine *game);
	void Draw(CGameEngine *game);



protected:



    friend class fus::CSingleton<CTestState>;
};



#endif
