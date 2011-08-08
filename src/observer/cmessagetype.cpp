#include "../include/cmessagetype.h"


bool CMessageType::operator== (CMessageType const & op)
{
	return (this->m_msgtype == op.m_msgtype);

}


bool CMessageType::operator!= (CMessageType const & op)
{
	return !(*this == op);
}


bool CMessageType::operator< (CMessageType const & op) const
{
	return ( this->m_msgtype < op.m_msgtype );
}
