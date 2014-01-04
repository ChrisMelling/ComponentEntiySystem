


///
/// anax
/// An open source C++ entity system.
///
/// Copyright (C) 2013 Miguel Martin (miguel.martin7.5@hotmail.com)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///

#ifndef __ANAX_WORLD_HPP__
#define __ANAX_WORLD_HPP__

#include <vector>
#include <unordered_map>
#include <type_traits>


class World
{
public:
		
	static const std::size_t DEFAULT_ENTITY_POOL_SIZE = 1000;
		
	/// Default Constructor
	World();
		
		
	template <typename TSystem>
	void addSystem(TSystem& system) { static_assert(std::is_base_of<BaseSystem, TSystem>(), "Template argument does not inherit from BaseSystem"); addSystem(system, TSystem::GetTypeId()); }
		
	template <typename TSystem>
	void removeSystem() { static_assert(std::is_base_of<BaseSystem, TSystem>(), "Template argument does not inherit from BaseSystem"); removeSystem(TSystem::GetTypeId()); }
		
	void removeAllSystems();
		
	Entity createEntity();
		
	std::vector<Entity> createEntities(std::size_t amount);
		
	void killEntity(Entity& entity);
		

	void killEntities(std::vector<Entity>& entities);
		

	void activateEntity(Entity& entity);
		

	void deactivateEntity(Entity& entity);

	bool isActivated(const Entity& entity) const;
		

	bool isValid(const Entity& entity) const;
		

	void refresh();
		

	std::size_t getAliveEntityCount() const;
		
private:
		
	/// Describes an array of Systems for storage within the world
	/// The index is the type ID of the system,
	/// thus systems of the same type can not be stored
	/// in the same World object.
	typedef std::unordered_map<int, BaseSystem*> SystemArray;
		
	/// Describes an array of Entities
	typedef std::vector<Entity> EntityArray;
		
		
	/// The amount of entities that are alive within the world
	std::size_t _aliveEntityCount;
		
	/// Systems attached with the world.
	SystemArray _systems;
			
		
	void checkForResize();
	void resize(std::size_t amount);
		
	void addSystem(BaseSystem& system);
	void removeSystem(int systemTypeId);		
		
		
	// to access components
	friend class Entity;
};


#endif // __ANAX_WORLD_HPP__
