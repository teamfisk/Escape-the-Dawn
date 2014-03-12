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
	auto bounds1 = m_World->GetComponent<Components::Bounds>(entity1, "Bounds");
	auto bounds2 = m_World->GetComponent<Components::Bounds>(entity2, "Bounds");

	float width = bounds1->VolumeVector.x;
	float height = bounds1->VolumeVector.y;
	float depth = bounds1->VolumeVector.z;

	GLfloat vertices1[] = {
		bounds1->Origin.x - width / 2, bounds1->Origin.y - height / 2, bounds1->Origin.z - depth / 2, 1.0,
		bounds1->Origin.x + width / 2, bounds1->Origin.y - height / 2, bounds1->Origin.z - depth / 2, 1.0,
		bounds1->Origin.x + width / 2, bounds1->Origin.y + height / 2, bounds1->Origin.z - depth / 2, 1.0,
		bounds1->Origin.x - width / 2, bounds1->Origin.y + height / 2, bounds1->Origin.z - depth / 2, 1.0,
		bounds1->Origin.x - width / 2, bounds1->Origin.y - height / 2, bounds1->Origin.z + depth / 2, 1.0,
		bounds1->Origin.x + width / 2, bounds1->Origin.y - height / 2, bounds1->Origin.z + depth / 2, 1.0,
		bounds1->Origin.x + width / 2, bounds1->Origin.y + height / 2, bounds1->Origin.z + depth / 2, 1.0,
		bounds1->Origin.x - width / 2, bounds1->Origin.y + height / 2, bounds1->Origin.z + depth / 2, 1.0,
	};

	GLuint vbo_vertices;
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
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

	

	return true;
}