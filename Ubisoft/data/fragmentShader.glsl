#version 400 // 150 daca nu e suportat opengl 4.x dar e suportat 3.3

in vec3 vertex_to_frag_col;

out vec4 out_col;

void main () {
  out_col = vec4 (vertex_to_frag_col, 1.0);
}