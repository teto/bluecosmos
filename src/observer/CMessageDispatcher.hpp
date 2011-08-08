#include <boost/shared_ptr.hpp>
#include <string>
#include <set>
#include <map>
#include <list>

#include "../include/cmessagemanager.h"
#include "../include/cmessagetype.h"
#include "../include/IObserver.h"
#include "../include/cmessage.h"
#include "../include/singleton.h"


#ifndef __CGENERICMESSAGEMANAGER_H__
#define __CGENERICMESSAGEMANAGER_H__

using namespace std;
using namespace boost;


/**
 *	A generic message manager.
 *	This is an implementation of a messages manager
 */
class CGenericMessageManager : public IMessageManager
{
	private :

		/**
		 * Total number of message queues
 		*/
		static const unsigned int NUMQUEUE = 2;



		/**
		 * A map which holds the listners related to a message type
		 */
		std::multimap< CMessageType, boost::shared_ptr<IObserver> > m_listeners;


		/**
		 * Mutex locking access to m_listeners
		 */
		//boost::recursive_mutex m_listenersMutex;


		/**
		 * There is two lists of messages. Only one is active at a time.<br>
		 * There is two lists of message in order to blocks infinites messages
		 * (a message which create another message and so on...)
		 */
		//list< shared_ptr<CMessage> > m_messages[NUMQUEUE];
		/**
		Les messages sont tries par leur
		delay puis par leur type
		**/
		std::set<CMessage> _messages;


		/**
		 * Mutex locking access to m_messages[]
		 */
		boost::recursive_mutex m_messagesMutex[NUMQUEUE];


		/**
		 * The index of the active message queue
		 */
		std::size_t m_activeQueue;


		/**
		 * Mutex locking access to m_activeQueue
		 */
		//boost::recursive_mutex m_activeQueueMutex;



	public :

		/**
		 * This is a constructor
		 */
		CGenericMessageManager(): m_activeQueue(0) {}

		/**
		 * This is a destructor
		 */
		virtual ~CGenericMessageManager() {}


		/**
		 * This adds a new listener
		 * @param handler The listener which handle messages
		 * @param messagetype The listener will care about every message of this message type
		 * @return True if ok, false otherwise
		 */
		virtual bool addListener ( shared_ptr<IObserver> handler, CMessageType messagetype );


		/**
		 * This deletes a new listener
		 * @param handler The listener which handle messages
		 * @param messagetype The listener which have cared about every message of this message type
		 * @return True if ok, false otherwise
		 */
		virtual bool delListener ( shared_ptr<IObserver> handler, CMessageType messagetype );


		/**
		 * This process a given message as parameter
		 * @param message The message to be processed
		 * @return True if ok, false otherwise
		 */
		virtual bool trigger ( shared_ptr<CMessage> message );


		/**
		 * This enqueue a message
		 * @param message The message to be processed
		 * @return True if ok, false otherwise
		 */
		virtual bool queueMessage ( shared_ptr<CMessage> message );


		/**
		 * This abort the first message or every message of type messagetype
		 * @param messagetype The message's or messages' type to be aborted
		 * @param alloftype Are every messages of type messagetype aborted ? (default : False)<br> True -> Yes <br> False -> No (only the first one is aborted)
		 * @return True if ok, false otherwise
		 */
		virtual bool abortMessage ( CMessageType messagetype, bool alloftype = false );


		/**
		 * This validate a message type
		 * @param messagetype The message type to be validated
		 * @return True if ok, false otherwise
		 */
		virtual bool validateType( CMessageType messagetype );


		/**
		 * This process the message queue
		 */
		virtual void process( );

};

#endif // __CGENERICMESSAGEMANAGER_H__
