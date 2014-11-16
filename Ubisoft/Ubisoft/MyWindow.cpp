#include "stdafx.h"
#include "MyWindow.h"

float winRatio;
GLFWwindow* window;
glm::mat4 projection_matrix;
glm::mat4 view_matrix;
int score;
int nr_rockets;
int nr_e1_killed;
int nr_e2_killed;
bool GAME_OVER;

int MyWindow::width;
int MyWindow::height;

double t = 0.0f;
double dt = dt_physics;
double accumulator = 0.0f;


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

	currentTime = glfwGetTime();
	score = 0;
	nr_rockets = 3;
	nr_e1_killed = 0;
	nr_e2_killed = 0;
	GAME_OVER = false;

	shader = new Shader("../data/vertexShader.glsl", "../data/fragmentShader.glsl");
	assert(shader);

	background = new SpriteManager();
	assert(background);

	crash_sprites = new SpriteManager();
	assert(crash_sprites);
	crash_sprites->reserveSprites(500);

	effect_sprites = new SpriteManager();
	assert(effect_sprites);
	effect_sprites->reserveSprites(500);

	UI_sprites = new SpriteManager();
	assert(UI_sprites);
	UI_sprites->reserveSprites(50);

	createDefaultSprites();
}
	
MyWindow::~MyWindow() {
	
	delete UI_sprites;
	delete effect_sprites;
	delete crash_sprites;
	delete background;
	delete shader;
	glfwDestroyWindow(window);
}

void MyWindow::createDefaultSprites() {

	background->addEffectSprite(BACKGROUND, NULL, -1.0f);

	crash_sprites->addCrashSprite(PLAYER, NULL, effect_sprites);

	effect_sprites->textures->addTexture("../resurse/Explosions/Exp_type_A.png", 1.0f, false);
	effect_sprites->textures->addTexture("../resurse/Explosions/Turret_blast_strip.png", 1.0f, false);
	effect_sprites->textures->addTexture("../resurse/Explosions/Exp_type_C.png", 1.0f, false);
	effect_sprites->textures->addTexture("../resurse/Explosions/Fort_exp_strip.png", 1.0f, false);
	effect_sprites->textures->addTexture("../resurse/Explosions/Vehicle_exp_strip.png", 1.0f, false);

	UI_sprites->addUiSprite(READY, 0.0f);
	UI_sprites->addUiSprite(SCORE, 0.0f);
	UI_sprites->addUiSprite(NUMBER_0, 0.0f);
	UI_sprites->addUiSprite(RED_BAR, 0.0f);
	UI_sprites->addUiSprite(GREEN_BAR, 0.0f);
	UI_sprites->addUiSprite(RKT_ICON, 0.0f);
	UI_sprites->addUiSprite(RKT_ICON, winRatio/30);
	UI_sprites->addUiSprite(RKT_ICON, 2*winRatio/30);
}

void MyWindow::createWave(double time) {

	static double previousTime = -wave_delay*20/21;
	static int enemy = 1;

	if(time - previousTime > wave_delay) {

		previousTime = time;

		if(UI_sprites->sprites->at(0)->type == READY)
			UI_sprites->removeSprite(0);

		if(enemy == 1) {
			for(int i=0; i<e1_nr_wave; i++)
				crash_sprites->addCrashSprite(ENEMY1, NULL, effect_sprites);
			enemy = 2;
		} else {
			for(int i=0; i<e2_nr_wave; i++)
				crash_sprites->addCrashSprite(ENEMY2, NULL, effect_sprites);
			enemy = 1;
		}
	}
	if(nr_e1_killed == e1_nr_wave || nr_e2_killed == e2_nr_wave) {
		crash_sprites->addCrashSprite(BONUS, NULL, effect_sprites);
		nr_e1_killed = 0;
		nr_e2_killed = 0;
		previousTime = -wave_delay;
	}
	if(crash_sprites->player != NULL && GAME_OVER == true) {
		UI_sprites->addUiSprite(OVER, 0.0f);
		crash_sprites->player = NULL;
	}
}

void MyWindow::testKeys(double time) {

	static double previousTime = 0.0f;

	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_SPACE) &&
		time - previousTime > fire_rate) {

		previousTime = time;
		crash_sprites->addCrashSprite(PROJECTILE, crash_sprites->player, effect_sprites);
	}
	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ENTER) &&
		time - previousTime > r_delay && nr_rockets > 0) {

		previousTime = time;
		crash_sprites->addCrashSprite(ROCKET, crash_sprites->player, effect_sprites);
		nr_rockets --;
	}
}

void MyWindow::handleCollision(double time) {

	static double previousTime = 0.0f;

	if(time - previousTime > collision_delay) {

		previousTime = time;
		crash_sprites->handleCollisions(effect_sprites, UI_sprites);
	}
}

void MyWindow::update_score() {

	static int previous_score = 0;

	if(score != previous_score) {

		UI_sprites->clearScore();

		int copy_score = score;
		int i = 0;

		while(copy_score){
			UI_sprites->addUiSprite(20 + copy_score % 10, i*winRatio/35);
			copy_score /= 10;
			i++;
		}
		previous_score = score;
	}
}

void MyWindow::update_rockets() {

	static int previous_nr_rockets = 3;

	if(nr_rockets != previous_nr_rockets) {

		UI_sprites->clearRockets();

		for(int i=0; i<nr_rockets; i++)
			UI_sprites->addUiSprite(RKT_ICON, i*winRatio/30);

		previous_nr_rockets = nr_rockets;
	}
}

void MyWindow::run() {

	while (!glfwWindowShouldClose(window)) {

		_update_fps_counter();
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		double newTime = glfwGetTime();
		double frameTime = newTime - currentTime;
		if ( frameTime > 0.25 )
			frameTime = 0.25;
		currentTime = newTime;

		accumulator += frameTime;

		while ( accumulator >= dt ) {

			// update fizica (deplasare, anim, coliziune)
			createWave(t);
			if(GAME_OVER == false) {
				testKeys(t);
				handleCollision(t);
			}
			background->update_background(dt);
			crash_sprites->update_crash_model(effect_sprites, t, dt);

			crash_sprites->update_animation(dt);
			effect_sprites->update_animation(dt);

			t += dt;
			accumulator -= dt;
		}
		// render si update scor
		update_score();
		update_rockets();

		background->drawSprites(shader, false);
		crash_sprites->drawSprites(shader, false);
		effect_sprites->drawSprites(shader, false);
		UI_sprites->drawSprites(shader, true);

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