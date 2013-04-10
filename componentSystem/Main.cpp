#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include <iostream>
#include <stdio.h>

#include <conio.h>
#include <windows.h>

using namespace std;
#include <list>
#include <map>

#include "SceneManager.h"
#include "Object.h"
#include "BaseMessage.h"
#include "BaseComponent.h"

class Draw : public BaseMessage
{
public: // Abstract class, constructor is protected
	Draw(int destinationObjectID)
		: BaseMessage(destinationObjectID, DrawMessage)
	{

	}
};

class Update : public BaseMessage
{
public: // Abstract class, constructor is protected
	Update(int destinationObjectID)
		: BaseMessage(destinationObjectID, updateMessage)
	{

	}
};

class PositionMessage : public BaseMessage
{
protected: // Abstract class, constructor is protected
	PositionMessage(int destinationObjectID, eMessageType messageTypeID, 
		sf::Vector2f pos)
		: BaseMessage(destinationObjectID, messageTypeID)
		, pos(pos)
	{

	}

public:
	sf::Vector2f pos;
};

class RotationMessage : public BaseMessage
{
public: // Abstract class, constructor is protected
	RotationMessage(int destinationObjectID, float rotation)
		: BaseMessage(destinationObjectID, rotationMessage)
		, _rotation(rotation)
	{

	}

public:
	float _rotation;
};

class MsgSetPosition : public PositionMessage
{
public:
	MsgSetPosition(int destinationObjectID, sf::Vector2f pos)
		: PositionMessage(destinationObjectID, SetPosition, pos)
	{}
};

class MsgGetPosition : public BaseMessage
{
public:
	MsgGetPosition(int destinationObjectID)
		: BaseMessage(destinationObjectID, GetPosition)
	{}

	sf::Vector2f pos;
};


class PlayerInputComponent : public BaseComponent
{
public:

	PlayerInputComponent(sf::RenderWindow* renderWindow,SceneManager *manager)
		: BaseComponent()
	{
		_window = renderWindow;
		_manager = manager;
	}

		bool SendMessage(BaseMessage* msg)
		{
			// Object has a switch for any messages it cares about
			switch(msg->m_messageTypeID)
			{

			case updateMessage:
				{               
					sf::Vector2f direction;

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){direction.x -= 0.2f;}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){direction.x += 0.2f;}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){direction.y -= 0.2f;}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){direction.y += 0.2f;}

					MsgSetPosition msgSetPos(_owner->GetObjectID(), direction);
					_manager->SendMessage(&msgSetPos);
				}
				break;
			}

			return true;
		}

	sf::RenderWindow *_window;
	SceneManager *_manager;
};

class WanderAIComponent : public BaseComponent
{
public:

	WanderAIComponent(sf::RenderWindow* renderWindow,SceneManager *manager)
		: BaseComponent()
	{
		_window = renderWindow;
		_manager = manager;

		float r1 = -1 + (float)rand()/((float)RAND_MAX/(-1-1));
		 
		float r2 = -1 + (float)rand()/((float)RAND_MAX/(-1-1));


		float radians = atan2(r1,r2);
		degrees = (radians/3.14159265) * 180;
		               
		double radian = degrees * (3.14159265 / 180);

		direction = sf::Vector2f((float)cos(radian), (float)sin(radian));
	}

		bool SendMessage(BaseMessage* msg)
		{
			// Object has a switch for any messages it cares about
			switch(msg->m_messageTypeID)
			{

			case updateMessage:
				{              
					// Get 'myObj' position to verify it was set properly
					MsgGetPosition msgGetPos(_owner->GetObjectID());
					_manager->SendMessage(&msgGetPos);

					if(msgGetPos.pos.x > 600) {direction.x *= -1;}
					if(msgGetPos.pos.y > 600) {direction.y *= -1;}
					if(msgGetPos.pos.y < 0) { direction.y *= -1;}
					if(msgGetPos.pos.x < 0) { direction.x *= -1;}

					MsgSetPosition msgSetPos(_owner->GetObjectID(), direction);
					_manager->SendMessage(&msgSetPos);

					RotationMessage msgRot(_owner->GetObjectID(), (float)degrees);
					_manager->SendMessage(&msgRot);
				}
				break;
			}

			return true;
		}

	sf::RenderWindow *_window;
	SceneManager *_manager;
	sf::Vector2f direction;
	double degrees;
};



class RenderComponent : public BaseComponent
{
public:

	RenderComponent(sf::RenderWindow* renderWindow, sf::Vector2f startingPos)
		: BaseComponent()
	{
		window = renderWindow;
		_sprite.setPosition(startingPos);
	}

	void loadTexture(std::string filename)
	{
		if(_texture.loadFromFile(filename) == false)
		{

		}
		else
		{
			_sprite.setTexture(_texture);
		}
	}


	bool SendMessage(BaseMessage* msg)
	{
		// Object has a switch for any messages it cares about
		switch(msg->m_messageTypeID)
		{

		case SetPosition:
			{               
				MsgSetPosition* msgSetPos = static_cast<MsgSetPosition*>(msg);
				_sprite.move(msgSetPos->pos);
			}
			break;
		case GetPosition:
			{
				MsgGetPosition* msgSetPos = static_cast<MsgGetPosition*>(msg);

				msgSetPos->pos = _sprite.getPosition();
			}
			break;

		case DrawMessage:
			{                   
				window->draw(_sprite);
			}
			break;

		default:
			return BaseComponent::SendMessage(msg);
		}

		return true;
	}

	sf::RenderWindow *window;
	sf::Sprite _sprite;
	sf::Texture _texture;
};






int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");

	// Create a scene manager/entity manager
	SceneManager *sceneMgr = new SceneManager();

	// Create an object for the player
	Object* myObj = sceneMgr->CreateObject(window);

	// Create an object for the NPC
	Object* myNPC = sceneMgr->CreateObject(window);

	// Player needs input, create the input component
	PlayerInputComponent* inputComp = new PlayerInputComponent(&window, sceneMgr);
	
	// Player needs to be rendered to the screen, create render component
	RenderComponent* renderComp = new RenderComponent(&window,sf::Vector2f(100,100));

	// Give the NPC some A.I, create A.I component
	WanderAIComponent* inputComp2 = new WanderAIComponent(&window, sceneMgr);

	// NPC also needs to be rendered to the screen, create render component
	RenderComponent* renderComp2 = new RenderComponent(&window,sf::Vector2f(200,200));

	// Set the renderComponents texture
	renderComp->loadTexture("Content/ball.png");

	// Attach render component to the object we made
	myObj->AddComponent(renderComp);

	// Attach input component to the object we made
	myObj->AddComponent(inputComp);

	// Set the renderComponents texture
	renderComp2->loadTexture("Content/ball.png");

	// Attach render component to the object we made
	myNPC->AddComponent(renderComp2);

	// Attach input component to the object we made
	myNPC->AddComponent(inputComp2);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

		for (int i = 0; i < 2; i++) {

			// Create a message telling the entity i to update
			Update msgUpdate(i);

			// Send the message to the manager
			sceneMgr->SendMessage(&msgUpdate);
        
			// Create a message telling the entity i to draw
			Draw msgDraw(i);

			// Send the message to the manager
			sceneMgr->SendMessage(&msgDraw);

		}

        window.display();
    }

    return 0;
}