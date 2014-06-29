#include "stdafx.h"
#include <GLEW/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <vector>
#include <glm\glm.hpp>

#define PI 3.14159265358979323846

using namespace std;


int g_gl_width = 640;
int g_gl_height = 640;

GLuint shader_programme;

GLuint vao[4];
GLuint vbo[4];

/*
void glfw_error_callback (int error, const char* description) {
  gl_log_err ("GLFW ERROR: code %i msg: %s\n", error, description);
}
*/

void PrintRenderVersion()
{
	// Vedem versiunile
	const GLubyte* renderer = glGetString (GL_RENDERER); //renderer string
	const GLubyte* version = glGetString (GL_VERSION); // version string
	printf ("Renderer: %s\n", renderer);
	printf ("OpenGL version supported %s\n", version);
}


// functie banala de incarcat continutul unui fisier intr-un buffer
char * LoadFileInMemory(const char *filename)
{
	int size = 0;
	char *buffer = NULL;
	FILE *f = fopen(filename, "rb");
	if (f == NULL)
	{
		return NULL;
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	buffer = new char[size + 1];
	if (size != fread(buffer, sizeof(char), size, f))
	{
		delete[] buffer;
	}
	fclose(f);
	buffer[size] = 0;
	return buffer;
}

// ....................Calculam FPS-ul si il afisam in titlul ferestrei.................
void _update_fps_counter (GLFWwindow* window) {
	static double previous_seconds = glfwGetTime ();
	static int frame_count;
	double current_seconds = glfwGetTime ();
	double elapsed_seconds = current_seconds - previous_seconds;
	if (elapsed_seconds > 0.25) {
		previous_seconds = current_seconds;
		double fps = (double)frame_count / elapsed_seconds;
		char tmp[128];
		sprintf (tmp, "opengl @ fps: %.2f", fps);
		glfwSetWindowTitle (window, tmp);
		frame_count = 0;
	}
	frame_count++;
}


void LoadShader()
{
	const char * vertex_shader = LoadFileInMemory("../data/vertexShader.glsl");
	const char * fragment_shader = LoadFileInMemory("../data/fragmentShader.glsl");

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	delete[] vertex_shader;
	delete[] fragment_shader;
}

// POLIGON
void CreatePoligon(float xc, float yc, int vertex_count, int index)
{
	vector<glm::vec3> vertex_buffer;
	float radius = 0.25f;

	if(vertex_count < 3) {
		printf ( "ERROR: Vertex count must be at least 3.\n");
		return;
	}
	if(vertex_count == 3) {
		// buffer cu vertecsi in RAM 
		vertex_buffer.push_back(glm::vec3(xc, yc+0.25f, 0.0f));
		vertex_buffer.push_back(glm::vec3(xc+0.25f, yc-0.25f, 0.0f));
		vertex_buffer.push_back(glm::vec3(xc-0.25f, yc-0.25f, 0.0f));
	}
	if(vertex_count >= 4) {
		// buffer cu vertecsi in RAM 
		for (float u = 0; u <= 2*PI; u += (float)2*PI/vertex_count)
		{
			vertex_buffer.push_back(glm::vec3(xc + radius * sin(u), yc + radius * cos(u), 0.0));
		}
	}
	// creare VAO
	glGenVertexArrays(1, &vao[index]);
	// bind VAO
	glBindVertexArray(vao[index]);
	// creare VBO
	glGenBuffers(1, &vbo[index]);
	// bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo[index]);
	//  scriem in bufferul din memoria video informatia din bufferul din memoria RAM
	glBufferData(GL_ARRAY_BUFFER, 3 * vertex_buffer.size() * sizeof (float), &vertex_buffer[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
}

// TRIUNGHI
void CreateTriangle(float x1, float y1, float x2, float y2, float x3, float y3, int index)
{
	// buffer cu vertecsi in RAM 
	float vertex_buffer[] = {
		x1, y1, 0.0f,
		x2, y2, 0.0f,
		x3, y3, 0.0f
	};
	// creare VAO
	glGenVertexArrays(1, &vao[index]);
	// bind VAO
	glBindVertexArray(vao[index]);
	// creare VBO
	glGenBuffers(1, &vbo[index]);
	// bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo[index]);
	//  scriem in bufferul din memoria video informatia din bufferul din memoria RAM
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof (float), vertex_buffer, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), (void *)0);
}

// PATRAT
void CreateQuad(float xc, float yc, float l, int index)
{
	// buffer cu vertecsi in RAM 
	float vertex_buffer[] = {
		xc+l/2, yc+l/2, 0.0f,
		xc+l/2, yc-l/2, 0.0f,
		xc-l/2, yc-l/2, 0.0f,
		xc-l/2, yc+l/2, 0.0f
	};
	// creare VAO
	glGenVertexArrays(1, &vao[index]);
	// bind VAO
	glBindVertexArray(vao[index]);
	// creare VBO
	glGenBuffers(1, &vbo[index]);
	// bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo[index]);
	//  scriem in bufferul din memoria video informatia din bufferul din memoria RAM
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof (float), vertex_buffer, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), (void *)0);
}


