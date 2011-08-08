#ifndef _FUSION_ILOGGER_HPP_INCLUDED
#define _FUSION_ILOGGER_HPP_INCLUDED

#include <fusion/logging/Logger.hpp>


template <class T>
fus::Logger&
operator <<(fus::Logger& logger,const irr::core::vector3d<T>& v){

    logger.Log(fus::NLogLevel::Append) << "Irrlicht Vector: " << v.X << "/" << v.Y << "/" << v.Z;
    return logger;
}



template <class T,class U>
fus::Logger&
operator <<(fus::Logger& logger,const std::pair < T, U >& p ){

    logger.Log(fus::NLogLevel::Append) << "std::pair [" << p.first << "/" << p.second << "]";
    return logger;
}





template <class T>
fus::Logger&
operator <<(fus::Logger& logger,const irr::core::rect<T>& rect){

    logger.Log(fus::NLogLevel::Append) << "Irrlicht Rect: X/Y: " << rect.UpperLeftCorner.X << "/" << rect.UpperLeftCorner.Y
                        << " Width/Height" << rect.getWidth() << "/" << rect.getHeight();
    return logger;
}

#endif
