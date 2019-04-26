#pragma once
#include "Mesh.h"
#include "Shader.h"
#include <Application.h>
#include <Gizmos.h>
#include "OBJMesh.h"
#include <Input.h>
#include "RenderTarget.h"
#include <iostream>

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
	//used to set up the camera
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;


	aie::Texture m_gridTexture;

	//shaders
	aie::ShaderProgram	m_shader;
	aie::ShaderProgram	m_postShader;


	Mesh				m_fullscreenMesh;
	Mesh				m_quadMesh;
	glm::mat4			m_quadTransform;

	aie::OBJMesh		m_spearMesh;
	glm::mat4			m_spearTransform;

	aie::RenderTarget	m_renderTarget;

	//light variables
	struct Light
	{
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
	//where multiple lights go
	Light				m_light;
	Light				m_light2;
	glm::vec3			m_ambientLight;

	//camera variables
	float xEye;
	float yEye;
	float zEye;

	float xCentre;
	float yCentre;
	float zCentre;

};


