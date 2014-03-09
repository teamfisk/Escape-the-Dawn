#include "World.h"

void World::RecycleEntityID(EntityID id)
{
	m_RecycledEntityIDs.push(id);
}

EntityID World::GenerateEntityID()
{
	if (!m_RecycledEntityIDs.empty()) {
		EntityID id = m_RecycledEntityIDs.top();
		m_RecycledEntityIDs.pop();
		return id;
	} else {
		return ++m_LastEntityID;
	}
}

void World::RecursiveUpdate(std::shared_ptr<System> system, double dt, EntityID parentEntity)
{
	for (auto pair : m_EntityParents) {
		EntityID child = pair.first;
		EntityID parent = pair.second;

		if (parent == parentEntity)	{
			system->UpdateEntity(dt, child, parent);
			RecursiveUpdate(system, dt, child);
		}
	}
}

void World::Update(double dt)
{
	for (auto pair : m_Systems) {
		auto system = pair.second;
		system->Update(dt);
		RecursiveUpdate(system, dt, 0);
	}
}

//std::vector<EntityID> GetEntityChildren(EntityID entity);
//{
//	std::vector<EntityID> children;
//	auto range = m_SceneGraph.equal_range(entity);
//	for (auto it = range.first; it != range.second; ++it)
//		children.push_back(it->second);
//	return children;
//}

EntityID World::GetEntityParent(EntityID entity)
{
	auto it = m_EntityParents.find(entity);
	return it == m_EntityParents.end() ? 0 : it->second;
}

bool World::ValidEntity(EntityID entity)
{
	return m_EntityParents.find(entity) != m_EntityParents.end();
}

void World::RemoveEntity(EntityID entity)
{
	m_EntityParents.erase(entity);
	RecycleEntityID(entity);
}

EntityID World::CreateEntity(EntityID parent /*= 0*/)
{
	EntityID newEntity = GenerateEntityID();
	m_EntityParents.insert(std::pair<EntityID, EntityID>(newEntity, parent));
	return newEntity;
}

World::~World()
{

}

World::World()
{
	m_LastEntityID = 0;
}

void World::Initialize()
{
	RegisterSystems();
	RegisterComponents();
}

void World::RegisterSystems()
{

}

void World::RegisterComponents()
{
	
}

std::shared_ptr<Component> World::AddComponent(EntityID entity, std::string componentType)
{
	return AddComponent<Component>(entity, componentType);
}

void World::AddSystem(std::string systemType)
{
	m_Systems[systemType] = std::shared_ptr<System>(m_SystemFactory.Create(systemType));
}