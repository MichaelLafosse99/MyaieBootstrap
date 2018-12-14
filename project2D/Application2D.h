#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <Vector2.h>

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Texture*		m_vectorSpriteUp;
	//aie::Texture*		m_vectorSpriteDown;
	//aie::Texture*		m_vectorSpriteLeft;
	//aie::Texture*		m_vectorSpriteRight;

	aie::Font*			m_font; 

	Vector2 bob;

	Vector2 Up;
	Vector2 Down;
	Vector2 Left;
	Vector2 Right;

	int op;

	float m_cameraX, m_cameraY;
	float m_timer;
};