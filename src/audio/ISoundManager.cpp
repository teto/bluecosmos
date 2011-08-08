#include "ISoundManager.hpp"
#include "IAudioDriver.hpp"
#include "CNullDriver.hpp"
//#include "CFModexDriver.hpp"
#include <fusion/logging/ILogger.hpp>

namespace audio {


/// TODO this funcition is merely a hack to be able to compile
//ISoundManager*
IAudioDriver*
createSoundManager(const SAudioParameters& parameters) {

    //IAudioDriver* driver = new CFModExDriver();
    IAudioDriver* driver = new CNullDriver();

    return driver;
}

//
//    ISoundManager::ISoundManager() : _driver(0)
//    {
//    }

}
