#include "CLuaVM.hpp"
#include "CLuaThread.hpp"
// TODO remove that dependancy
#include "../logging/ILogger.hpp"
#include "../core/CStringBuilder.hpp"
#include "../../../src/audio/SAudioParameters.hpp"
#include <luabind/luabind.hpp>
#include <luabind/class_info.hpp>
#include <lua/lua.hpp>

// TODO a supprimer pr après les tests
#include <irrlicht.h>


using namespace luabind;
using namespace detail;


namespace fus {



//TOnLuaErrorCallback CLuaVM::onLuaErrorFunction = 0;
TOnLuaErrorCallback onLuaErrorFunction = 0;

/*
typedef void (*lua_Hook) (lua_State *L, lua_Debug *ar);
Type for debugging hook functions.
*/
int
onLuaPanic(lua_State *s){
    _LOG_ERROR << "LUA PANIC" << "tODO chercher erreur sur la stack";
    // TODO a
    throw std::runtime_error("Lua PANIC");
}




// TODO should print stack
int
onLuaError(lua_State *state){

    _LOG_ERROR << "onLuaError called";

    //std::string error;
    //stackDump(state);

    luaL_traceback(state,state,"onLuaError called",0);

    //const char *luaL_tolstring (lua_State *L, int idx, size_t *len);
    _LOG_ERROR << luaL_tolstring ( state, -1, 0);

    if(onLuaErrorFunction){
        _LOG_ERROR << "onLuaErrorFunction defined, should be executed";
    }

// Returns an error
    return 1;
}



//lua_State* state
CLuaVM::CLuaVM() : _vm(0)
{

    //luabind::set_pcall_callback( onLuaError );
    //registerErrorHandlers();

    createVM();
    luabind::set_pcall_callback( onLuaError );
    lua_atpanic (this->getVM(), onLuaPanic);
}



CLuaVM::~CLuaVM(){

    //luabind::close()
    // BUG ?
    //lua_close(_vm);
    //_INFO << "Lua VM destroyed";
}



/**
object_rep.cpp push_metatable
//faut recuperer le int m_instance_metatable; dans class registry via cpp_instance
class_rep => metatable_ref recupere l'integer de la metatable et après on modifie la valeur de __newindex
puis
class_registry.cpp, line 79,
int create_cpp_instance_metatable(lua_State* L)
you can specify your own function for __newindex method

__newindex closure by default is "set_instance_value" in object_rep
**/
// TODO transformer en template !
/*

    //luabind::detail::class_registry reg( getVM() ); / get_classes
    //metatable_ref class_re::metatable_ref est interessan

    //get_class_names dans class_info.hpp est intéressant aussi
    class_rep* rep = reg->find_class();
    if(! rep ) return false;


    // ou bien on utilise get_class_info
    // prend un argument une classe argument définie dans object.hpp
    set_instance_value
    //virtual_def est appelé quand on enregistre une fonction (la fin de class.hpp)

    il y a une metatable cree par une class_rep
    dans push_instance_metatable() dans
    chaque object_rep.cpp prend comme metatable celle de sa class_rep associee.
    L'idée est donc d'aller modifier la metatable de la class_rep associee au object_rep

    exemple de comment initialiser le type_id se situe dans
    class_base::init( typeid(T) trouve ligne 782 de class.hpp


def_readwirte =>
            this->add_member(
                new registration_type(
                    name, mem_ptr, detail::null_type(), mem_ptr));
dans "class.hpp"

add_member qu'on trouve dans class.cpp l.259 qui fait m_registration->m_members.operator,(scope(ptr));
cree une liste chainee des scopes

class_registration defini dans class.cpp

Dans object_rep.cpp, dans la fonction "push_instance_metatable" => on push un __newindex = set_instance_value

aussidansleconstructeurdeclass_rep.cpponserendcompteqqu'ilyaa
*/
bool
CLuaVM::setSpecialNewIndex(const char* class_name){


    luabind::detail::class_registry* reg  = detail::class_registry::get_registry( _vm );
    luabind::detail::class_rep* rep = reg->find_class( typeid(irr::SIrrlichtCreationParameters) );
    luabind::detail::class_rep* rep_audio = reg->find_class( typeid(audio::SAudioParameters) );
    // _INFO << get_class_name( typeid(irr::SIrrlichtCreationParameters) );



    if(!rep){
        _LOG_WARNING << "could not find a class rep for SIrrlichtCreationParameters";
        return false;
    }
    else {
        _INFO << "found rep for class '" << rep->name() << "'";
        _INFO << "registry: cpp_class" << reg->cpp_class();
        _INFO << "registry: cpp_instance" << reg->cpp_instance();
        _INFO << "registry: lua_instance" << reg->lua_instance();
        _INFO << "registry: lua_class" << reg->lua_class();
    }


    if(!rep_audio){
        _LOG_WARNING << "could not find a class rep for SIrrlichtCreationParameters";
        return false;
    }
    else {
        _INFO << "found rep for class '" << rep_audio->name() << "'";
//        _INFO << "registry: cpp_class" << rep_audio->cpp_class();
//        _INFO << "registry: cpp_instance" << rep_audio->cpp_instance();
//        _INFO << "registry: lua_instance" << rep_audio->lua_instance();
//        _INFO << "registry: lua_class" << rep_audio->lua_class();
    }

    int index = rep->metatable_ref();
    _INFO << "class_rep: metatable_ref" << rep->metatable_ref();

    // voici la cle utilise pour acceder au tableau representant la metatable
    lua_pushinteger( _vm, index );
    //Pushes onto the stack the value t[k], where t is the value at the given valid index and k is the value at the top of the stack.
    // Pushes on top of stack the metatable
    lua_gettable(_vm, LUA_REGISTRYINDEX);
    // la on se retrouve avec la metatable sur la stack
//    Returns 1 if the value at the given acceptable index is a table, and 0 otherwise.
    //_INFO << "Is table (should be table )" << lua_istable( _vm, -1);

    lua_pushstring( _vm , "__newindex");
    //    //class_rep::lua_settable_dispatcher
    lua_pushcclosure(_vm, &onNewIndex, 0);
    // set new index
    lua_rawset( _vm, -3);


    // pop le tableau /metatable
    lua_pop( _vm,1);
    return true;
}

int onIndex(lua_State *L) {
    _INFO << "onIndex called";
    return 0;
}

/**
Each instance is pushed via lua_newuserdata
Userdata represent C values in Lua. A full userdata represents a block of memory. It is an object (like a table): you must create it, it can have its own metatable, and you can detect when it is being collected. A full userdata is only equal to itself (under raw equality).


**/
int onNewIndex(lua_State *L) {
// table, key, value are pushed onto the stack
    _INFO << "onNewIndex called";
  //Pushes onto the stack the environment table of the value at the given index.
/*  lua_getfenv(L, 1);
  //Pushes a copy of the element at the given valid index onto the stack.
  //copiesthepreviousenvtable
  lua_pushvalue(L, 2);
  //Pushes onto the stack the value t[k], where t is the value at the given valid index and k is the value at the top of the stack.
  lua_rawget(L, -2);

  if (lua_isnil(L, -1) && lua_getmetatable(L, -2))
  {
      _INFO << "is NIL";
      lua_pushvalue(L, 2);
      lua_rawget(L, -2);
      lua_replace(L, -3);
      lua_pop(L, 1);
  }

  if (lua_tocfunction(L, -1) == &property_tag)
  {
      _INFO << "is property";
      // this member is a property, extract the "set" function and call it.
      lua_getupvalue(L, -1, 2);

      if (lua_isnil(L, -1))
      {
          lua_pushfstring(L, "property '%s' is read only", lua_tostring(L, 2));
          lua_error(L);
      }

      lua_pushvalue(L, 1);
      lua_pushvalue(L, 3);
      lua_call(L, 2, 0);
      return 0;
  }

  lua_pop(L, 1);

  if (!lua_getmetatable(L, 4))
  {
      _INFO << "is !lua_getmetatable";
    // ajoute par moi <<<<<
        lua_pushfstring(L, "bug ici ", lua_tostring(L, 2));
        lua_error(L);
    // fin ajoute par moi <<<<<

//      lua_newtable(L);
//      lua_pushvalue(L, -1);
//      lua_setfenv(L, 1);
//      lua_pushvalue(L, 4);
//      lua_setmetatable(L, -2);
  }
  else
  {
      lua_pop(L, 1);
  }

  lua_pushvalue(L, 2);
  lua_pushvalue(L, 3);
  lua_rawset(L, -3);
  */
  return 0;

}


/*int onNewIndex(lua_State *L) {
//int specialNewIndex() {
    _INFO << " NEW INDEX FUNCTION CALLED";
// BUG ;
// Les 2 get_table renvoient rien

    //stackDump(L);
    // Le stackdump affiche userdata/cle/valeur
    // en bas de la stack on recupere le lua_touserdata
	//luabind::
	//If the value at the given acceptable index is a full userdata, returns its block address. If the value is a light userdata, returns its pointer. Otherwise, returns NULL.




	detail::class_rep* crep = static_cast<detail::class_rep*>(lua_touserdata( L, 1));
    if(!crep){
        _LOG_WARNING << "Could not find crep ";
        return 1;
    }
    _INFO << "got crep for class "  << crep->name() ;

    lua_pop(L,3);


	// push first table onto the stack (on top of lua user data)
	// le bug c'est que ca ca push nil


	//crep->get_table(L);
    //_INFO << "Is table (should be table )" << lua_istable( _vm, -1);

	// copy key, then value
	//lua_pushvalue(L, -3);
	//lua_pushvalue(L, -3);
	//stackDump(L);

	// set the value without calling metamethod
	lua_rawset(L, -3);


	// pop table
	lua_pop(L, 1);

	// get default table
	crep->get_default_table(L);
	//Moves the top element into the given position (and pops it), without shifting any element
	// remplace le userdata en 1 par le tableau
	//lua_replace(L, 1);

	// cet appel pop ensuite la cle et la value
	//lua_rawset(L, -3
	return 0;
}
*/



bool
CLuaVM::retrieveStringFromStack(std::string& msg){

    //luabind::object obj( luabind::from_stack( getVM(), -1) );
                //
    //msg.append("\n");
    msg.append(lua_tostring( getVM(), -1) );

    //msg.append( luabind::object_cast<std::string>( obj ) );

    //
    return (!msg.empty());
}





// TODO lua_gettop(L)
//TOnLuaErrorCallback
void
//CLuaVM::registerErrorHandlers( luabind::pcall_callback_fun onErrorFunction){
CLuaVM::registerErrorHandlers( TOnLuaErrorCallback& onErrorFunction){



    //lua_CFunction
    onLuaErrorFunction = onErrorFunction;

    // TODO
    //return 0;
}



void
CLuaVM::getGlobals( luabind::object& g){
    g = luabind::globals( this->getVM() );
}


/**
// TODO
int LuaPrint(lua_State *L)
{
	int nArgs = lua_gettop(L);
	int i;
	lua_getglobal(L, "tostring");
	std::string ret;//this is where we will dump the output
	//make sure you start at 1 *NOT* 0
	for(i = 1; i <= nArgs; i++)
	{
		const char *s;
		lua_pushvalue(L, -1);
		lua_pushvalue(L, i);
		lua_call(L, 1, 1);
		s = lua_tostring(L, -1);
		if(s == NULL)
			return luaL_error(L, LUA_QL("tostring") " must return a string to ", LUA_QL("print"));

		if(i > 1) ret.append("\t");

		ret.append(s);
		lua_pop(L, 1);
	};
	ret.append("\n");
	//Send it wherever
	glConsole::GetSingleton().Echo(ret.c_str());
	return 0;
};
[...]
	//same as before register it with the state
	lua_register(MainState, "print", LuaPrint );
	*/
bool
CLuaVM::bind(const luabind::scope& scope) {

    try {

        // On peut passer un nom de namespace
        //luabind::module( this->getVM(), "logger" )[
        luabind::module( this->getVM() )[
            scope
        ];
        return true;
    }
    //catch(luabind::error& e)
    catch(...){
        return false;
    }
}


int
CLuaVM::saveTopChunkIntoGlobals() {
    //

    //return luaL_ref(_vm, LUA_GLOBALSINDEX );
    return 0;
    //(_vm)
}


bool
CLuaVM::execute(){
    /*
If errfunc is 0, then the error message returned on the stack is exactly the original error message. Otherwise, errfunc is the stack index of an error handler function. (In the current implementation, this index cannot be a pseudo-index.) In case of runtime errors, this function will be called with the error message and its return value will be the message returned on the stack by lua_pcall.
*/

// will push the error function  each time
    //int result = luabind::detail::pcall(getVM(), 0, LUA_MULTRET);

    // Aller chercher la fct d'erreur dans detail::pcall
    int result = 0;
    //result = luabind::detail::pcall(getVM(), 0, LUA_MULTRET);

		pcall_callback_fun e = get_pcall_callback();
		int en = 0;
		if ( e )
		{
			int base = lua_gettop(_vm);
			lua_pushcfunction(_vm, e);
			lua_insert(_vm, base);  // push pcall_callback under chunk and args
			en = base;
  		}
  		//int lua_pcallk (lua_State *L, int nargs, int nresults, int errfunc,int ctx, lua_CFunction k);
		result = lua_pcallk(_vm, 0, 0, en,0,0);
        if ( en )
			lua_remove(_vm, en);  // remove pcall_callback


    // If we are here, it means there has been an error so we unwind stack
    if(result != 0){

        //_LOG_ERROR << "Error happened while executing";
        setErrorDescription(result);

        return false;
    }

    return true;
}





bool
CLuaVM::RunCommand(const char* param){

    int ret = luaL_loadstring( getVM(), param );
    if( ret != 0){
        setErrorDescription(ret);
        //_LOG_DEBUG << "TODO Lua could not load string";
        return false;
    }

    return execute();
}


// Push chunk onto stack
bool
CLuaVM::loadChunkFromGlobals(const int& index) {
    //lua_copy();
    //lua_pushvalue()
    //return execute();
//    lua_pushinteger( _vm, index);
//    lua_gettable (_vm, LUA_GLOBALSINDEX);
    //lua_pushinteger( _vm, index);
    //lua_gettable (_vm, -1);
    return false;
}

//int
bool
CLuaVM::loadChunkFromFile(const char* filename) {

    BOOST_ASSERT(filename);
    // TODO RunFunctionFromChunk
    //loadChunkFromGlobals
    int ret = luaL_loadfile( this->getVM(), filename);

    if(ret != 0){
        _LOG_ERROR << "Error while luaL_loadfile( " << filename << ")";
        //CLuaVM::getErrorDescription(ret);
        // _thread
        setErrorDescription(ret);
        //CLuaVM::handleError( getVM() );
        return false;
    }
    return true;
}



/**
TODO si fichier corrompu alors interrompre le fichier puis le recharger quand modifié
**/
bool
CLuaVM::RunFile(const char* param){


	// on peut supprimer  le try/Catch car pas cense lance d'exception
//certainement
    return (loadChunkFromFile(param) && execute() );

}

//std::string
//CLuaVM::retrieveStringFromTopOfStack() {
//
//}

//std::string
void
CLuaVM::setErrorDescription(const int& ret){

    bool retrieveErrorMsgFromStack = false;
    std::string msg;
    switch( ret ){

        // tt est ok
        case LUA_YIELD :
            //LUA_ERROK
        case 0:
            return;
            //break; //return true;

        case LUA_ERRERR:
            msg = "LUA_ERRERR: error while running error handler";
            break;

        case LUA_ERRMEM:
            msg = "LUA_ERRMEM: Memory allocation error";
            break;

        case LUA_ERRRUN:
            // TODO : la vm n'arrete pas de grossir, elle a plein de nil qui s'ajoute
            msg = "LUA_ERRRUN: Runtime error.";// + lua_gettop(_vm->getVM() );
            retrieveErrorMsgFromStack = true;
            //stack size before from_stack


            //CLuaVM::handleError(_vm->getVM() );
            //_LOG_WARNING << "Should print stack";
            break;

        case LUA_ERRFILE:
            msg = "LUA_ERRFILE: Could not find file";
            break;

        case LUA_ERRSYNTAX:
           msg = "LUA_ERRSYNTAX: Syntax error during pre-compilation";
           retrieveErrorMsgFromStack = true;
           break;

        default:
            msg = "Unhandled lua error";
            //msg += ret;
            //std::cout << " ret" <<  ret;
           break;
    }

    // If error message should be on top of stack then we try to retrieve it
    if(retrieveErrorMsgFromStack)
    {
        retrieveStringFromStack(msg);
    }


    //return msg;
    // TODO a modifier
    /*
    std::string temp;
    if(!handleError( getVM(), temp)){

        //msg.append("Could not retrieve error from stack");
        msg.append(temp);
    }
    else {
        msg.append(temp);
    }
        */
    _errorMessage = msg;
}




// protected
//void
//CLuaVM::createVM(){
//
//    lua_close(_vm);
//}


void
CLuaVM::createVM(){
	// initialize Lua
    _vm = luaL_newstate();

    // load Lua base libraries
    luaL_openlibs(_vm);
    //luaopen_debug(_vm);

    // Connect LuaBind to this lua state
    luabind::open(_vm);
}



void
CLuaVM::reset() {


    if( _vm ){
        lua_close(_vm);
    }
    createVM();
}



/**
should return an error code
**/
bool
CLuaVM::handleError(lua_State* state,std::string& errorDescription){


    lua_Debug d;

    fus::TCharStringBuilder stream("");
    // 2nd parameter is the level of function 0 => current function
    // n+1 level calls level nfunction

    // recupere le message de debug implante par lua
    luabind::object obj(luabind::from_stack(state, -1) );

    if(lua_getstack(state, 1, &d) !=  1 ){

        errorDescription = "Could not retrieve item from stack at level [1]. Dump stack... ";
        //int top = lua_gettop(L);

        stackDump(state);
        return false;
    }

    // could dumpa stack


    //Returns information about a specific function or function invocation
    // must be called with a valid lua_Debug,
    // 's','l','n' fills certain fields of lua_Debug
    // l => line
    // Returns 0 on error
 //object error_stream(from_stack(e.state(), -1));

    // regarder ici comment on pop le message pr en pusher un plus complet
    // http://www.rasterbar.com/products/luabind/docs.html#error-handling
    if(lua_getinfo(state, "Sln", &d) == 0){
        //stream();
        errorDescription = "Couldn't retrieve info from stack";
        return false;
    }

//a "printable" version of source d.short_src

    std::string src(d.source);
    // if true, then we have the filename
    // otherwise it is the string defining function
    if( !src.empty() && src[0] == '@'){
        //
        //src =
        stream("Line [")( d.currentline );
        stream("] of file ");//("\" in code:\n");

    }
    else {
        stream("In code \n");
    }

    stream(d.short_src)
    ("\nDescription of the problem:\t")("\n");
    stream(obj);
    //(lua_tostring(mLuaState, -1))

    // name is a reasonable name for a function
    // namewhat a more descriptible
    if (d.name != 0){
        try {
            stream("(")( d.namewhat )( " " )(d.name)(")");
        }
        catch(std::exception& e){
            _LOG_ERROR << "Lua error";
        }
    }
    else {
        stream("d.name == 0");
    }

//int luaL_LOG_ERROR (lua_State *L, const char *fmt, ...);
    //lua_pushstring(mLuaState, stream.str().c_str());
    //_errorMessage = stream.str();//lua_tostring(mLuaState,-1);
    errorDescription = stream.str() ;

    return true;
}






/**
TODO Dump stack
**/
void
stackDump (lua_State *L) {


      int top = lua_gettop(L);
      printf("\n======================\n");
      if(top == 0){
            printf("Stack empty\n");
      }
      else {
        printf("Stack size (lua_gettop() value ) : [%d]\n",top);
        }

      for (int i = 1; i <= top; i++) {  /* repeat for each level */


        //printf("default case");
        int t = lua_type(L, i);
        printf("Type [%s] for level [%d]\n\t", lua_typename(L,t),i);

        switch (t) {

          case LUA_TSTRING:  /* strings */
            printf("String: [%s]", lua_tostring(L, i));
            break;

          case LUA_TNIL:
              printf("Nil value");
              break;
          case LUA_TTHREAD:
              printf("Thread");
              break;

          case LUA_TBOOLEAN:  /* booleans */
            printf(lua_toboolean(L, i) ? "true" : "false");
            break;

          case LUA_TNUMBER:  /* numbers */
            printf("Number [%g]", lua_tonumber(L, i));
            break;
            // TODO http://www.lua.org/source/5.1/lua.h.html
          case LUA_TTABLE:
              // afficher le tableau
              printf("Table");
              break;
          default:  /* other values */
//              printf("");
                printf("Unhandled case of type [%s]", lua_typename(L, t));
                break;

        }
        printf("\n");  /* put a separator */
      }
//      printf("\n======================\n");  /* end the listing */
//      printf("\n=========== LUABIND VERSION ===========\n");  /* end the listing */
//
//      luabind::detail::stack_content_by_name(L,0);
//      printf("\n======================\n");
}


}
