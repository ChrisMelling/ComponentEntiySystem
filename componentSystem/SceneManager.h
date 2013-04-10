#pragma once

#include "forward.h"

class SceneManager
{
public: 
	SceneManager();
	// Returns true if the object or any components handled the message
	bool SendMessage(BaseMessage* msg);

	Object* CreateObject(sf::RenderWindow &renderWindow);
	int nextObjectID;
private:
	std::map<int, Object*> m_Objects;

};


