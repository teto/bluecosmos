/**
\file
\author
**/
#ifndef INTRUSIVE_HPP_INCLUDED
#define INTRUSIVE_HPP_INCLUDED


#include <boost/intrusive/slist.hpp>

namespace bin = boost::intrusive ;


/**
Templates du base_hook
http://www.boost.org/doc/libs/1_41_0/doc/html/intrusive/usage.html
//safe_link   auto_unlink
*/

//bin::link_mode<bin::auto_unlink>slist_
// on peut pas utiliser bin::link_mode<bin::auto_unlink>
// si cache_last active
//typedef bin::slist_base_hook<  > THookPerso;

struct SFleetTag;
struct SLevelTag;
//bin::tag<SFleetTag>
//, bin::void_pointer<CStaticBattery>
//bin::tag<SLevelTag>

class CStaticBattery;
class CMissile;
class CBullet;


//CStaticBattery
typedef bin::slist_base_hook< bin::tag<SLevelTag> > TLevelHook;
typedef bin::slist_base_hook< bin::tag<SFleetTag>  > TFleetHook;

////////////////////////////////////
///// Level manager list
typedef bin::slist<CStaticBattery, bin::base_hook<TLevelHook> , bin::linear<true>, bin::cache_last<true>  > TComprehensiveList;

////////////////////////////////////
//Fleet missiles
//typedef bin::slist<CMissile, bin::base_hook<TFleetHook> , bin::linear<true>, bin::cache_last<true>  > TMissileList;
//
//// Fleet bullets
//typedef bin::slist<CBullet, bin::base_hook<TFleetHook> , bin::linear<true>, bin::cache_last<true>  > TBulletList;


#endif
