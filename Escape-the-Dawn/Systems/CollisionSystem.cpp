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
	LOG_INFO("Updating entity %i with parent %i", entity, parent);
}

bool Systems::CollisionSystem::Intersects(EntityID aEntity, EntityID bEntity)
{
	auto aTransform = m_World->GetComponent<Components::Transform>(aEntity, "Transform");
	if(aTransform == nullptr)
		return false;
	auto bTransform = m_World->GetComponent<Components::Transform>(bEntity, "Transform");
	if(bTransform == nullptr)
		return false;

	auto aCollisionComponent = m_World->GetComponent<Components::Collision>(aEntity, "Collision");
	if(aCollisionComponent == nullptr)
		return false;
	auto bCollisionComponent = m_World->GetComponent<Components::Collision>(bEntity, "Collision");
	if(bCollisionComponent == nullptr)
		return false;
	aCollisionComponent->CollidingEntities.clear();
	bCollisionComponent->CollidingEntities.clear();
	
	auto aBounds = m_World->GetComponent<Components::Bounds>(aEntity, "Bounds");
	
	auto bBounds = m_World->GetComponent<Components::Bounds>(bEntity, "Bounds");

	glm::vec3 aMax = aTransform->Position + aBounds->Origin + aBounds->VolumeVector;
	glm::vec3 aMin = aTransform->Position + aBounds->Origin - aBounds->VolumeVector;
	glm::vec3 bMax = bTransform->Position + bBounds->Origin + bBounds->VolumeVector;
	glm::vec3 bMin = bTransform->Position + bBounds->Origin - bBounds->VolumeVector;

	if (aMin.x <= bMax.x && bMin.x <= aMax.x) {
		if (aMin.y <= bMax.y && bMin.y <= aMax.y) {
			if (aMin.z <= bMax.z && bMin.z <= aMax.z) {
				aCollisionComponent->CollidingEntities.push_back(aEntity);
				bCollisionComponent->CollidingEntities.push_back(bEntity);
				return true;
			}
		}
	}

	return false;
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