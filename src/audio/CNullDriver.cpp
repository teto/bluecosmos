#include "CNullDriver.hpp"
#include "SAudioParameters.hpp"

#include <fusion/logging/ILogger.hpp>

namespace audio {

CNullDriver::CNullDriver()
{

}


ISound*
CNullDriver::getSound(const std::string& filename) {
    return 0;
}




void
CNullDriver::update()
{

}


bool
CNullDriver::init(const SAudioParameters&)
{

    return true;
}

}
