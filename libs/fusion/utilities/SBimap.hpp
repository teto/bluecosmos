#ifndef _FUSION_SBIMAP_HPP_INCLUDED
#define _FUSION_SBIMAP_HPP_INCLUDED

#include <boost/bimap.hpp>

//http://www.boost.org/doc/libs/1_46_1/libs/bimap/doc/html/boost_bimap/the_tutorial/useful_functions.html
//namespace {
// 3ieme param = pointeur de fonction
// struct id {}
//tagged<T1,id>
// get<id>
//http://www.boost.org/doc/libs/1_47_0/libs/bimap/example/user_defined_names.cpp
template<class T1,class T2>
struct SBimap {
    // TODO checker que T1 != T2

    typedef boost::bimaps::bimap<T1,T2> TBimap;
    typedef typename TBimap::value_type TAssociation;
    typedef typename TBimap::left_map TLeftMap; // Use with references otherwise will copy
    typedef typename TBimap::right_map TRightMap; // Use with references otherwise will copy
    //TLeftMap& left_map;

    SBimap() //: left_map(Bimap.left_map)
    {

    }



    // \todo static
    TBimap Bimap;

    #define CONVERT(side)     \
    try { return _bimap.side.at(key);} \
    catch( std::out_of_range & e ) { \
        _LOG_ERROR << "Couldn't find " << #side << "key [" << key << "] in bimap"; \
        return _unknown; \
    }
    #undef CONVERT


//    insert(T1&,T2&){
//    }
//    find(T1 const& key){
//
//    }

    // TODO renvoyer un boost optional ?
    T2 convert(const T1& key) {
        //CONVERT(left)
        //boost::optional<T2> ret;
        //.find()
        return Bimap.left.at(key);
    }

    T1 convert(const T2& key) {
        //CONVERT(right)
        return Bimap.right.at(key);
    }

};

#endif
