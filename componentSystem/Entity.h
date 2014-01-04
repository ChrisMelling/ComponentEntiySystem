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

#ifndef __ANAX_ENTITY_HPP__
#define __ANAX_ENTITY_HPP__

#include <type_traits>
#include <cstdint>
#include "Component.h"

namespace anax
{
	class World;
	

	class Entity
	{
	public:
		
		/// Default constructor
		Entity();
		
		/// \param world The World the entity belongs to
		/// \param id The designated ID of the Entity
		/// \note You should not call this ctor
		Entity(World& world, int id);
		

		
		/// Determines if this Entity handle is valid & able to be used.
		/// \note You should only use this for DEBUG builds
		///		  as checking if an Entity is valid may/may not
		///		  impact your performance.
		/// \return true if this Entity is valid, false otherwise
		bool isValid() const;
		
		/// \return The Entity's ID
		const int getId() const;
		
		/// \return The World that the Entity belongs to.
		/// \note This function will fail if the Entity is null.
		/// \see isNull() To check whether the Entity is null.
		World& getWorld() const;
		
		/// \return true if this Entity is activated
		bool isActivated() const;
		
		/// Activates this Entity
		void activate();
		
		/// Deactivates this Entity
		void deactivate();
		
		/// Kills this Entity
		/// \see World::killEntity for an alternate way to kill an Entity
		void kill();
		
		/// Adds a component to the Entity
		/// \tparam The type of component you wish to add
		/// \param component The component you wish to add
		/// \note component must be dynamically allocated with new, as
		/// it is stored as a unique_ptr. I may change this in the future
		/// by adding an option to alter how it's stored or something
		/// along those lines.
		/// \return The entity you added
		template <typename T>
		T& addComponent(T* component);
		
		/// Removes a component
		/// \tparam The type of component you wish to remove
		template <typename T>
		void removeComponent();
		
		/// Removes all the components attached to the Entity
		void removeAllComponents();
		
		/// Retrives a component from this Entity
		/// \tparam The type of component you wish to retrieve
		/// \return A pointer to the component
		template <typename T>
		T& getComponent() const;
		
		/// Determines if this Entity has a component or not
		/// \tparam The type of component you wish to check for
		/// \return true if this Entity contains a component
		template <typename T>
		bool hasComponent() const;
		
		/// Comparrision operator
		bool operator==(const Entity& entity) const;
		bool operator!=(const Entity& entity) const { return !operator==(entity); }
		
	private:
		
		// wrappers to add components
		// so I may call them from templated public interfaces
		void addComponent(BaseComponent* component, int componentTypeId);
		void removeComponent(int componentTypeId);
		BaseComponent& getComponent(int componentTypeId) const;
		bool hasComponent(int componentTypeId) const;
		
		
		/// The ID of the Entity
		int _id;
		
		/// The world that this Entity belongs to. This is guarenteed
		/// to not be null, as long as this entity is not null.
		/// \see isNull() To determine if the entity is null or not.
		World* _world;
		
		
		friend class World;
	};
	
	
	template <typename T>
	T& Entity::addComponent(T* component)
	{
		static_assert(std::is_base_of<BaseComponent, T>(), "T is not a component, cannot add T to entity");
		addComponent(component, T::GetTypeId());
		return *component;
	}
	
#ifdef ANAX_USE_VARIADIC_TEMPLATES

	template <typename T, typename... Args>
	T& Entity::addComponent(Args&&... args)
	{
		return addComponent<T>(new T{args...});
	}
	
#endif // ANAX_USE_VARIADIC_TEMPLATES

	template <typename T>
	void Entity::removeComponent()
	{
		static_assert(std::is_base_of<BaseComponent, T>(), "T is not a component, cannot remove T from entity");
		removeComponent(T::GetTypeId());
	}
	
	template <typename T>
	T& Entity::getComponent() const
	{
		static_assert(std::is_base_of<BaseComponent, T>(), "T is not a component, cannot retrieve T from entity");
		return static_cast<T&>(getComponent(T::GetTypeId()));
	}
	
	template <typename T>
	bool Entity::hasComponent() const
	{
		static_assert(std::is_base_of<BaseComponent, T>(), "T is not a component, cannot determine if entity has T");
		return hasComponent(T::GetTypeId());
	}
}

#endif // __ANAX_ENTITY_HPP__