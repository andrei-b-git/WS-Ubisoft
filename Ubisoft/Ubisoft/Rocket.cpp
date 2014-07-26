#include "stdafx.h"
#include "common.h"
#include "Rocket.h"

Rocket Rocket::me;


Rocket::Rocket() {
	
	speed = r_speed;
}

Rocket::Rocket(glm::vec3 center, TextureManager *textures) {

	sprite = new Sprite(ROCKET, center, glm::vec2(winRatio/30, winRatio/30));
	sprite->set_texture(textures->addTexture("../resurse/Rockets/rocket_type_A0000.png", 0.0f));
	speed = r_speed;
}

Rocket::~Rocket() {}

Rocket* Rocket::Get() {

	return &me;
}

bool Rocket::calc_model_Rocket(Sprite* &sprite, float dt) {

	glm::vec3 pos = sprite->pos;

	pos.y += speed*dt;

	glm::mat4 model_matrix = glm::translate(glm::mat4(), pos);
	if(sprite->isInside(model_matrix)) {
		sprite->pos = pos;
		sprite->model_matrix = model_matrix;
		return true;
	}
	else
		return false;
}
