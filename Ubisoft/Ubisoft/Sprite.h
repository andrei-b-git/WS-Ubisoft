#pragma once

#include "common.h"
#include "Shader.h"
#include "Texture.h"


class Sprite {

public:
	int type;
	glm::vec3 center;
	glm::vec2 dif;
	GLuint vao;
	Texture *texture;
	int nr_indices;

	glm::mat4 original_model_matrix;
	glm::mat4 model_matrix;
	glm::vec3 pos;
	float offset;

	Sprite *ref;
	int ref_type;
	double previousTime;

	struct Animation {
		float begin_frame;
		float current_frame;
		float end_frame;
		float speed;
		double current_time;
	} currentAnimation;

	struct aabb {
		glm::vec2 min;
		glm::vec2 max;
	} AABB;
	bool hasColided;
	Sprite *crasher;

	struct Gameplay {
		float hp;
		float red;
		float dmg;
		int hit_score;
		int kill_score;
	} own;


	Sprite(int _type, glm::vec3 _center, glm::vec2 _dif);
	~Sprite();
	void set_texture(Texture *_texture);
	bool verify_frames(float begin, float end);
	void set_frames(float begin, float end);
	aabb get_AABB(glm::mat4 model_matrix, bool real);
	bool isInside(glm::mat4 model_matrix, float limit, bool isPlayer);
};