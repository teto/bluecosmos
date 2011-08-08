/**
\file
\author
**/
#ifndef MACROS_HPP_INCLUDED
#define MACROS_HPP_INCLUDED


/// Defines macros
#define FUSION_MEMBER_FUNCTION(object,ptr_to_member_function) (object.(*ptr_to_member_function))

// Fonction valable pour les policy car il s'agit de fct statique !! mais pas
#define FUSION_CHECK_FUN(Policy, Member) enum { Policy##Member = sizeof(&Policy::Member) > 0 };


// limits a value to low and high
#define LIMIT_RANGE(value, low, high)	{	if (value < low)	value = low;	else if(value > high)	value = high;	}




#endif // MACROS_HPP_INCLUDED
