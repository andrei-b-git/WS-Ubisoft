#pragma once

#include "common.h"
#include "Shader.h"
#include "SpriteManager.h"


class MyWindow {

private:
	static int width;
	static int height;
	const char* name;

	double prevTime;

	Shader *shader;

	SpriteManager *background;
	SpriteManager *effect_sprites;
	SpriteManager *crash_sprites;


	void _update_fps_counter();
	static void glfw_key_callback (GLFWwindow* _window, int key, int scancode, int action, int mods);
	static void glfw_window_size_callback (GLFWwindow* _window, int _width, int _height);
	void createSprites();
	void testKeys();
	void displayFrame(float deltaTime);

public:
	MyWindow(const char* _name, int _width, int _height);
	~MyWindow();
	void run();
};