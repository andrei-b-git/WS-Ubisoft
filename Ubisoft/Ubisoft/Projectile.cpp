#include "stdafx.h"
#include "common.h"
#include "Projectile.h"

Projectile Projectile::me;


Projectile::Projectile() {
	
	speed = pr_speed;
}

Projectile::Projectile(glm::vec3 center, TextureManager *textures) {

	sprite = new Sprite(PROJECTILE, center, glm::vec2(winRatio/40, winRatio/20));
	sprite->set_texture(textures->addTexture("../resurse/FX/projectile_bolt_red.png", 1.0f));
	sprite->texture->texRatio = pr_texRatio;
	sprite->set_frames(pr_idle_begin, pr_idle_end);
	speed = pr_speed;
}

Projectile::~Projectile() {}

Projectile* Projectile::Get() {

	return &me;
}

bool Projectile::calc_model_Projectile(Sprite* &sprite, float dt) {

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
