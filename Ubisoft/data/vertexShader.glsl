#version 400 // 150 daca nu e suportat opengl 4.x dar e suportat 3.3

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec2 in_tex;

out vec2 texture_coord;

uniform mat4 model_matrix, projection_matrix;

void main () {
	texture_coord = in_tex;
	gl_Position = projection_matrix * model_matrix * vec4 (in_pos, 1.0);
}