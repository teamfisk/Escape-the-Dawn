#include "Model.h"


Model::Model()
{
	temp_CreateModelShit();
	CreateBuffers();
}


void Model::temp_CreateModelShit()
{
	Vertices.push_back(0.0f);
	Vertices.push_back(0.0f);
	Vertices.push_back(2.0f);

	Vertices.push_back(0.0f);
	Vertices.push_back(1.0f);
	Vertices.push_back(2.0f);

	Vertices.push_back(1.0f);
	Vertices.push_back(0.0f);
	Vertices.push_back(2.0f);

	Normals.push_back();
	Normals.push_back();
	Normals.push_back();
}


void Model::CreateBuffers( std::vector<float> _Vertices, std::vector<float> _Normals, std::vector<float> _TextureCoords )
{
	glGenBuffers(1, &VertBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertBuffer);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size()*sizeof(float), Vertices.data, GL_STATIC_DRAW);
	GLERROR("GLEW: BufferFail1");

	glGenBuffers(1, &NormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, NormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, Normals.size()*sizeof(float), Normals.data, GL_STATIC_DRAW);
	GLERROR("GLEW: BufferFail2");

	glGenBuffers(1, &TextureCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, TextureCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, TextureCoords.size()*sizeof(float), TextureCoords.data, GL_STATIC_DRAW);
	GLERROR("GLEW: BufferFail3");

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	GLERROR("GLEW: BufferFail4");

	glBindBuffer(GL_ARRAY_BUFFER, VertBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	GLERROR("GLEW: BufferFail5");

	glBindBuffer(GL_ARRAY_BUFFER, NormalBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, TextureCoordBuffer);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	GLERROR("GLEW: BufferFail5");
}

