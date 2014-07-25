#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite(int _type, glm::vec3 center, glm::vec2 dif) {

	type = _type;
	model_matrix = glm::mat4();
	pos = glm::vec3();

	currentAnimation.speed = anim_speed;
	currentAnimation.current_time = 0.0f;

	AABB.min = glm::vec2(center.x - dif.x, center.y - dif.y);
	AABB.max = glm::vec2(center.x + dif.x, center.y + dif.y);

	GLfloat vertex_buffer[] = {	center.x + dif.x, center.y + dif.y, 0.0f, 1.0f, 1.0f,
								center.x + dif.x, center.y - dif.y, 0.0f, 1.0f, 0.0f,
								center.x - dif.x, center.y - dif.y, 0.0f, 0.0f, 0.0f,
								center.x - dif.x, center.y + dif.y, 0.0f, 0.0f, 1.0f };

	GLubyte index_buffer[] = {	0, 1, 2,
								2, 3, 0 };

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo = 0, ibo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer), vertex_buffer, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer), index_buffer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(VERTEX_COORD_LOC);
	glVertexAttribPointer(VERTEX_COORD_LOC, 3, GL_FLOAT, GL_FALSE, 5 * sizeof (float), (void *)0);

	glEnableVertexAttribArray(TEXTURE_COORD_LOC);
	glVertexAttribPointer(TEXTURE_COORD_LOC, 2, GL_FLOAT, GL_FALSE, 5 * sizeof (float), (void *)(3 * sizeof(float)));

	nr_indices = sizeof(index_buffer);
}

Sprite::~Sprite() {

	glDeleteVertexArrays(1,&vao);
}

void Sprite::set_texture(Texture *_texture) {

	texture = _texture;
	assert(texture);
}

bool Sprite::verify_frames(float begin, float end) {

	return (currentAnimation.begin_frame == begin && currentAnimation.end_frame == end);
}

void Sprite::set_frames(float begin, float end) {

	currentAnimation.begin_frame = begin;
	currentAnimation.current_frame = begin;
	currentAnimation.end_frame = end;
}

Sprite::aabb Sprite::get_AABB(glm::mat4 model_matrix, bool real) {

	struct aabb new_AABB;
	glm::mat4 PV = glm::mat4();

	if(real == true)
		PV = projection_matrix * view_matrix;

	glm::vec4 new_min = PV * model_matrix * 
						glm::vec4 (AABB.min, 0.0f, 1.0f);

	glm::vec4 new_max = PV * model_matrix * 
						glm::vec4 (AABB.max, 0.0f, 1.0f);

	new_AABB.min.x = new_min.x;
	new_AABB.min.y = new_min.y;
	new_AABB.max.x = new_max.x;
	new_AABB.max.y = new_max.y;

	return new_AABB;
}

bool Sprite::isInside(glm::mat4 model_matrix) {

	struct aabb new_AABB = get_AABB(model_matrix, true);

	return !(new_AABB.min.x < -1.0f || new_AABB.min.y < -1.0f ||
			new_AABB.max.x > 1.0f || new_AABB.max.y > 1.0f);
}
