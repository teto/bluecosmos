/**
\file
\author
**/

#ifndef COpenAlDriver_HPP_INCLUDED
#define COpenAlDriver_HPP_INCLUDED


#include "IAudioDriver.hpp"
#include <list>
#include <map>
#include <vector>
//#include <fusion/core/CSingleton.hpp>

namespace audio {


class COpenAlDriver :
        public IAudioDriver
{

private:



public:

    COpenAlDriver();
    ~COpenAlDriver();

    bool init(const SAudioParameters&);


	void update();

    ISound* getSound(const char* filename);


    void collectGarbage();

};

}

#endif // CEXPLOSIONS_HPP_INCLUDED
