#include <stack>
#include <unordered_map>
#include <vector>
#include <string>

#include "Entity.h"
#include "Component.h"
#include "Components/Transform.h"

class World
{
public:
	World()
	{
		m_LastEntityID = 0;
	}

	EntityID CreateEntity(EntityID parent = 0)
	{
		EntityID newEntity = GenerateEntityID();
		m_SceneGraph.insert(std::pair<EntityID, EntityID>(newEntity, parent));
		return newEntity;
	}

	void RemoveEntity(EntityID entity)
	{
		m_SceneGraph.erase(entity);
		RecycleEntityID(entity);
	}

	bool ValidEntity(EntityID entity)
	{
		return m_SceneGraph.find(entity) != m_SceneGraph.end();
	}

	EntityID GetEntityParent(EntityID entity)
	{
		auto it = m_SceneGraph.find(entity);
		return it == m_SceneGraph.end() ? 0 : it->second;
	}

	std::shared_ptr<Component> AddComponent(EntityID entity, std::string componentType)
	{
		std::shared_ptr<Component> component = ComponentFactory::Instance()->Create(componentType);
		m_ComponentsOfType[componentType].push_back(component);
		m_EntityComponents[entity][componentType] = component;
	}

	/*std::vector<EntityID> GetEntityChildren(EntityID entity)
	{
		std::vector<EntityID> children;
		auto range = m_SceneGraph.equal_range(entity);
		for (auto it = range.first; it != range.second; ++it)
			children.push_back(it->second);
		return children;
	}*/

private:
	EntityID m_LastEntityID;
	std::stack<EntityID> m_RecycledEntityIDs;
	// A map of child entities to parent entities
	std::unordered_map<EntityID, EntityID> m_SceneGraph; 
	std::unordered_map<std::string, std::vector<std::shared_ptr<Component>>> m_ComponentsOfType;
	std::unordered_map<EntityID, std::map<std::string, std::shared_ptr<Component>>> m_EntityComponents;

	EntityID GenerateEntityID()
	{
		if (!m_RecycledEntityIDs.empty()) {
			EntityID id = m_RecycledEntityIDs.top();
			m_RecycledEntityIDs.pop();
			return id;
		} else {
			return ++m_LastEntityID;
		}
	}

	void RecycleEntityID(EntityID id)
	{
		m_RecycledEntityIDs.push(id);
	}
};