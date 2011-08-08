

#ifndef __IOBSERVER_HPP__
#define __IOBSERVER_HPP__

#include <string>
#include <boost/shared_ptr.hpp>

//#include "cmessage.hpp"

using namespace std;
using namespace boost;


/**
 *	A message listener.
 *	This is a base implementation for all of the message's handler
 */
class IObserver
{

public:

	/**
	 * This is a constructor
	 */
	IObserver() {}

	/**
	 * This is a destructor
	 */
	virtual ~IObserver() {}

	/**
	 * This method is called in order to process a message
	 * @param message The message this method will have to process

	 shared_ptr<CMessage>

	 */
	virtual void handleMessage ( const CMessage& message ) = 0;


};

#endif // __CMESSAGELISTENER_H__
