#ifndef _BIND_CONCAT_HPP_INCLUDED
#define _BIND_CONCAT_HPP_INCLUDED

#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>

namespace luabind {


#define LUABIND_BINARY_METAMETHOD(name_, op,fn) \
    namespace operators { \
\
        struct name_ \
        { \
            template<class T0, class T1, class Policies> \
            struct apply \
            { \
                static void execute(lua_State* L, T0 _0, T1 _1) \
                { \
                    detail::operator_result(L, fn(_0 , _1), (Policies*)0); \
                } \
            }; \
\
            static char const* name() \
            { \
                return "__" # name_; \
            } \
        }; \
\
    }\
    template<class T, class U> \
    detail::binary_operator< \
        operators::name_ \
      , U \
      , T \
    > \
    inline op(self_base<U>, T const&) \
    { \
        return 0; \
    } \
    \
    template<class T, class U> \
    detail::binary_operator< \
        operators::name_ \
      , T \
      , U \
    > \
    inline op(T const&, self_base<U>) \
    { \
        return 0; \
    } \
    \
    detail::binary_operator< \
        operators::name_ \
      , self_type \
      , self_type \
    > \
    inline op(self_type, self_type) \
    { \
        return 0; \
    } \
    \
    detail::binary_operator< \
        operators::name_ \
      , self_type \
      , const_self_type \
    > \
    inline op(self_type, const_self_type) \
    { \
        return 0; \
    } \
    \
    detail::binary_operator< \
        operators::name_ \
      , const_self_type \
      , self_type \
    > \
    inline op(const_self_type, self_type) \
    { \
        return 0; \
    } \
    \
    detail::binary_operator< \
        operators::name_ \
      , const_self_type \
      , const_self_type \
    > \
    inline op(const_self_type, const_self_type) \
    { \
        return 0; \
    }



    template<class T0,class T1>
    std::string onConcat(T0 const& _0,T1 const& _1)
    {
#ifdef LUABIND_NO_STRINGSTREAM
        std::strstream s;
        s << _0 << _1 << std::ends;
#else
        std::stringstream s;
        s << _0 << _1;
#endif
        return s.str();

        //return s.str();
        //return std::string("[CONCAT function called]");
    }


//concat_operator
    LUABIND_BINARY_METAMETHOD(concat,concat_operator,onConcat)

    #undef LUABIND_BINARY_METAMETHOD

}


#endif
