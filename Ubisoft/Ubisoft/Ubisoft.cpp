#include "stdafx.h"
#include "stb_image.h"
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <vector>
#include <math.h>
#include "Shader.h"
#include "Sprite.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;


static int g_gl_width = 1024;
static int g_gl_height = 768;

static glm::mat4 original_model_matrix = glm::mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
static glm::mat4 projection_matrix = glm::mat4(g_gl_height/(float)g_gl_width,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
static glm::vec3 translation;


static void glfw_error_callback (int error, const char* description) {

	fprintf(stderr, "GLFW ERROR: code %i msg: %s\n", error, description);
}


static void glfw_key_callback (GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose (window, 1);
}


static void glfw_window_size_callback (GLFWwindow* window, int width, int height) {

	g_gl_width = width;
	g_gl_height = height;
	float ratio = width / (float) height;
	projection_matrix = glm::mat4(1/ratio,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);

	glViewport(0, 0, g_gl_width, g_gl_height);
}


static void _update_fps_counter (GLFWwindow* window) {

	static double previous_seconds = glfwGetTime ();
	static int frame_count;
	double current_seconds = glfwGetTime ();
	double elapsed_seconds = current_seconds - previous_seconds;
	if (elapsed_seconds > 0.25) {
		previous_seconds = current_seconds;
		double fps = (double)frame_count / elapsed_seconds;
		char tmp[128];
		sprintf (tmp, "Space Invaders | FPS: %.2f", fps);
		glfwSetWindowTitle (window, tmp);
		frame_count = 0;
	}
	frame_count++;
}


static void TestKeys(GLFWwindow* window) {

	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_W))
		translation.y += 0.01;
	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_S))
		translation.y -= 0.01;
	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_A))
		translation.x -= 0.01;
	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_D))
		translation.x += 0.01;
}

int main() {

	if (!glfwInit ()) {
		fprintf (stderr, "ERROR: could not start GLFW3\n");
		return 1;
	} 
	glfwSetErrorCallback(glfw_error_callback);

	glfwWindowHint (GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(g_gl_width, g_gl_height, "Space Invaders", NULL, NULL);
	if (!window) {
		printf ( "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent (window);
	glfwSetWindowPos(window, 400, 200);

	glewInit ();

	glfwSetKeyCallback(window, glfw_key_callback);
	glfwSetWindowSizeCallback(window, glfw_window_size_callback);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LESS);

	Shader *shader = new Shader();
	Sprite *poly1 = new Sprite(0.0f, 0.0f, 0.25f, 4, original_model_matrix, "../resurse/player0000.png");
	Sprite *poly = new Sprite(0.0f, 0.0f, 2.0f, 4, original_model_matrix, "../resurse/Background2.png");

    while (!glfwWindowShouldClose(window)) {

		_update_fps_counter (window);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram (shader->program);

		TestKeys(window);

		poly1->model_matrix = glm::translate(original_model_matrix, translation);
		glUniformMatrix4fv(shader->location_model_matrix,1,false,glm::value_ptr(poly1->model_matrix));
		glUniformMatrix4fv(shader->location_projection_matrix,1,false,glm::value_ptr(projection_matrix));
		glUniform1i(shader->location_has_alpha, 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, poly1->texture);
		glUniform1i(shader->location_texture, 0);

		glBindVertexArray(poly1->vao);
		glDrawElements(GL_TRIANGLES, poly1->nr_indices, GL_UNSIGNED_INT, NULL);

		glUniformMatrix4fv(shader->location_model_matrix,1,false,glm::value_ptr(poly->model_matrix));
		glUniformMatrix4fv(shader->location_projection_matrix,1,false,glm::value_ptr(projection_matrix));
		glUniform1i(shader->location_has_alpha, 1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, poly->texture);
		glUniform1i(shader->location_texture, 0);

		glBindVertexArray(poly->vao);
		glDrawElements(GL_TRIANGLES, poly->nr_indices, GL_UNSIGNED_INT, NULL);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
	delete shader;
	delete poly;

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG
