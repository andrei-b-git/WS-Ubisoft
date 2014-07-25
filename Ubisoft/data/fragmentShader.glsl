#version 400 // 150 daca nu e suportat opengl 4.x dar e suportat 3.3

in vec2 texture_coord;

uniform sampler2D basic_texture;

out vec4 out_color;

void main () {

	out_color = texture(basic_texture, texture_coord);
}
