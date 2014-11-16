#include "stdafx.h"
#include "common.h"
#include "Projectile.h"

Projectile Projectile::me;


Projectile::Projectile() {}

Projectile::Projectile(Sprite *ref, TextureManager *textures) {

	switch(ref->type) {
		case PLAYER: {
			sprite = new Sprite(PROJECTILE, glm::vec3(p_coords_x, p_coords_y + winRatio/11, 0.0f), glm::vec2(winRatio/40, winRatio/20));
			sprite->set_texture(textures->addTexture("../resurse/FX/projectile_bolt_blue.png", 1.0f, false));
			sprite->texture->texRatio = pr_texRatio;
			sprite->set_frames(pr_idle_begin, pr_idle_end);
			sprite->own.hp = 1.0f;
			sprite->own.dmg = ppr_dmg;
			sprite->own.hit_score = 0;
			sprite->own.kill_score = 0;
			break;
		}
		case ENEMY1: {
			sprite = new Sprite(PROJECTILE, glm::vec3(ref->center.x, ref->center.y - winRatio/20, 0.0f), glm::vec2(winRatio/40, winRatio/20));
			sprite->set_texture(textures->addTexture("../resurse/FX/projectile_bolt_red.png", 1.0f, true));
			sprite->texture->texRatio = pr_texRatio;
			sprite->set_frames(pr_idle_begin, pr_idle_end);
			sprite->own.hp = 1.0f;
			sprite->own.dmg = e1pr_dmg;
			sprite->own.hit_score = 0;
			sprite->own.kill_score = 0;
			break;
		}
	}
}

Projectile::~Projectile() {}

Projectile* Projectile::Get() {

	return &me;
}

bool Projectile::calc_model_Projectile(Sprite* &sprite, double dt) {

	glm::vec3 pos = sprite->pos;

	switch(sprite->ref_type) {
		case PLAYER: {
			pos.y += (float)(ppr_speed*dt);
			break;
		}
		case ENEMY1: {
			pos.y -= (float)(e1pr_speed*dt);
			break;
		}
	}
	glm::mat4 model_matrix = glm::translate(sprite->original_model_matrix, pos);
	if(sprite->isInside(model_matrix, outer_lim, false)) {
		sprite->pos = pos;
		sprite->model_matrix = model_matrix;
		return true;
	}
	else
		return false;
}
