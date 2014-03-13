#include "CollisionSystem.h"
#include "World.h"

void Systems::CollisionSystem::UpdateEntity(double dt, EntityID entity, EntityID parent)
{
	if (parent != 0)
	{
		auto transform = m_World->GetComponent<Components::Transform>(entity, "Transform");
		auto parentTransform = m_World->GetComponent<Components::Transform>(parent, "Transform");

		transform->Position[0] += parentTransform->Position[0];
		transform->Position[1] += parentTransform->Position[1];
		transform->Position[2] += parentTransform->Position[2];
	}

	auto entities = m_World->GetEntities();

	for (auto pair : *entities) {
		EntityID entity2 = pair.first;
		EntityID parent2 = pair.second;

		// Check if entity2 is a child of entity
		/*auto currentParent = parent;
		bool childOfEntity2 = false;
		while (currentParent != 0) {
			if (currentParent == entity2) {
				childOfEntity2 = true;
				break;
			}
			currentParent = entities[currentParent];
		}
		if (childOfEntity2)
			continue;*/

		// Check if we're the parent to entity2
	
		//pair.first, pair.second;
		if(entity == entity2)
			break;
		Intersects(entity, entity2);
	}
}

void Systems::CollisionSystem::Intersects(EntityID aEntity, EntityID bEntity)
{
	auto aTransform = m_World->GetComponent<Components::Transform>(aEntity, "Transform");
	if(aTransform == nullptr)
		return;
	auto bTransform = m_World->GetComponent<Components::Transform>(bEntity, "Transform");
	if(bTransform == nullptr)
		return;

	auto aCollisionComponent = m_World->GetComponent<Components::Collision>(aEntity, "Collision");
	if(aCollisionComponent == nullptr)
		return;
	auto bCollisionComponent = m_World->GetComponent<Components::Collision>(bEntity, "Collision");
	if(bCollisionComponent == nullptr)
		return;

	
	auto aBounds = m_World->GetComponent<Components::Bounds>(aEntity, "Bounds");
	
	auto bBounds = m_World->GetComponent<Components::Bounds>(bEntity, "Bounds");

	glm::vec3 aPos = aTransform->Position + (aBounds->Origin * aTransform->Scale);
	glm::vec3 bPos = bTransform->Position + (bBounds->Origin * bTransform->Scale);

	glm::vec3 aMax = aPos + aBounds->VolumeVector * aTransform->Scale;
	glm::vec3 aMin = aPos - aBounds->VolumeVector * aTransform->Scale;
	glm::vec3 bMax = bPos + bBounds->VolumeVector * bTransform->Scale;
	glm::vec3 bMin = bPos - bBounds->VolumeVector * bTransform->Scale;

	if (aMin.x <= bMax.x && bMin.x <= aMax.x) {
		if (aMin.y <= bMax.y && bMin.y <= aMax.y) {
			if (aMin.z <= bMax.z && bMin.z <= aMax.z) {
				aCollisionComponent->CollidingEntities.push_back(aEntity);
				bCollisionComponent->CollidingEntities.push_back(bEntity);
				return;
			}
		}
	}
}

void Systems::CollisionSystem::CreateBoundingBox(std::shared_ptr<Components::Bounds> bounds)
{
	float width = abs(bounds->VolumeVector.x);
	float height = abs(bounds->VolumeVector.y);
	float depth = abs(bounds->VolumeVector.z);

	GLfloat vertices[] = {
		bounds->Origin.x - width, bounds->Origin.y - height, bounds->Origin.z - depth, 1.0,
		bounds->Origin.x + width, bounds->Origin.y - height, bounds->Origin.z - depth, 1.0,
		bounds->Origin.x + width, bounds->Origin.y + height, bounds->Origin.z - depth, 1.0,
		bounds->Origin.x - width, bounds->Origin.y + height, bounds->Origin.z - depth, 1.0,
		bounds->Origin.x - width, bounds->Origin.y - height, bounds->Origin.z + depth, 1.0,
		bounds->Origin.x + width, bounds->Origin.y - height, bounds->Origin.z + depth, 1.0,
		bounds->Origin.x + width, bounds->Origin.y + height, bounds->Origin.z + depth, 1.0,
		bounds->Origin.x - width, bounds->Origin.y + height, bounds->Origin.z + depth, 1.0,
	};

	GLuint vbo_vertices;
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLushort elements[] = {
		0, 1, 2, 3,
		4, 5, 6, 7,
		0, 4, 1, 5, 
		2, 6, 3, 7
	};
	GLuint ibo_elements;
	glGenBuffers(1, &ibo_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}