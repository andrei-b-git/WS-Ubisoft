#include "stdafx.h"
#include "common.h"
#include "Enemy2.h"
#include "utils.h"
#include <math.h>

Enemy2 Enemy2::me;


Enemy2::Enemy2() {

	speed = e2_speed;
}

Enemy2::Enemy2(TextureManager *textures) {

	static float offset = 0.0f;

	float x = Random(-outer_lim + offset, -outer_lim + 0.5f + offset);
	float y = Random(1.1f, 1.2f);

	if(offset > 1.5f)
		offset = 0.0f;
	offset += 0.5f;

	sprite = new Sprite(ENEMY2, glm::vec3(x, y, 0.0f), glm::vec2(winRatio/15, winRatio/15));
	sprite->set_texture(textures->addTexture("../resurse/Enemies/strip_spikey.png", 1.0f, false));
	sprite->set_frames(e2_idle_begin, e2_idle_end);
	sprite->pos.z = 1.0f;
	sprite->offset = Random(1.0f, 3.0f);
	sprite->own.hp = e2_hp;
	sprite->own.dmg = e2_dmg;
	sprite->own.hit_score = e2_hit;
	sprite->own.kill_score = e2_kill;
	speed = e2_speed;
}

Enemy2::~Enemy2() {}

Enemy2* Enemy2::Get() {

	return &me;
}

bool Enemy2::calc_model_Enemy2(Sprite* &sprite, double dt) {

	glm::vec3 pos = sprite->pos;

	pos.x += (float)(Random(-3.0f, 3.0f)*dt);
	if(pos.x > -outer_lim && pos.x < outer_lim)
		sprite->pos.x = pos.x;
	pos.y -= (float)(speed*dt);

	glm::mat4 model_matrix = glm::translate(pos);

	model_matrix *= glm::translate(glm::vec3(sprite->center.x, sprite->center.y, 0.0f));
	model_matrix *= glm::scale(glm::vec3(sprite->offset, sprite->offset, 0.0f));
	model_matrix *= glm::translate(glm::vec3(-sprite->center.x, -sprite->center.y, 0.0f));
	sprite->offset += (float)(pos.z*1.0f*dt);
	if(sprite->offset > 3.0f || sprite->offset < 1.0f)
		pos.z *= -1.0f;

	sprite->pos.y = pos.y;
	sprite->pos.z = pos.z;
	sprite->model_matrix = model_matrix;

	if(pos.y < -2.3f)
		return false;
	return true;
}
