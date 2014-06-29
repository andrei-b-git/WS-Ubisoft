#version 400 // 150 daca nu e suportat opengl 4.x dar e suportat 3.3

in vec3 in_pos;
uniform vec3 in_col;

out vec3 vertex_to_frag_col;

void main () {
	gl_Position = vec4 (in_pos, 1.0);
	vertex_to_frag_col = in_col;
}