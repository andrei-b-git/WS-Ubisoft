#pragma once

enum VERTEX_ATRIBUTES
{
	VERTEX_COORD_LOC	= 0,
	TEXTURE_COORD_LOC	= 1
};


class Shader {

public:
	GLuint program;
	unsigned int location_projection_matrix;
	unsigned int location_view_matrix;
	unsigned int location_model_matrix;
	unsigned int location_texture;
	unsigned int location_isAnimated;
	unsigned int location_frame;
	unsigned int location_texRatio;
	unsigned int location_red;

	Shader(const char* vs_name, const char* fs_name);
	~Shader();
};