

#ifndef __CMESSAGE_H__
#define __CMESSAGE_H__


#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/any.hpp>
#include <irrlicht.h>
#include "../utils/TClock.hpp"

#include "cmessagetype.h"
//const CMessageType MSG_ANYTYPE("*");

using namespace std;
using namespace boost;
using boost::any_cast;


class IMessageOriginator;

/**
 *	A message.
 */
class CMessage
{
	//private:
	public:
        // Est dorenavant un entier
		TMessageType m_type;
		boost::any _data;

		IMessageOriginator* _sender;

		// Delay
		TTimer::TimeType _delay;

	public:
        //int Type;

		/**
		 * This is a constructor
		 */
        //m_type(_msgtype), m_userdata(_data)
		CMessage() {};


        //IMessageOriginator* originator = 0,
        void setup(const TMessageType& msgtype, const boost::any& data = boost::any() );

		/**
		 * This is a destructor
		 */
		~CMessage() {}

		/**
		 * This returns the type of this message
		 *	@return CMessageType	:	Its type
		 */
		TMessageType getType() const {return m_type;}

		/**
		 * This returns the data contained in this message
		 *	@return shared_ptr<boost::any>	:	Its data
		 */
		template <class T> T getData() {return  T (boost::any_cast<T>(_data)) ;}


////////////////////////////////////////////
///
///     Necessary when used with std::set
///
////////////////////////////////////////////

		/**
		 * Operator ==
		 * @param op A message's type to compare to
		 * @return bool : The result :)
		 */
		bool operator== (CMessage const & op);

		/**
		 * Operator !=
		 * @param op A message's type to compare to
		 * @return bool : The result :)
		 */
		bool operator!= (CMessage const & op);

		/**
		 * Operator <
		 * @param op A message's type to compare to
		 * @return bool : The result :)
		 */
		bool operator< ( CMessage const & op ) const;
};

#endif // __CMESSAGE_H__
