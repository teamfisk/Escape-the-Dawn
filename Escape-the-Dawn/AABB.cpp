#include "AABB.h"

AABB::AABB(glm::vec3 _volumeVector, glm::vec3 _origin)
{
	volumeVector = _volumeVector;
	origin = _origin;

	CreateBB();
}

void AABB::CreateBB()
{
	// Cube 1x1x1, centered on origin
	GLfloat vertices[] = {
		origin.x - 0.5, origin.y - 0.5, origin.z - 0.5, 1.0,
		origin.x + 0.5, origin.y - 0.5, origin.z - 0.5, 1.0,
		origin.x + 0.5, origin.y + 0.5, origin.z - 0.5, 1.0,
		origin.x - 0.5, origin.y + 0.5, origin.z - 0.5, 1.0,
		origin.x - 0.5, origin.y - 0.5, origin.z + 0.5, 1.0,
		origin.x + 0.5, origin.y - 0.5, origin.z + 0.5, 1.0,
		origin.x + 0.5, origin.y + 0.5, origin.z + 0.5, 1.0,
		origin.x - 0.5, origin.y + 0.5, origin.z + 0.5, 1.0,
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

	glm::vec3 size = glm::vec3(glm::abs(origin.x-volumeVector.x), glm::abs(origin.y-volumeVector.y), glm::abs(origin.z-volumeVector.z));
	glm::mat4 transform =  glm::translate(glm::mat4(1), origin) * glm::scale(glm::mat4(1), size);

	for (int i = 0; i < )
}