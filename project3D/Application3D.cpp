#define GLM_FORCE_SWIZZLE
#define	GLM_ENABLE_EXPERIMENTAL

#include "Application3D.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/mat4x4.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

Application3D::Application3D() {

}

Application3D::~Application3D() {

}

mat4 tank_rot(1);
mat4 turret_rot(1);
mat4 barrel_rot(1);
mat4 tank_trans(1);
mat4 turret_trans(1);
mat4 barrel_trans(1);

glm::mat4 world(1);
glm::mat4 tank_base = world;
glm::mat4 base_turret = tank_base * turret_trans * turret_rot;
glm::mat4 turret_barrel = base_turret * barrel_trans * barrel_rot;

bool Application3D::startup() {

	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
		getWindowWidth() / (float)getWindowHeight(),
		0.1f, 1000.f);

	turret_trans = glm::translate(vec3(0, .2, 0));
	barrel_trans = glm::translate(vec3(.6, .2, 0));
	barrel_rot = glm::rotate(1.70f, vec3(0, 0, 1));
	turret_rot = glm::rotate(4.7f, vec3(0, 1, 0));

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
float degrees2 = 90.0f;

//old bodies
//vec3 tankBody(0, 0, 0);
//vec3 sphereBody(0, 0.5, 0);
//vec3 cylinderBody(0, 1, 1.7);

/*vec3 camera(15, 15, 0);*/
float camera = .5f;

void Application3D::update(float deltaTime) {

	//glm::mat4 michealisatampon = glm::mat4(
	//	1.0f, 1.0f, 1.0f, 1.0f,
	//	2.0f, 2.0f, 2.0f, 2.0f,
	//	3.0f, 3.0f, 3.0f, 3.0f,
	//	4.0f, 4.0f, 4.0f, 4.0f
	//	);
	
	tank_base = world * tank_trans * tank_rot;
	base_turret = tank_base * turret_trans * turret_rot;
	turret_barrel = base_turret * barrel_trans * barrel_rot;

	vec3 forward = tank_base[2]*(10 * deltaTime);

	// query time since application started
	float time = getTime();

	// rotate camera
	m_viewMatrix = glm::lookAt(vec3(glm::sin(camera) * 20, 10, glm::cos(camera) * 15),
		vec3(0), vec3(0, 1, 0));

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	//const glm::mat4* cylinderRotation = new glm::mat4(
	//1.0f, .0f,			.0f,		   .0f,
	//0.0f, cos(degrees), sin(degrees), .0f,
	//.0f, -sin(degrees), cos(degrees),   0.0f,
	//.0f, .0f,		   .0f,			   1.0f);

	//const glm::mat4* squareRotation = new glm::mat4(
	//cos(degrees2), 0.0f, -sin(degrees2), .0f,
	//0.0f,		   1.0f, 0.0f,			 .0f,
	//sin(degrees2), 0.0f, cos(degrees2),  .0f,
	//.0f,		   .0f,	 0.0f,			 1.0f);
	//
	//const glm::mat4* sphereRotation = new glm::mat4(
	//cos(degrees2), 0.0f, -sin(degrees2), .0f,
	//0.0f,		   1.0f, 0.0f,			 .0f,
	//sin(degrees2), 0.0f, cos(degrees2),  .0f,
	//.0f,		   .0f,	 0.0f,			 1.0f);

	grid();

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	// demonstrate a few shapes
	Gizmos::addAABBFilled(tank_base[3], vec3(1, .5, 1.5), vec4(0, 0.5f, 1, 0.25f), &tank_base);
	Gizmos::addSphere(base_turret[3], 1, 8, 8, vec4(1, 0, 0, 0.5f), &base_turret);
	Gizmos::addCylinderFilled(turret_barrel[3], .2f, 1, 20, vec4(1, 0, 0, 0.5f), &turret_barrel);

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	////////////////////////////////////////////

		//Rotates the barrel
	if (input->isKeyDown(aie::INPUT_KEY_UP))
	{
		barrel_rot = barrel_rot * glm::rotate(.1f, vec3(0, 0, 1));
	}
	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		barrel_rot = barrel_rot * glm::rotate(-.1f, vec3(0, 0, 1));
	}

	//Rotates the body and sphere
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		turret_rot = turret_rot * glm::rotate(.1f, vec3(0, 1, 0));
	}
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		turret_rot = turret_rot * glm::rotate(-.1f, vec3(0, 1, 0));
	}

	////////////////////////////////////////////

		//Tank body movement
	if (input->isKeyDown(aie::INPUT_KEY_W))
	{
		tank_trans = tank_trans * glm::translate(forward);

		/*tankBody = tankBody + moveUp * 5.0f * deltaTime;
		sphereBody = sphereBody + moveUp * 5.0f * deltaTime;
		cylinderBody = cylinderBody + moveUp * 5.0f * deltaTime;*/
	}

	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		tank_trans = tank_trans * glm::translate(-forward);

		/*tankBody = tankBody - moveUp * 5.0f * deltaTime;
		sphereBody = sphereBody - moveUp * 5.0f * deltaTime;
		cylinderBody = cylinderBody - moveUp * 5.0f * deltaTime;*/
	}

	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		tank_rot = tank_rot * glm::rotate(.1f, vec3(0, 1, 0));
	}

	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		tank_rot = tank_rot * glm::rotate(-.1f, vec3(0, 1, 0));
	}

	if (input->isKeyDown(aie::INPUT_KEY_Q))
	{
		camera += 2 * deltaTime;
	}

	if (input->isKeyDown(aie::INPUT_KEY_E))
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