void TestKeys(GLFWwindow* window)
{
	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_W)) {

	}
	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_S)) {

	}
	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_A)) {

	}
	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_D)) {

	}
}


// se va chema aceasta functie pe window resize 
void glfw_window_size_callback (GLFWwindow* window, int width, int height) {
	g_gl_width = width;
	g_gl_height = height;
  
  /* putem modifica aici matricile de perspectiva */
}


void DrawObjects(GLFWwindow* window, int vertex_count)
{
	while (!glfwWindowShouldClose(window)) {
		//..... Randare................. 
		_update_fps_counter(window);
		// stergem ce s-a desenat anterior
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glViewport (0, 0, g_gl_width, g_gl_height);
		// spunem ce shader vom folosi pentru desenare
		glUseProgram(shader_programme);

		TestKeys(window);

		// CERC
		glUniform3f(glGetUniformLocation(shader_programme, "in_col"), 0.0f, 1.0f, 0.0f);
		// facem bind
		glBindVertexArray(vao[0]);
		if(vertex_count == 3) {
			// draw points 0-3 from the currently bound VAO with current in-use shader
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		if(vertex_count >= 4) {
			// draw points 0-4 from the currently bound VAO with current in-use shader
			glDrawArrays(GL_TRIANGLE_FAN, 0, vertex_count);
		}
		// TRIUNGHI 1
		glUniform3f(glGetUniformLocation(shader_programme, "in_col"), 1.0f, 0.0f, 0.0f);
		// facem bind
		glBindVertexArray(vao[1]);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// TRIUNGHI 2
		glUniform3f(glGetUniformLocation(shader_programme, "in_col"), 0.0f, 0.0f, 1.0f);
		// facem bind
		glBindVertexArray(vao[2]);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// PATRAT
		glUniform3f(glGetUniformLocation(shader_programme, "in_col"), 1.0f, 1.0f, 0.0f);
		// facem bind
		glBindVertexArray(vao[3]);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_QUADS, 0, 4);

		// facem swap la buffere (Double buffer)
		glfwSwapBuffers(window);

		glfwPollEvents();

		if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose (window, 1);
		}
	}
}


int main () {

	// Initializare (se creeaza contextul)
	if (!glfwInit ()) {
		fprintf (stderr, "ERROR: could not start GLFW3\n");
		return 1;
	} 
	// Se creeaza fereastra
	// ........Resolution si Fullscreen..........
//	GLFWmonitor* mon = glfwGetPrimaryMonitor ();
//	const GLFWvidmode* vmode = glfwGetVideoMode (mon);
//	GLFWwindow* window = glfwCreateWindow (vmode->width, vmode->height, "Extended GL Init", mon, NULL);
	GLFWwindow* window = glfwCreateWindow (g_gl_width, g_gl_height, "Workshop1", NULL, NULL);
	if (!window) {
		// nu am reusit sa facem fereastra, oprim totul si dam mesaj de eroare
		printf ( "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	// Atasam contextul de fereastra
	glfwMakeContextCurrent (window);
	// Pornit extension handler-ul
	glewInit ();

	//............Antialiasing...............
//	glfwWindowHint (GLFW_SAMPLES, 4);
	// setam callbackul 
//	glfwSetWindowSizeCallback (window, glfw_window_size_callback);

	PrintRenderVersion();

	LoadShader();

	int vertex_count;
	printf("Vertex_count = ");
	scanf("%d", &vertex_count);

	CreatePoligon(0.0, 0.0, vertex_count, 0);
	CreateTriangle(-0.5f, -0.25f, -0.25f, -0.75f, -0.75f, -0.75f, 1);
	CreateTriangle(0.5f, -0.25f, 0.75f, -0.75f, 0.25f, -0.75f, 2);
	CreateQuad(-0.5f, 0.5f, 0.25f, 3);

	DrawObjects(window, vertex_count);
  
	glfwTerminate();

	return 0;
}