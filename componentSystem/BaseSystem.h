
#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__

#include <vector>

#include "Entity.hpp"


/// \author Miguel Martin
class BaseSystem
{
public:
		
	/// Default constructor
	BaseSystem();
		
	/// Destructor
	virtual ~BaseSystem() = 0;
		
	///// \return The World attached to the System
	//World& getWorld() const;
	//	
	/// \return All the entities that are within the System
	std::vector<Entity> getEntities() const;
		
private:
		
	/// Initializes the system, when a world is succesfully
	/// attached to it.
	virtual void initialize() {}
		
	/// Occurs when an Entity is added to the system
	/// \param entity The Entity that is added to the system
	virtual void onEntityAdded(Entity& entity) {}
		
	/// Occurs when an Entity is removed to the system
	/// \param entity The Entity that is removed from the system
	virtual void onEntityRemoved(Entity& entity) {}
		
		
		
	/// Used to add an Entity to the system
	/// \param entity The Entity you wish to add
 	/// \note This is called by the attached World object
	void add(Entity& entity);
		
	/// Used to remove an Entity from the system
	/// \param entity The Entity you wish to remove
 	/// \note This is called by the attached World object
	void remove(Entity& entity);
		
	/// Used to set the attached World
	/// \param world The World to attach to
	/// \note This is called by the attached World object
	//void setWorld(World& world);
		
	/// The Entities that are attached to this system
	std::vector<Entity> _entities;
};

class System : public BaseSystem
{
public:
		
	/// Sets the ComponentFilter
	/// \param componentFilter The ComponentFilter you wish the system to have
	System() : BaseSystem() {}

};


#endif // __SYSTEM_HPP__