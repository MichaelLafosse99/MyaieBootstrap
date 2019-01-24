#include "Application3D.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

Application3D::Application3D() {

}

Application3D::~Application3D() {

}

bool Application3D::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
										  getWindowWidth() / (float)getWindowHeight(),
										  0.1f, 1000.f);

	return true;
}

void Application3D::shutdown() {

	Gizmos::destroy();
}

void grid()
{
	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}
}

float degrees = 90.0f;
float degrees2 = 0.0f;

	vec3 tankBody(0, 0, 0);
	vec3 sphereBody(0, 0.5, 0);
	vec3 cylinderBody(0, 1, 1.7);

	/*vec3 camera(15, 15, 0);*/
	float camera = .5f;

void Application3D::update(float deltaTime) {

	// query time since application started
	float time = getTime();

	// rotate camera
	m_viewMatrix = glm::lookAt(vec3(glm::sin(camera) *20, 10, glm::cos(camera) * 15),
							   vec3(0), vec3(0, 1, 0));

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	const glm::mat4* cylinderRotation = new glm::mat4(
	1.0f, .0f,			.0f,		   .0f,
	0.0f, cos(degrees), -sin(degrees), .0f,
	.0f, sin(degrees), cos(degrees),   0.0f,
	.0f, .0f,		   .0f,			   1.0f);

	const glm::mat4* squareRotation = new glm::mat4(
	cos(degrees2), 0.0f, -sin(degrees2), .0f,
	0.0f,		   1.0f, 0.0f,			 .0f,
	sin(degrees2), 0.0f, cos(degrees2),  .0f,
	.0f,		   .0f,	 0.0f,			 1.0f);
	
	const glm::mat4* sphereRotation = new glm::mat4(
	cos(degrees2), 0.0f, -sin(degrees2), .0f,
	0.0f,		   1.0f, 0.0f,			 .0f,
	sin(degrees2), 0.0f, cos(degrees2),  .0f,
	.0f,		   .0f,	 0.0f,			 1.0f);

	grid();

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	// demonstrate a few shapes
	Gizmos::addAABBFilled(tankBody, vec3(1,.5,1.5), vec4(0, 0.5f, 1, 0.25f), squareRotation);
	Gizmos::addSphere(sphereBody, 1, 8, 8, vec4(1, 0, 0, 0.5f), sphereRotation);
	Gizmos::addCylinderFilled(cylinderBody, .2f, 1, 20, vec4(1, 0, 0, 0.5f), cylinderRotation);

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

////////////////////////////////////////////

	//Rotates the barrel
	if (input->isKeyDown(aie::INPUT_KEY_UP))
	{
		degrees += 5 * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		degrees -= 5 * deltaTime;
	}

	//Rotates the body and sphere
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		degrees2 += 5 * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		degrees2 -= 5 * deltaTime;
	}
	
////////////////////////////////////////////

	//Tank body movement
	if (input->isKeyDown(aie::INPUT_KEY_W))
	{
		vec3 moveUp(glm::sin(degrees2), 0, cos(degrees2));

		tankBody = tankBody + moveUp * 5.0f * deltaTime;
		sphereBody = sphereBody + moveUp * 5.0f * deltaTime;
		cylinderBody = cylinderBody + moveUp * 5.0f * deltaTime;
	}

	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		vec3 moveUp(glm::sin(degrees2), 0, cos(degrees2));

		tankBody = tankBody - moveUp * 5.0f * deltaTime;
		sphereBody = sphereBody - moveUp * 5.0f * deltaTime;
		cylinderBody = cylinderBody - moveUp * 5.0f * deltaTime;
	}

	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		

		camera += 2 * deltaTime;

	}

	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		

		camera += -2 * deltaTime;

	}

////////////////////////////////////////////
}

void Application3D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective in case window resized
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
										  getWindowWidth() / (float)getWindowHeight(),
										  0.1f, 1000.f);

	// draw 3D gizmos
	Gizmos::draw(m_projectionMatrix * m_viewMatrix);

	// draw 2D gizmos using an orthogonal projection matrix (or screen dimensions)
	Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());
}

void Application3D::store()
{
	Gizmos::addRing(vec3(5, 0, -5), 1, 1.5f, 8, vec4(0, 1, 0, 1));
	Gizmos::addDisk(vec3(-5, 0, 5), 1, 16, vec4(1, 1, 0, 1));
	Gizmos::addArc(vec3(-5, 0, -5), 0, 2, 1, 8, vec4(1, 0, 1, 1));

	/*mat4 t = glm::rotate(mat4(1), time, glm::normalize(vec3(1, 1, 1)));
	t[3] = vec4(-2, 0, 0, 1);
	Gizmos::addCylinderFilled(vec3(0), 0.5f, 1, 5, vec4(0, 1, 1, 1), &t);*/

	// demonstrate 2D gizmos
	Gizmos::add2DAABB(glm::vec2(getWindowWidth() / 2, 100),
		glm::vec2(getWindowWidth() / 2 * (fmod(getTime(), 3.f) / 3), 20),
		vec4(0, 1, 1, 1));
}