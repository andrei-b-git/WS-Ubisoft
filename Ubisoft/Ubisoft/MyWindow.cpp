#include "stdafx.h"
#include "MyWindow.h"

float winRatio;
GLFWwindow* window;
glm::mat4 projection_matrix;
glm::mat4 view_matrix;

int MyWindow::width;
int MyWindow::height;


MyWindow::MyWindow(const char* _name, int _width, int _height) {

	width = _width;
	height = _height;
	name = _name;

	glfwWindowHint (GLFW_SAMPLES, 4);

	GLFWmonitor* mon = glfwGetPrimaryMonitor ();
	const GLFWvidmode* vmode = glfwGetVideoMode (mon);
	window = glfwCreateWindow(width, height, name, NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
	}
	glfwMakeContextCurrent (window);
	glfwSetWindowPos(window, (vmode->width - width)/2, (vmode->height - height)/2);

	glfwSetKeyCallback(window, glfw_key_callback);
	glfwSetWindowSizeCallback(window, glfw_window_size_callback);

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	winRatio = width / (float) height;
	projection_matrix = glm::mat4(1/winRatio,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
	view_matrix = glm::mat4();
	glViewport(0, 0, width, height);

	shader = new Shader("../data/vertexShader.glsl", "../data/fragmentShader.glsl");
	assert(shader);

	background = new SpriteManager();
	assert(background);

	effect_sprites = new SpriteManager();
	assert(effect_sprites);
	effect_sprites->reserveSprites(100);

	crash_sprites = new SpriteManager();
	assert(crash_sprites);
	crash_sprites->reserveSprites(500);

	createSprites();

	prevTime = glfwGetTime();
}
	
MyWindow::~MyWindow() {
	
	delete effect_sprites;
	delete crash_sprites;
	delete background;
	delete shader;
	glfwDestroyWindow(window);
}

void MyWindow::createSprites() {

	background->addEffectSprite(BACKGROUND, glm::mat4());

	crash_sprites->addCrashSprite(PLAYER);
	crash_sprites->addCrashSprite(ENEMY1);
	crash_sprites->addCrashSprite(ENEMY1);
	crash_sprites->addCrashSprite(ENEMY1);
}

void MyWindow::createSprites_regulary() {

	static double previous_seconds = glfwGetTime();

	if(glfwGetTime () - previous_seconds > create_delay) {

		previous_seconds = glfwGetTime();
		crash_sprites->addCrashSprite(ENEMY1);
	}
}

void MyWindow::testKeys() {

	static double previous_seconds = glfwGetTime();

	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_SPACE) &&
		glfwGetTime () - previous_seconds > pr_delay) {

		previous_seconds = glfwGetTime();
		crash_sprites->addCrashSprite(PROJECTILE);
	}
	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ENTER) &&
		glfwGetTime () - previous_seconds > r_delay) {

		previous_seconds = glfwGetTime();
		crash_sprites->addCrashSprite(ROCKET);
		effect_sprites->addEffectSprite(JET_ROCKET, glm::mat4());
	}
}

void MyWindow::handleCollision() {

	static double previous_seconds = glfwGetTime();

	if(glfwGetTime () - previous_seconds > collision_delay) {

		previous_seconds = glfwGetTime();
		crash_sprites->handleCollisions();
	}
}

void MyWindow::displayFrame() {

	float deltaTime = (float)(glfwGetTime() - prevTime);
	prevTime = glfwGetTime();

	crash_sprites->update_crash_model(effect_sprites, deltaTime);

	background->drawSprites(shader, deltaTime);
	crash_sprites->drawSprites(shader, deltaTime);
	effect_sprites->drawSprites(shader, deltaTime);
}

void MyWindow::run() {

	while (!glfwWindowShouldClose(window)) {

		_update_fps_counter();
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		testKeys();

		handleCollision();

		displayFrame();

//		createSprites_regulary();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void MyWindow::_update_fps_counter () {

	static double previous_seconds = glfwGetTime ();
	static int frame_count;
	double current_seconds = glfwGetTime ();
	double elapsed_seconds = current_seconds - previous_seconds;
	if (elapsed_seconds > 0.25) {
		previous_seconds = current_seconds;
		double fps = (double)frame_count / elapsed_seconds;
		char tmp[128];
		sprintf (tmp, "%s | FPS: %.2f", name, fps);
		glfwSetWindowTitle (window, tmp);
		frame_count = 0;
	}
	frame_count++;
}

void MyWindow::glfw_key_callback (GLFWwindow* _window, int key, int scancode, int action, int mods) {

	if (GLFW_PRESS == glfwGetKey (_window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose (_window, 1);
}

void MyWindow::glfw_window_size_callback (GLFWwindow* _window, int _width, int _height) {

	width = _width;
	height = _height;
	winRatio = width / (float) height;
	projection_matrix = glm::mat4(1/winRatio,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);

	glViewport(0, 0, width, height);
}