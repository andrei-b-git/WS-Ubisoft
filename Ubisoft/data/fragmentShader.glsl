#version 400 // 150 daca nu e suportat opengl 4.x dar e suportat 3.3

in vec2 texture_coord;

uniform sampler2D basic_texture;
uniform int has_alpha;

out vec4 out_color;

void main () {
	vec3 tex = texture(basic_texture, texture_coord).xyz;

	if(has_alpha<0.5f)
		if((tex.r<0.1) && (tex.g<0.1) && (tex.b>0.1))
			discard;

	out_color = vec4(tex, 1.0f);
}
