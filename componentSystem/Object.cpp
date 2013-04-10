
#include "Object.h"

Object::Object(sf::RenderWindow &renderWindow ,int uniqueID): m_UniqueID(uniqueID)
{

}

void Object::AddComponent(BaseComponent* comp)
{
	comp->setOwner(this);
    m_Components.push_back(comp);
}

bool Object::SendMessage(BaseMessage* msg)
{
	bool messageHandled = false;

	// Object has a switch for any messages it cares about
	switch(msg->m_messageTypeID)
	{

	default:
		return PassMessageToComponents(msg);
	}

	// If the object didn't handle the message but the component
	// did, we return true to signify it was handled by something.
	messageHandled |= PassMessageToComponents(msg);

	return messageHandled;
}

bool Object::PassMessageToComponents(BaseMessage* msg)
{
	bool messageHandled = false;

	std::list<BaseComponent*>::iterator compIt = m_Components.begin();
	for ( compIt; compIt != m_Components.end(); ++compIt )
	{
		messageHandled |= (*compIt)->SendMessage(msg);
	}

	return messageHandled;
}