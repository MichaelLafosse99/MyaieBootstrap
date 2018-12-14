#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {

	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");
	m_vectorSpriteUp = new aie::Texture("./textures/vector sprite.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);

	bob = { 100,100 };

	Up = { 0, 5 };
	Down = { 0, -5 };
	Left = { -5, 0 };
	Right = { 5,0 };

	op;

	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	return true;
}

void Application2D::shutdown() {
	
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;
	

	// input example
	aie::Input* input = aie::Input::getInstance();

	// use arrow keys to move camera
	if (input->isKeyDown(aie::INPUT_KEY_UP))
		m_cameraY += 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		m_cameraY -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		m_cameraX -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		m_cameraX += 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_W))
	{
		bob = bob + Up;
		m_2dRenderer->setUVRect(int(m_timer * 10) % 9 / 9.0f, 0, 1.f / 9, 1.f / 4);
		op = 1;
	}

	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		bob = bob + Down;
		m_2dRenderer->setUVRect(int(m_timer * 10) % 9 / 9.0f, 0.50, 1.f / 9, 1.f / 4);
		op = 2;
	}

	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		bob = bob + Left;
		m_2dRenderer->setUVRect(int(m_timer * 10) % 9 / 9.0f, 0.25, 1.f / 9, 1.f / 4);
		op = 3;
	}

	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		bob = bob + Right;
		m_2dRenderer->setUVRect(int(m_timer * 10) % 9 / 9.0f, 0.75, 1.f / 9, 1.f / 4);
		op = 4;
	}

	switch (op)
	{
	case 1:
		if (input->isKeyUp(aie::INPUT_KEY_W))
		{
			m_2dRenderer->setUVRect(0, 0, 1.f / 9, 1.f / 4);
		}
		break;
	case 2:
		if (input->isKeyUp(aie::INPUT_KEY_S))
		{
			m_2dRenderer->setUVRect(0, 0.50, 1.f / 9, 1.f / 4);
		}
		break;
	case 3:
		if (input->isKeyUp(aie::INPUT_KEY_A))
		{
			m_2dRenderer->setUVRect(0, 0.25, 1.f / 9, 1.f / 4);
		}
		break;
	default:
	case 4:
		if (input->isKeyUp(aie::INPUT_KEY_D))
		{
			m_2dRenderer->setUVRect(0, 0.75, 1.f / 9, 1.f / 4);
		}
		break;
	}

	// exit the application
	//if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
	//	quit();
}

void Application2D::draw() {

	//// wipe the screen to the background colour
	//clearScreen();

	//// set the camera position before we begin rendering
	//m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();
	
	m_2dRenderer->drawSprite(m_vectorSpriteUp, bob.Getx(), bob.Gety(), 100, 100);

	//// demonstrate animation
	////m_2dRenderer->setUVRect(int(m_timer) % 8 / 8.0f, 0, 1.f / 8, 1.f / 8);
	//m_2dRenderer->drawSprite(m_texture, 200, 200, 100, 100);

	//// demonstrate spinning sprite
	//m_2dRenderer->setUVRect(0,0,1,1);
	//m_2dRenderer->drawSprite(m_shipTexture, 200, 200, 0, 0, 0, 1);

	//// draw a thin line
	//m_2dRenderer->drawLine(300, 300, 600, 400, 2, 1);

	//// draw a moving purple circle
	//m_2dRenderer->setRenderColour(1, 0, 1, 1);
	//m_2dRenderer->drawCircle(sin(m_timer) * 100 + 600, 150, 50);

	//// draw a rotating red box
	//m_2dRenderer->setRenderColour(1, 0, 0, 1);
	//m_2dRenderer->drawBox(600, 500, 60, 20, m_timer);

	//// draw a slightly rotated sprite with no texture, coloured yellow
	//m_2dRenderer->setRenderColour(1, 1, 0, 1);
	//m_2dRenderer->drawSprite(nullptr, 400, 400, 50, 50, 3.14159f * 0.25f, 1);
	
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}