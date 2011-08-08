#include "CMessage.hpp"
//IMessageOriginator* originator,
void
CMessage::setup(const TMessageType& msgtype, const boost::any& data )
{

    m_type = msgtype;
    //_sender = originator;
    _data = data;
}



// Basically we say that all messages are different
bool
CMessage::operator== (CMessage const & op)
{

	//return (  (this->m_type == op.m_type) && (this->_delay <= op._delay)  );
	return false;
}


bool
CMessage::operator!= (CMessage const & op)
{
	return !(*this == op);
}


bool
CMessage::operator< (CMessage const & op) const
{
	return ( (this->_delay <= op._delay) && (this->m_type < op.m_type) );
}
