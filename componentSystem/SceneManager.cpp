

#include "SceneManager.h"
#include "BaseMessage.h"
#include "BaseComponent.h"
#include "Object.h"

SceneManager::SceneManager()
{
	 nextObjectID = 0;
}

Object* SceneManager::CreateObject(sf::RenderWindow &renderWindow)
	{
		Object* newObj = new Object(renderWindow,nextObjectID++);
		m_Objects[newObj->GetObjectID()] = newObj;

		return newObj;
	}

bool SceneManager::SendMessage(BaseMessage* msg)
{
	// We look for the object in the scene by its ID
	std::map<int, Object*>::iterator objIt = m_Objects.find(msg->m_destObjectID);       
	if ( objIt != m_Objects.end() )
	{           
		// Object was found, so send it the message
		return objIt->second->SendMessage(msg);
	}

	// Object with the specified ID wasn't found
	return false;
}
