#include "stdafx.h"
#include "common.h"
#include "Enemy1.h"
#include "utils.h"
#include <math.h>

Enemy1 Enemy1::me;


Enemy1::Enemy1() {

	speed = e1_speed;
}

Enemy1::Enemy1(TextureManager *textures) {

	static float offset = 0.0f;

	float x = Random(-outer_lim + offset, -outer_lim + 0.5f + offset);
	float y = Random(1.1f, 1.2f);

	if(offset > 1.5f)
		offset = 0.0f;
	offset += 0.5f;

	sprite = new Sprite(ENEMY1, glm::vec3(x, y, 0.0f), glm::vec2(winRatio/15, winRatio/15));
	sprite->set_texture(textures->addTexture("../resurse/Enemies/strip_fighter.png", 1.0f, false));
	sprite->set_frames(e1_idle_begin, e1_idle_end);
	sprite->pos.z = Random(-1.0f, 1.0f) > 0.0f ? 1.0f : -1.0f;
	sprite->own.hp = e1_hp;
	sprite->own.dmg = e1_dmg;
	sprite->own.hit_score = e1_hit;
	sprite->own.kill_score = e1_kill;
	speed = e1_speed;
}

Enemy1::~Enemy1() {}

Enemy1* Enemy1::Get() {

	return &me;
}

bool Enemy1::calc_model_Enemy1(Sprite* &sprite, double dt) {

	glm::vec3 pos = sprite->pos;

	pos.y -= (float)(speed*dt);
	pos.x = 1.5f*sin(pos.z*(pos.y - sprite->offset)*2*PI/360.0f);
	float S = Random(0.3f, 0.7f);
	sprite->offset += S;

	glm::mat4 model_matrix = glm::translate(pos);
	if(sprite->isInside(model_matrix, outer_lim, false)) {
		sprite->pos = pos;
		sprite->model_matrix = model_matrix;
	}
	if(pos.y < -2.3f)
		return false;
	return true;
}
