#ifndef _FUSION_WSTRING_CONVERTER
#define _FUSION_WSTRING_CONVERTER

#include <luabind/luabind.hpp>
#include "../core/string.hpp"


namespace luabind
{
        template <>
        struct default_converter< std::wstring >
                : native_converter_base< std::wstring >
        {
                static int compute_score( lua_State * s, int index )
                {
                        return lua_type( s, index ) == LUA_TSTRING ? 0 : -1;
                }

                std::wstring from( lua_State * s, int index )
                {
                    std::wstring res;
                    convertIntoWideString(lua_tostring( s, index ), res);
                        return  res;
                }

                void to( lua_State * s, const std::wstring & str )
                {
                    convertIntoWideString
                        lua_pushstring( s, StrUtils::Narrow( str ).c_str( ) );
                }
        };




        ///

        template <>
        struct default_converter< const std::wstring >
                : default_converter< std::wstring >
                { };

        template <>
        struct default_converter< const std::wstring & >
                : default_converter< std::wstring >
                { };
}


#endif
