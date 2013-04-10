
#include "BaseComponent.h"

BaseComponent::BaseComponent() 
{

}

bool BaseComponent::SendMessage(BaseMessage* msg) { return false; }

void BaseComponent::setOwner(Object* owner)
{
	_owner = owner;
}