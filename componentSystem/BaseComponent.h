#pragma once

#include "forward.h"

class BaseComponent
{
public:
	BaseComponent();
	virtual bool SendMessage(BaseMessage* msg);

	void setOwner(Object* owner);

	Object* _owner;
};