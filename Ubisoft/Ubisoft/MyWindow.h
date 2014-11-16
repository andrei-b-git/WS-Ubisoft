#pragma once

#include "common.h"
#include "Shader.h"
#include "SpriteManager.h"


class MyWindow {

private:
	static int width;
	static int height;
	const char* name;

	double currentTime;

	Shader *shader;

	SpriteManager *background;
	SpriteManager *crash_sprites;
	SpriteManager *effect_sprites;
	SpriteManager *UI_sprites;


	void _update_fps_counter();
	static void glfw_key_callback (GLFWwindow* _window, int key, int scancode, int action, int mods);
	static void glfw_window_size_callback (GLFWwindow* _window, int _width, int _height);
	void MyWindow::createDefaultSprites();
	void createWave(double time);
	void testKeys(double time);
	void handleCollision(double time);
	void update_score();
	void update_rockets();

public:
	MyWindow(const char* _name, int _width, int _height);
	~MyWindow();
	void run();
};