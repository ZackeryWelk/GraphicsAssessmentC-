#pragma once
#include "Mesh.h"
#include "Shader.h"
#include <Application.h>
#include <Gizmos.h>
#include "OBJMesh.h"

class App : public aie::Application
{
public:
	App();
	virtual ~App();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();


protected:
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	aie::ShaderProgram	m_shader;

	Mesh				m_quadMesh;
	glm::mat4			m_quadTransform;


	//aie::OBJMesh		m_bunnyMesh;
	//glm::mat4			m_bunnyTransform;
};


