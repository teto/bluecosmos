#ifndef _FUSION_CLUAMANAGER_HPP_INCLUDED
#define _FUSION_CLUAMANAGER_HPP_INCLUDED

#include "IScriptInterpreter.hpp"

#include <luabind/lua_include.hpp>
#include <luabind/luabind.hpp>
#include <string>

#if 0
namespace fus {

//std::string const&,
typedef void (*TOnLuaErrorCallback)(std::string const&);



extern TOnLuaErrorCallback onLuaErrorFunction;

// Utilities
int onLuaError(lua_State*);
int onLuaPanic(lua_State *s);
int onNewIndex(lua_State *s);
int onIndex(lua_State *L);
void stackDump (lua_State *L);

//lua_State *L
//int specialNewIndex();

    //typedef boost::function<void,const std::string&> f;

// Pour passer en mode debug !!
    //int lua_sethook (lua_State *L, lua_Hook f, int mask, int count);


class CLuaManager :
    public CSingleton<CLuaManager>
{
    friend class CSingleton<CLuaManager>;

public:

    CLuaVM();
    virtual ~CLuaVM();


    //static TOnLuaErrorCallback registerErrorHandlers(TOnLuaErrorCallback&);
    static void registerErrorHandlers(TOnLuaErrorCallback&);

    /**
    Retreive string on top of stack
    **/
    bool retrieveStringFromStack(std::string&);

    void reset();

    /** \brief
     *
     * \param
     * \param
     * \return true if error
     *
     */
    //static bool checkReturnValue(const int&);
    static bool handleError(lua_State* state,std::string&);
    const std::string& getErrorDescription() {return _errorMessage; };
    void setErrorDescription(const int&);
    bool bind(const luabind::scope& scope);
    bool RunCommand(const char* param);
    bool RunFile(const char* param) ;
    bool RunChunk(const int& array,const int& index) ;


//    bool loadChunkFromFile(const char*) {
//        int temp;
//        return loadChunkFromFile();
//    }
    bool loadChunkFromFile(const char*);
    bool loadChunkFromGlobals(const int&);

    int saveTopChunkIntoGlobals();

    void getGlobals( luabind::object& );
    lua_State* getVM() { return _vm;};
    virtual bool execute();

    // Prevents creation of new attributes to a class
    bool setSpecialNewIndex(const char*);


protected:
//    static TOnLuaErrorCallback onLuaErrorFunction;

    void createVM();
    void destroyVM();

    //int loadString(const char*);

    lua_State* _vm;
    std::string _errorMessage;

};



}
#endif

#endif
