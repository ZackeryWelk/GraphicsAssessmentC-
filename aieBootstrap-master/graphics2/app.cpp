#include "app.h"



App::App()
{
}


App::~App()
{
}

bool App::startup()
{
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	//initialise gizmo primitive counts
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	//create simple camera transforms
	m_viewMatrix = glm::lookAt(glm::vec3(10), glm::vec3(0), glm::vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f);

	m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");
	if (m_shader.link() == false)
	{
		printf("Shader Error: %s\n", m_shader.getLastError());
		return false;
	}

	m_quadMesh.initialiseQuad();

	//if (m_bunnyMesh.load("./stanford/bunny.obj") == false)
	//{
	//	printf("Bunny Mesh Error! \n");
	//	return false;
	//}

	//m_bunnyTransform =
	//{
	//	0.5f,0	 ,0		,0,
	//	0	,0.5f,0		,0,
	//	0	,0	 ,0.5f	,0,
	//	0	,0	 ,0		,1
	//};

	m_quadTransform =
	{
		10,0 ,0 ,0,
		0 ,10,0 ,0,
		0 ,0 ,10,0,
		0 ,0 ,0 ,1
	};
	return true;
}

void App::shutdown()
{
}

void App::update(float deltaTime)
{

}

void App::draw()
{

	//wipe the screen to the background colour
	clearScreen();


	//update perspective in case the window is resized
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f);


	//bind shader
	m_shader.bind();



	//bind transform

	auto pvm = m_projectionMatrix * m_viewMatrix * m_quadTransform;
	//auto pvmb = m_projectionMatrix * m_viewMatrix * m_bunnyTransform;

	m_shader.bindUniform("ProjectionViewModel", pvm);
	//m_shader.bindUniform("ProjectionViewModel", pvmb);



	//draw things here

	m_quadMesh.draw();
	//m_bunnyMesh.draw();




	//draw 3d gizmos
	aie::Gizmos::draw(m_projectionMatrix * m_viewMatrix);

	//draw 2d gizmos using orthagonal projection matrix
	aie::Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());


}
