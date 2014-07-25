#version 400 // 150 daca nu e suportat opengl 4.x dar e suportat 3.3

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec2 in_tex;

out vec2 texture_coord;

uniform mat4 projection_matrix, view_matrix, model_matrix;
uniform float isAnimated;
uniform float frame;
uniform float texRatio;

void main () {

	texture_coord.x = (1.0f - isAnimated)*in_tex.x   +   isAnimated*(frame + in_tex.x)*texRatio;
	texture_coord.y = in_tex.y;

	gl_Position = projection_matrix * 
					view_matrix * 
					model_matrix * 
					vec4 (in_pos, 1.0);
}