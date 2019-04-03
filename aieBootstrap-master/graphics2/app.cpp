#include "app.h"



App::App()
{
}


App::~App()
{
}

bool App::startup()
{
	xTest = 10;
	yTest = 10;
	zTest = 10;

	xLook = 0;
	yLook = 0;
	zLook = 0;

	setBackgroundColour(0.25f, 0.25f, 0.25f);

	//initialise gizmo primitive counts
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	//create simple camera transforms
	m_viewMatrix = glm::lookAt(glm::vec3(10), glm::vec3(0,5,0), glm::vec3(0, 1, 0)); /*(70)(0,45,0)(0,1,0) for the spear / (10)(0,0,0)(0,1,0) for quad*/
//	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f);

	//shader
	m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");
	
	if (m_shader.link() == false)
	{
		printf("Shader Error: %s\n", m_shader.getLastError());
		return false;
	}

	if (m_gridTexture.load("./textures/numbered_grid.tga") == false)
	{
		printf("Failed to load texture!\n");
		return false;
	}

	if (m_spearMesh.load("./soulspear/soulspear.obj", true, true) == false)
	{
		printf("soulspear Mesh Error!\n");
		return false;
	}

	//light setup
	m_light.diffuse = { 1,1,0 };
	m_light.specular = { 1,1,0 };
	m_ambientLight = { 0.25f,0.25f,0.25f };

	m_quadMesh.initialiseQuad();

	m_quadTransform =
	{
		1,0 ,0 ,0,
		0 ,1,0 ,0,
		0 ,0 ,1,0,
		0 ,0 ,0 ,1
	};
	return true;
}

void App::shutdown()
{
}

void App::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		printf("back\n");
		xTest += 0.2f;
		xLook += 0.2f;
		zTest += 0.2f;
		zLook += 0.2f;
	}
	if (input->isKeyDown(aie::INPUT_KEY_W))
	{
		printf("forward\n");
		xTest -= 0.2f;
		xLook -= 0.2f;
		zTest -= 0.2f;
		zLook -= 0.2f;
	}
	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		printf("left\n");
		zTest += 0.2f;
		zLook += 0.2f;
		xTest -= 0.2f;
		xLook -= 0.2f;
	}
	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		printf("right\n");
		zTest -= 0.2f;
		zLook -= 0.2f;
		xTest += 0.2f;
		xLook += 0.2f;
	}
	if (input->isKeyDown(aie::INPUT_KEY_E))
	{
		printf("up\n");
		yTest += 0.2f;
		yLook += 0.2f;
	}
	if (input->isKeyDown(aie::INPUT_KEY_Q))
	{
		printf("down\n");
		yTest -= 0.2f;
		yLook -= 0.2f;
	}

	//create simple camera transforms
	m_viewMatrix = glm::lookAt(glm::vec3(xTest,yTest,zTest), glm::vec3(xLook, yLook, zLook), glm::vec3(0, 1, 0)); /*(70)(0,45,0)(0,1,0) for the spear / (10)(0,0,0)(0,1,0) for quad*/

	float time = getTime();

	m_light.direction = glm::normalize(glm::vec3(glm::cos(time * 2), glm::sin(time * 2), 0));

}

void App::draw()
{

	//wipe the screen to the background colour
	clearScreen();


	//update perspective in case the window is resized
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f);
	

	//bind shader
	m_shader.bind();

	//bind camera position
	m_shader.bindUniform("cameraPosition", glm::vec3(glm::inverse(m_viewMatrix)[3]));

	//bind light
	m_shader.bindUniform("Ia", m_ambientLight);
	m_shader.bindUniform("Id", m_light.diffuse);
	m_shader.bindUniform("Is", m_light.specular);
	m_shader.bindUniform("LightDirection", m_light.direction);

	//bind transform
	auto pvm = m_projectionMatrix * m_viewMatrix * m_quadTransform;
	m_shader.bindUniform("ProjectionViewModel", pvm);
	
	//bind transforms for lighting 
	m_shader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_quadTransform)));

	
	m_shader.bindUniform("diffuseTexture", 0);

	//bind texture to a specified location
	m_gridTexture.bind(0);


	//draw things here
	m_spearMesh.draw();
//	m_quadMesh.draw();




	//draw 3d gizmos
	aie::Gizmos::draw(m_projectionMatrix * m_viewMatrix);

	//draw 2d gizmos using orthagonal projection matrix
	aie::Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());


}
