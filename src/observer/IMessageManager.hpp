#include <string>

#ifndef __CMESSAGEMANAGER_H__
#define __CMESSAGEMANAGER_H__



#include "cmessagetype.h"
#include "IObserver.hpp"
#include <irrlicht.h>
#include <map>
#include <set>
#include <stack>
#include <boost/shared_ptr.hpp>
//multi
//using namespace std;




/**
 *	A message manager.
 *	This is a base implementation for all of the messages manager
 */
 // renommer en queue ?
class CMessageManager
{
//std::shared_ptr<
    static const unsigned int NUMQUEUE = 1;

    unsigned int m_activeQueue;

    typedef IObserver* TObserver;
    //boost::shared_ptr<IObserver>
    std::multimap<TMessageType, TObserver> _observers;

    // Utilise 2 sets pr eviter une boucle infinie
    std::set< CMessage* > _messages[NUMQUEUE];

    // Pool of messages 20 is the max size of the pool
    std::stack<CMessage*> _pool;

    // nb of elements in pool
    //std::size_t _pooled;




public:// TODO remove that dependance
    irr::ITimer* _timer;


	/**
	 * This is a constructor
	 */
	CMessageManager();

	/**
	 * This is a destructor
	 */
	virtual ~CMessageManager() {}


	/**
	 * This adds a new listener
	 * @param handler The listener which handle messages
	 * @param messagetype The listener will care about every message of this message type
	 * @return True if ok, false otherwise
	 */
	 //shared_ptr
    bool addListener ( boost::shared_ptr<IObserver> handler, const TMessageType& messagetype );

	/**
	 * This deletes a new listener
	 * @param handler The listener which handle messages
	 * @param messagetype The listener which have cared about every message of this message type
	 * @return True if ok, false otherwise
	 */
	 // TODO Not used yet
    //bool removeListener ( shared_ptr<IObserver> handler, TMessageType messagetype );

    //, IMessageLauncher* sender
    void
    addMessage(const TMessageType& type, const irr::u32& delay = 0, const boost::any& data = boost::any());

    irr::u32 getTriggerTime(const irr::u32& delay );


    void notify();


	/**
	 * This process a given message as parameter
	 * @param message The message to be processed
	 * @return True if ok, false otherwise
	 */
	//virtual bool trigger ( shared_ptr<CMessage> message ) = 0;


	/**
	 * This process the message queue
	 */
	//virtual void dispatchDelayedMessages( ) = 0;


};

#endif // __CMESSAGEMANAGER_H__
