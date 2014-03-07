#ifndef World_h__
#define World_h__

#include <stack>
#include <unordered_map>
#include <vector>
#include <string>

#include "Entity.h"
#include "Component.h"
#include "Factory.h"
#include "Components/Transform.h"
#include "Components/Input.h"
#include "Components/DirectionalLight.h"

#include "System.h"
#include "Systems/CollisionSystem.h"

class World
{
public:
	World();
	~World();

	virtual void RegisterComponents();
	virtual void RegisterSystems();

	EntityID CreateEntity(EntityID parent = 0);

	void RemoveEntity(EntityID entity);

	bool ValidEntity(EntityID entity);

	EntityID GetEntityParent(EntityID entity);

	template <class T>
	std::shared_ptr<T> AddComponent(EntityID entity, std::string componentType)
	{
		std::shared_ptr<T> component = std::shared_ptr<T>(static_cast<T*>(m_ComponentFactory.Create(componentType)));
		if (component == nullptr) {
			LOG_ERROR("Failed to attach invalid component \"%s\" to entity #%i", componentType.c_str(), entity);
			return nullptr;
		}

		m_ComponentsOfType[componentType].push_back(component);
		m_EntityComponents[entity][componentType] = component;
		return component;
	}

	std::shared_ptr<Component> AddComponent(EntityID entity, std::string componentType)
	{
		return AddComponent<Component>(entity, componentType);
	}

	template <class T>
	std::shared_ptr<T> GetComponent(EntityID entity, std::string componentType)
	{
		return std::static_pointer_cast<T>(m_EntityComponents[entity][componentType]);
	}

	/*std::vector<EntityID> GetEntityChildren(EntityID entity);*/

	void AddSystem(System* system);

	// Recursively update through the scene graph 
	void Update(double dt);

	void RecursiveUpdate(std::shared_ptr<System> system, double dt, EntityID parentEntity);

private:
	EntityID m_LastEntityID;
	std::stack<EntityID> m_RecycledEntityIDs;
	// A bottom to top tree. A map of child entities to parent entities.
	std::unordered_map<EntityID, EntityID> m_EntityParents;
	
	ComponentFactory m_ComponentFactory;
	std::unordered_map<std::string, std::vector<std::shared_ptr<Component>>> m_ComponentsOfType;
	std::unordered_map<EntityID, std::map<std::string, std::shared_ptr<Component>>> m_EntityComponents;
	std::vector<std::shared_ptr<System>> m_Systems;

	EntityID GenerateEntityID();

	void RecycleEntityID(EntityID id);
};

#endif // World_h__