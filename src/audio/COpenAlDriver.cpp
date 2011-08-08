#include "COpenAlDriver.hpp"
#include "ISound.hpp"
#include "SAudioParameters.hpp"

//#include <fusion/logging/ILogger.hpp>
#include <fusion/fusion.hpp>

namespace audio {


COpenAlDriver::COpenAlDriver()
{
    //ctor

}


ISound*
COpenAlDriver::getSound(const char* filename) {
    return 0;
}



void
COpenAlDriver::collectGarbage() {

}




COpenAlDriver::~COpenAlDriver()
{

}



void
COpenAlDriver::update()
{

}




//const int& maxChannelsNumber
bool
COpenAlDriver::init(const SAudioParameters&)
{
    return true;

}

}
