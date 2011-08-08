/**
\file IGameConfig.h

Refaire pour l'adapter avec le systeme de boost::program_options
*/
#ifndef IGameConfig_HPP
#define IGameConfig_HPP


#include <map>
#include <string>
#include <bitset>
#include <irrlicht.h>
#include <boost/array.hpp>  // header only
//#include <irrlicht.h>  // header only
#include "events/CBindDescriptor.hpp"
#include "events/CBindCollection.hpp"
#include "def.hpp"
#include <boost/logic/tribool.hpp>  // header only

namespace blo = boost::logic;

class CConfigManager;


typedef CBindCollection<NPlayerInput::Count> TMappingSet;



    //NPlayer::TMappings mKeyMaps;
class CConfigManager
{

private:
public:


//    static TBiMap _videoDrivers;
//    static void getAvailableVideoDriverList(std::vector<std::wstring>& list)
    void enableFullscreen(const blo::tribool& value);
    void enableVsync(const blo::tribool& value);
    //void enableShaders(const blo::tribool& value);

    void setAntialiasingLevel(const int& value);
    void getIrrlichtParameters( irr::SIrrlichtCreationParameters& parameters) const ;

    std::wstring _videoDriver;
    std::wstring _audioDriver;
    int _antialiasing;
    bool _fullscreen;
    bool _vsync;

    //typedef
    typedef std::map<std::wstring,bool> TShadersList;
    TShadersList _shaders;

    bool _enableDialogs;


    //bool _shaders;
//
//    int _width;
//    int _height;

//    enum EDictionaryTypes {
//    VideoDriverType,
//    AudioDriverType,
//    Count
//    };


//    const int& getWindowWidth() const;
//    const int& getWindowHeight() const;
//    const irr::core::dimension2du& getWindowSize() const;

    //SIrrlichtCreationParameters _parameters;

    //SIrrlichtCreationParameters _creationParameters;
    //static void initializeDictionaries();


    //bool _needRestart;

    //std::string _filename;
    //typedef std::map<std::string,int> TDictionary;

    //boost::array<TDictionary,Count> _dictionaries;

public:
    CConfigManager(
                //const std::string& filename
                );
    ~CConfigManager();

    void reset();

    typedef boost::shared_ptr< CBindCollection< NPlayerInput::Count > > TMappingPtr;


    TMappingPtr _mappingSet;

    // la reference is very important, otherwise can create trouble
    TMappingPtr getPlayerMapping() const { return _mappingSet; };

    // NEW

    //TMappings _mappings;

    //TMappingPtr getMappingSet();

    void enableShader(const std::wstring&, const bool&);

    //bool Save();
    bool RawSave(
                 const char* filename
                 //const CConfigManager& config
//                 const unsigned int& width,
//                 const unsigned int& height,
//                 const bool& vsync,
//                 const bool& fullscreen,
//                 const bool& enableDialogs
                 );


    bool loadFromFile(const char* filename
                     //CConfigManager& config
//                     unsigned int& width,unsigned int& height,
//                     bool& vsync,bool& fullscreen,bool& antialias,
//                     std::stringw& videoDriver,std::stringw& audioDriver
              );

//    bool Load(SIrrlichtCreationParameters& parameters);
};


#endif

