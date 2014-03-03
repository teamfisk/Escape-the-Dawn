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
			system->Update(dt, child, parent);
			RecursiveUpdate(system, dt, child);
		}
	}
}

void World::Update(double dt)
{
	for (auto system : m_Systems) {
		RecursiveUpdate(system, dt, 0);
	}
}

void World::AddSystem(System* system)
{

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

	m_Systems.push_back(std::make_shared<Systems::Collision>(this));
}