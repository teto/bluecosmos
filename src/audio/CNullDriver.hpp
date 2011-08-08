/**
\file
\author
**/
#ifndef CNullDriver_HPP_INCLUDED
#define CNullDriver_HPP_INCLUDED


#include "IAudioDriver.hpp"
#include <boost/shared_ptr.hpp>
#include <fusion/core/CSingleton.hpp>

namespace audio {


class CSound;




class CNullDriver :
        public IAudioDriver
{


public:

    CNullDriver();
    //~CNullDriver();

    bool init(const SAudioParameters&);
	void update();

    ISound* getSound(const std::string& filename);


    //void collectGarbage();

};

}

#endif // CEXPLOSIONS_HPP_INCLUDED
