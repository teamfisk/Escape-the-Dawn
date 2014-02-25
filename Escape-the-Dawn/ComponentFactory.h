#ifndef ComponentFactory_h__
#define ComponentFactory_h__

#include <string>
#include <memory>
#include <functional>
#include <map>

struct Component;

#define REGISTER_COMPONENT(NAME, TYPE) \
	static ComponentRegistrar<TYPE> registrar(NAME);

template<class T>
class ComponentRegistrar
{
public:
	ComponentRegistrar(std::string name)
	{
		ComponentFactory::Instance()->Register(name, [](void) -> std::shared_ptr<Component> { return std::shared_ptr<Component>(new T()); });
	}
};

class ComponentFactory
{
public:
	static ComponentFactory* Instance()
	{
		static ComponentFactory factory;
		return &factory;
	}

	void Register(std::string name, std::function<std::shared_ptr<Component>(void)> factoryFunction)
	{
		m_FactoryFunctions[name] = factoryFunction;
	}

	std::shared_ptr<Component> Create(std::string name)
	{
		auto it = m_FactoryFunctions.find(name);
		if (it != m_FactoryFunctions.end())
			return it->second();
		else
			return nullptr;
	}

private:
	std::map<std::string, std::function<std::shared_ptr<Component>(void)>> m_FactoryFunctions;
};

#endif // ComponentFactory_h__