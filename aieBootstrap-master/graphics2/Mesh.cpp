#include "Mesh.h"





Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::initialise(unsigned int vertexCount, const Vertex * vertices, unsigned int indexCount, unsigned int * indices)
{

	assert(vao == 0);

	//generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	//bind vertex array aka a mech wrapper
	glBindVertexArray(vao);

	//bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	//enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//enable the second element as normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);

	//enable third element as texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);
	//bind indicies if there are any
	if (indexCount != 0)
	{
		glGenBuffers(1, &ibo);

		//bind vertex buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		//fill vertex buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		triCount = indexCount / 3;
	}
	else
	{
		triCount = vertexCount / 3;
	}

	//unbind buffer
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::initialiseQuad()
{
	//check that the mesh is ont initialised already
	assert(vao == 0);

	//generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	//bind vertex array aka mesh wrapper
	glBindVertexArray(vao);

	//bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//define 6 verticies for the 2 triangles

	Vertex vertices[6];
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };

	vertices[3].position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].position = { 0.5f, 0, 0.5f, 1 };
	vertices[5].position = { 0.5f, 0, -0.5f, 1 };


	vertices[0].normal = { 0, 1, 0, 0 };
	vertices[1].normal = { 0, 1, 0, 0 };
	vertices[2].normal = { 0, 1, 0, 0 };
	vertices[3].normal = { 0, 1, 0, 0 };
	vertices[4].normal = { 0, 1, 0, 0 };
	vertices[5].normal = { 0, 1, 0, 0 };


	vertices[0].texCoord = { 0, 1 };
	vertices[1].texCoord = { 1, 1 };
	vertices[2].texCoord = { 0, 0 };

	vertices[3].texCoord = { 0, 0 };
	vertices[4].texCoord = { 1, 1 };
	vertices[5].texCoord = { 1, 0 };
	
	
	
	//fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);


	//enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//enable the second element as normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);

	//enable third element as texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

	//unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//a quad has 2 triangles
	triCount = 2;

}

void Mesh::initialiseFullscreenQuad()
{
	assert(vao == 0);

	//generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	//bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);

	//bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//define vertices
	float vertices[] = {
		-1,1,//top left
		-1,-1,//bottom left
		 1,1,//top right
		-1,-1,//bottom left
		 1,-1,//bottom right
		 1,1//top right
	};

	//fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW);

	//enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, 0);

	//unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//quad has 2 triangles
	triCount = 2;
}

void Mesh::draw()
{
	glBindVertexArray(vao);
	//using indicies or just verticies?

	if (ibo != 0)
	{
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
	}
	else 
	{
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
	}
}
