#ifndef COMPONENT_HPP
#define COMPONENT_HPP

//STD
#include <vector>
#include <string>
#include <memory>

//3RD

//SELF
#include "Constants.hpp"

class Entity;

class Component
{
public:
    Component();
    virtual ~Component();
	    std::shared_ptr<Entity>& createEnt();
    constant::Comp type;
	
protected:
    Entity *mpOwnerEntity;

};

#endif
