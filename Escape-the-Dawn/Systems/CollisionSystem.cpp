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

bool Systems::CollisionSystem::Intersects(EntityID entity1, EntityID entity2)
{
	auto collisionComponent1 = m_World->GetComponent<Components::Collision>(entity1, "Collision");
	if(collisionComponent1 == nullptr)
		return false;
	auto collisionComponent2 = m_World->GetComponent<Components::Collision>(entity2, "Collision");
	if(collisionComponent2 == nullptr)
		return false;
	collisionComponent1->CollidingEntities.clear();
	collisionComponent2->CollidingEntities.clear();
	
	auto bounds1 = m_World->GetComponent<Components::Bounds>(entity1, "Bounds");
	
	auto bounds2 = m_World->GetComponent<Components::Bounds>(entity2, "Bounds");
	

	glm::vec3 max1 = glm::vec3(bounds1->Origin.x + bounds1->VolumeVector.x, bounds1->Origin.y + bounds1->VolumeVector.y, bounds1->Origin.z + bounds1->VolumeVector.z); 
	glm::vec3 min1 = glm::vec3(bounds1->Origin.x - bounds1->VolumeVector.x, bounds1->Origin.y - bounds1->VolumeVector.y, bounds1->Origin.z - bounds1->VolumeVector.z); 
	glm::vec3 max2 = glm::vec3(bounds2->Origin.x + bounds2->VolumeVector.x, bounds2->Origin.y + bounds2->VolumeVector.y, bounds2->Origin.z + bounds2->VolumeVector.z); 
	glm::vec3 min2 = glm::vec3(bounds2->Origin.x - bounds2->VolumeVector.x, bounds2->Origin.y - bounds2->VolumeVector.y, bounds2->Origin.z - bounds2->VolumeVector.z);



	for(int z = min1.z; z < max1.z; z++)
		if (z > min2.z && z < max2.z)
			for (int y = min1.y; y < max1.y; y++)
				if(y > min2.y && y < max2.y)
					for (int x = min1.x; x < max1.x; x++)
						if(x > min2.x && x < max2.x)
						{
							//vi har en kollision!!! kanske :(
							collisionComponent1->CollidingEntities.push_back(entity2);
							collisionComponent2->CollidingEntities.push_back(entity1);
							return true;
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