
#ifndef __ANAX_COMPONENT_HPP__
#define __ANAX_COMPONENT_HPP__

#include <cstddef>
#include <vector>
#include <functional>

namespace anax
{
	class BaseComponent
	{
	public:
		BaseComponent();
		~BaseComponent();	
	};
	
	
	template <typename T>
	class Component
		: public BaseComponent
	{
	public:
		Component()
		virtual ~Component() = 0;	
	};

	typedef std::vector<std::reference_wrapper<BaseComponent>> ComponentArray;
}

#endif // __ANAX_COMPONENT_HPP__