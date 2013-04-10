#pragma once

#include "forward.h"

enum eMessageType
{
	SetPosition,
	GetPosition,    
	DrawMessage,
	updateMessage,
	rotationMessage,
};

class BaseMessage
{
protected: // Abstract class, constructor is protected
	BaseMessage(int destinationObjectID, eMessageType messageTypeID);

public: // Normally this isn't public, just doing it to keep code small
	int m_destObjectID;
	eMessageType m_messageTypeID;
};