#ifndef _BINDS_HPP_INCLUDED
#define _BINDS_HPP_INCLUDED

#include <luabind/luabind.hpp>


////////////////////////////////////////////////////:
/// Binding functions
////////////////////////////////////////////////////:

luabind::scope bindConfigStructToLua( );
luabind::scope bindLevelHandlerToLua( );
luabind::scope bindSound( );
luabind::scope bindPlayerToLua( );
luabind::scope bindEngineToLua( );
luabind::scope bindFleets( );


#endif
