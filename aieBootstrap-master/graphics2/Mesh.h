#pragma once
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <gl_core_4_4.h>
#include <Texture.h>
class Mesh
{	
public:
	Mesh() : triCount(0), vao(0), vbo(0),ibo(0) {}
	virtual ~Mesh();

	struct Vertex {
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;

	};
	//generate buffers, bind vertex array and buffer, then fill the buffer, bind indicies if there are any, and then unbind the buffer
	void initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount = 0, unsigned int* indices = nullptr);
	
	//generates buffers, binds vertex array and buffer, fill vert buffer with defined verts for 2 triangles, unbind the buffer  
	void initialiseQuad();
	//does the same as initialiseQuad but with different vertices
	void initialiseFullscreenQuad();

	//rebinds vao then either calls glDrawArrays or glDrawElements
	virtual void draw();


protected:
	//stores unsigned ints for vao vbo and ibo. also with aditional unsigned ints storing how many triangles out mesh has
	unsigned int triCount;
	unsigned int vao, vbo, ibo;
};

