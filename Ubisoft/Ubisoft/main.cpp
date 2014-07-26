#include "stdafx.h"

#define _CRTDBG_MAP_ALLOC

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif

#include <stdlib.h>
#include <crtdbg.h>

#include "MyWindow.h"
#include "utils.h"


static void glfw_error_callback (int error, const char* description) {

	ErrorLog("GLFW ERROR: code %i msg: %s\n", error, description);
}

void APIENTRY openglDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, void* userParam)
{
	printf("%s", message);
	__debugbreak();
}

int main() {

	printf("-------------------------------------\n");
	printf("\tLEFT: TASTA A\n");
	printf("\tRIGHT: TASTA D\n");
	printf("\tUP: TASTA W\n");
	printf("\tDOWN: TASTA S\n");
	printf("\tSHOOT: TASTA SPACE\n");
	printf("\tSHOOT ROCKET: TASTA ENTER\n");
	printf("-------------------------------------\n");

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (!glfwInit ()) {
		fprintf (stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}
	glfwSetErrorCallback(glfw_error_callback);

	MyWindow *win = new MyWindow("Space Invaders", WWIDTH, WHEIGHT);
	assert(win);

	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(openglDebugCallback, NULL);
	glEnable(GL_DEBUG_OUTPUT);

	win->run();

	delete win;

	glfwTerminate();

	return 0;
}
