#include "stdafx.h"
#include "common.h"
#include "Shader.h"
#include "utils.h"


Shader::Shader(const char* vs_name, const char* fs_name) {

	const char * vertex_shader = LoadFileInMemory(vs_name);
	const char * fragment_shader = LoadFileInMemory(fs_name);

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	program = glCreateProgram();
	glAttachShader(program, fs);
	glAttachShader(program, vs);
	glLinkProgram(program);

	location_projection_matrix = glGetUniformLocation(program,"projection_matrix");
	location_view_matrix = glGetUniformLocation(program,"view_matrix");
	location_model_matrix = glGetUniformLocation(program,"model_matrix");
	location_texture = glGetUniformLocation(program, "basic_texture");
	location_isAnimated = glGetUniformLocation(program, "isAnimated");
	location_frame = glGetUniformLocation(program, "frame");
	location_texRatio = glGetUniformLocation(program, "texRatio");

	delete[] vertex_shader;
	delete[] fragment_shader;
}

Shader::~Shader() {
	
	glDeleteProgram(program);
}