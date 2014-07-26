#include "stdafx.h"
#include "common.h"
#include "Enemy1.h"

Enemy1 Enemy1::me;


Enemy1::Enemy1() {

	speed = e1_speed;
}

Enemy1::Enemy1(TextureManager *textures) {

	float x = -1.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0f)));
	float y = winRatio/6 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.0f - winRatio/3)));

	sprite = new Sprite(ENEMY1, glm::vec3(x, y, 0.0f), glm::vec2(winRatio/15, winRatio/15));
	sprite->set_texture(textures->addTexture("../resurse/Enemies/strip_fighter.png", 1.0f));
	sprite->set_frames(e1_idle_begin, e1_idle_end);
	sprite->pos.z = (x > 0.0f) ? -1.0f : 1.0f;
	speed = e1_speed;
}

Enemy1::~Enemy1() {}

Enemy1* Enemy1::Get() {

	return &me;
}

void Enemy1::calc_model_Enemy1(Sprite* &sprite, float dt) {

	glm::vec3 pos = sprite->pos;

	pos.x += pos.z*speed*dt;

	glm::mat4 model_matrix = glm::translate(glm::mat4(), pos);
	if(sprite->isInside(model_matrix)) {
		sprite->pos = pos;
		sprite->model_matrix = model_matrix;
	}
	else
		sprite->pos.z *= -1.0f;
}
