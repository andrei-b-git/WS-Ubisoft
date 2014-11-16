#include "stdafx.h"
#include "common.h"
#include "Rocket.h"

Rocket Rocket::me;


Rocket::Rocket() {
	
	speed = r_speed;
}

Rocket::Rocket(glm::vec3 center, TextureManager *textures) {

	sprite = new Sprite(ROCKET, center, glm::vec2(winRatio/35, winRatio/35));
	sprite->set_texture(textures->addTexture("../resurse/Rockets/rocket_type_A0000.png", 0.0f, false));
	sprite->own.hp = 1.0f;
	sprite->own.dmg = r_dmg;
	sprite->own.hit_score = 0;
	sprite->own.kill_score = 0;
	speed = r_speed;
}

Rocket::~Rocket() {}

Rocket* Rocket::Get() {

	return &me;
}

bool Rocket::calc_model_Rocket(Sprite* &sprite, double dt) {

	glm::vec3 pos = sprite->pos;

	pos.y += (float)(speed*dt);

	glm::mat4 model_matrix = glm::translate(sprite->original_model_matrix, pos);
	if(sprite->isInside(model_matrix, outer_lim, false)) {
		sprite->pos = pos;
		sprite->model_matrix = model_matrix;
		return true;
	}
	else
		return false;
}
