#pragma once
#include "Mesh.h"
#include "Shader.h"
#include <Application.h>
#include <Gizmos.h>
#include "OBJMesh.h"
#include <Input.h>

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


	aie::Texture m_gridTexture;

	aie::ShaderProgram	m_shader;

	Mesh				m_quadMesh;
	glm::mat4			m_quadTransform;

	aie::OBJMesh		m_spearMesh;
	glm::mat4			m_spearTransform;

	struct Light
	{
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
	Light				m_light;
	Light				m_light2;
	glm::vec3			m_ambientLight;

	float xEye;
	float yEye;
	float zEye;

	float xCentre;
	float yCentre;
	float zCentre;

	float m_timer;
};


