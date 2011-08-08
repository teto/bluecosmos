#include <iostream>
#include <boost/foreach.hpp>


#include "IMessageManager.hpp"
//#include <boost/anycast.hpp>



CMessageManager::CMessageManager() : m_activeQueue(0) {


}


TTimer::TimeType
CMessageManager::getTriggerTime(const irr::u32& delay ){
    return (_timer->getTime() + delay ) ;
}

void
CMessageManager::addMessage(const TMessageType& type, const irr::u32& delay , const boost::any& data){

    //_messages
    CMessage* msg  = 0;

    //irr::u32 _timer->getTime ();
    if(! _pool.empty()){

        msg = _pool.top();
        _pool.pop();
    }
    else {
        msg = new CMessage();
    }

    // configure message
    msg->m_type = type;
    // TODO : renommate ?
    msg->_delay = getTriggerTime(delay);//delay;

    //;
    _messages[0].insert( msg );

    // add message to queue
}



bool
CMessageManager::addListener ( boost::shared_ptr<IObserver> handler, const TMessageType& messagetype )
{

	/*
	 * Each tupple (handler, message type) must be unique.
	 * So it's checked.
	 */

	bool found = false;
/*
    // check if listener already exists
	for (std::multimap< TMessageType, shared_ptr<IObserver> >::iterator it = _observers.lower_bound(messagetype);
		( (it != _observers.upper_bound(messagetype) ) && (found == false) ); ++it)
	{
		if ( (*it).second == handler )
			found = true;
	}


	if (found == true)
		return false;



	// * Finally the new listener is added :)


    _observers.insert( std::pair< TMessageType, shared_ptr<IObserver> >(messagetype, handler));
*/
	return true;

}



void
CMessageManager::notify( )
{

	/*
	 * We can't process an active message queue because a handler could create a
	 * new message which would be processed and would create another message and so on...
	 * So it would turn into an infinite loop.
	 */

	unsigned int queuetoprocess = 1;//m_activeQueue;

	// update queue
	//m_activeQueue = (m_activeQueue + 1) % NUMQUEUE;



	/*
	 * We send messages to every handlers which sniff everything
	 */

	BOOST_FOREACH( CMessage* msg, _messages[queuetoprocess] )
	//for ( list< shared_ptr<CMessage> >::iterator itmsg = m_messages[queuetoprocess].begin(); itmsg != m_messages[queuetoprocess].end(); itmsg++ )
	{

        //msg
/*
		for (std::multimap< TMessageType, boost::shared_ptr<IObserver> >::iterator it = _observers.lower_bound(anytype);
   	    it != _observers.upper_bound(boost::anytype) ; ++it)
		{

			((*it).second)->handleMessage( *msg );

		}



        //Then we send messages to registered handlers


		for (multimap< CMessageType, shared_ptr<IObserver> >::iterator it = _observers.lower_bound((*itmsg)->getType());
  	     it != _observers.upper_bound((*itmsg)->getType())  ; ++it)
		{

			((*it).second)->handle( *itmsg );

		}
*/
	}


    //erase all messages
	//m_messages[queuetoprocess].erase( m_messages[queuetoprocess].begin(), m_messages[queuetoprocess].end() );
}






#if 0
bool
CMessageManager::removeListener ( shared_ptr<IObserver> handler, CMessageType messagetype )
{


	/*
	 * If this listener handle message types that are unknown,
	 * it returns false because it's impossible to have it also in the listener's multimap.
	 */
	{

		if ( m_messageTypes.find(messagetype) == m_messageTypes.end() )
		{

			pair<set<CMessageType>::iterator,bool> result = m_messageTypes.insert(messagetype);

			if ( ( result.second == false ) ||  ( result.first == m_messageTypes.end() ) )
				return false;

		}
	}


	/*
	 * Then it's deleted from the listener's multimap
	 */

	bool found = false;

	{
		boost::recursive_mutex::scoped_lock lock(m_listenersMutex);
		multimap< CMessageType, shared_ptr<IObserver> >::iterator result = m_listeners.end();

		for (multimap< CMessageType, shared_ptr<IObserver> >::iterator it = m_listeners.lower_bound(messagetype);
			( (it != m_listeners.upper_bound(messagetype) ) && (found == false) ); ++it)
		{
			if ( (*it).second == handler )
			{
				found = true;
				result = it;
			}
		}

		if (found == false)
			return false;

		m_listeners.erase( result );
	}




	/*
	 * If this listener was the last one to handle its message type,
	 * the message type has to be deleted from the set of message types.
	 */
	{
		boost::recursive_mutex::scoped_lock lock(m_listenersMutex);
		if ( m_listeners.find(messagetype) == m_listeners.end() )
		{

			boost::recursive_mutex::scoped_lock lock(m_messageTypesMutex);

			set<CMessageType>::iterator result = m_messageTypes.find(messagetype);

			if ( result != m_messageTypes.end() )
			{
				m_messageTypes.erase(result);
			}
			else
				// message type not found
				return false;
		}
	}


	return true;

}
#endif

