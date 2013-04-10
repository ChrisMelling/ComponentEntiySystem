#pragma once

#include "forward.h"
#include "BaseComponent.h"
#include "BaseMessage.h"

class Object
{
public:
	Object(sf::RenderWindow &renderWindow ,int uniqueID);

	int GetObjectID() const { return m_UniqueID; }
	void AddComponent(BaseComponent* comp);
	bool SendMessage(BaseMessage* msg);

private: // Methods
	bool PassMessageToComponents(BaseMessage* msg);

private: // Members
	int m_UniqueID;
	std::list<BaseComponent*> m_Components;

};