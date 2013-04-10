
#include "BaseMessage.h"

BaseMessage::BaseMessage(int destinationObjectID, eMessageType messageTypeID) 
		: m_destObjectID(destinationObjectID)
		, m_messageTypeID(messageTypeID)
{

}