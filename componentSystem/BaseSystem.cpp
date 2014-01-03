
#include "BaseSystem.h"

#include <algorithm>

BaseSystem::BaseSystem()
{

}
	

BaseSystem::~BaseSystem()
{
}

	
std::vector<Entity> BaseSystem::getEntities() const
{
	return _entities;
}
	

void BaseSystem::add(Entity &entity)
{
	_entities.push_back(entity);
	onEntityAdded(entity);
}
	
void BaseSystem::remove(Entity &entity)
{
	//_entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
		
	onEntityRemoved(entity);
}
	
