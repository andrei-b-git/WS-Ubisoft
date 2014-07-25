#pragma once

#include "common.h"
#include "Shader.h"
#include "Texture.h"


class Sprite {

public:
	int type;
	GLuint vao;
	Texture *texture;
	int nr_indices;

	glm::mat4 model_matrix;
	glm::vec3 pos;

	struct Animation {
		float begin_frame;
		float current_frame;
		float end_frame;
		float speed;
		float current_time;
	} currentAnimation;

	struct aabb {
		glm::vec2 min;
		glm::vec2 max;
	} AABB;


	Sprite(int _type, glm::vec3 center, glm::vec2 dif);
	~Sprite();
	void set_texture(Texture *_texture);
	bool verify_frames(float begin, float end);
	void set_frames(float begin, float end);
	aabb get_AABB(glm::mat4 model_matrix, bool real);
	bool isInside(glm::mat4 model_matrix);
};