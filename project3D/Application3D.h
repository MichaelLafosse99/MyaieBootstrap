#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include "Vector3.h"
class Application3D : public aie::Application {
public:

	Application3D();
	virtual ~Application3D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void store();

protected:

	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
};