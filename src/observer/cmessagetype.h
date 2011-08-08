#include <string>


#ifndef __CMESSAGETYPE_H__
#define __CMESSAGETYPE_H__


using namespace std;

// tt le reste apres c des commentaires
typedef int TMessageType;

//typedef 0 TAnyType;

namespace NMessageType {
    enum EId {
    CreatePlayerBullet,
    CreateEnemyBullet,
    CreateExplosion

    };

}






#if 0
// lis tof messages
/// signaux ou events ?
// entre parentheses donnes complementaire
addMessage(delay,sender, msgType, boost::any<data>)
Suicide,
Collision,  (sender)
Explosion   (coordonnes,taille ?)

Config (recreateWindow ?)



/**
 *	A message's type.
 */
class CMessageType
{
	private:

		/**
		 * A string which contain the message type
		 */
		string m_msgtype;

	public:

		/**
		 * This is a constructor
		 */
		CMessageType(string _msgtype): m_msgtype(_msgtype) {}

		/**
		 * This is a destructor
		 */
		~CMessageType() {}

		/**
		 * Operator ==
		 * @param op A message's type to compare to
		 * @return bool : The result :)
		 */
		bool operator== (CMessageType const & op);

		/**
		 * Operator !=
		 * @param op A message's type to compare to
		 * @return bool : The result :)
		 */
		bool operator!= (CMessageType const & op);

		/**
		 * Operator <
		 * @param op A message's type to compare to
		 * @return bool : The result :)
		 */
		bool operator< ( CMessageType const & op ) const;

		/**
		 * Returns its type
		 * @return string : The type
		 */
		string getTypeStr() {return m_msgtype;}

};
#endif


#endif // __CMESSAGETYPE_H__
