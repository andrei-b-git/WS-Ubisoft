#include "stdafx.h"
#include "SpriteManager.h"
#include "Player.h"
#include "Projectile.h"
#include "Rocket.h"
#include "Enemy1.h"

Sprite *player;
bool thrust;
Sprite *thrustSprite;
Sprite *jet_rocket;


SpriteManager::SpriteManager() {

	sprites = new std::vector<Sprite*>;
	assert(sprites);
	textures = new TextureManager();
	assert(textures);
}

SpriteManager::~SpriteManager() {
	
	while(!sprites->empty()) {
		delete sprites->back();
		sprites->pop_back();
	}
	delete sprites;
	delete textures;
}

void SpriteManager::reserveSprites(int nr) {

	sprites->reserve(nr);
}

void SpriteManager::addEffectSprite(int type, glm::mat4 model_matrix) {

	Sprite *s;

	switch(type) {
		case BACKGROUND: {
			s = new Sprite(BACKGROUND, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(winRatio, winRatio));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/Backgrounds/Background3.png", 0.0f));
			sprites->push_back(s);
			break;
		}
		case JET_PLAYER: {
			thrustSprite = new Sprite(JET_PLAYER, glm::vec3(0.0f, -winRatio/2.2f, 0.0f), glm::vec2(winRatio/20, winRatio/20));
			assert(thrustSprite);
			thrustSprite->set_texture(textures->addTexture("../resurse/FX/thrust_yellow2.png", 1.0f));
			thrustSprite->set_frames(jp_idle_begin, jp_idle_end);
			thrustSprite->model_matrix = model_matrix;
			sprites->push_back(thrustSprite);
			break;
		}
		case JET_ROCKET: {
			Sprite::aabb AABB = player->get_AABB(player->model_matrix, false);
			glm::vec3 center = glm::vec3((AABB.max.x + AABB.min.x)/2, AABB.max.y - winRatio/20, 0.0f);
			jet_rocket = new Sprite(JET_ROCKET, center, glm::vec2(winRatio/30, winRatio/30));
			assert(jet_rocket);
			jet_rocket->set_texture(textures->addTexture("../resurse/FX/projectile_bolt_blue.png", 1.0f));
			jet_rocket->texture->texRatio = jr_texRatio;
			jet_rocket->set_frames(jr_idle_begin, jr_idle_end);
			sprites->push_back(jet_rocket);
			break;
		}
	}
}

void SpriteManager::addCrashSprite(int type) {

	switch(type) {
		case PLAYER: {
			Player *p = new Player(textures);
			assert(p);
			player = p->sprite;
			sprites->push_back(p->sprite);
			thrust = false;
			break;
		}
		case PROJECTILE: {
			Sprite::aabb AABB = player->get_AABB(player->model_matrix, false);
			glm::vec3 center = glm::vec3((AABB.max.x + AABB.min.x)/2, AABB.max.y, 0.0f);
			Projectile *pr = new Projectile(center, textures);
			assert(pr);
			sprites->push_back(pr->sprite);
			break;
		}
		case ROCKET: {
			Sprite::aabb AABB = player->get_AABB(player->model_matrix, false);
			glm::vec3 center = glm::vec3((AABB.max.x + AABB.min.x)/2, AABB.max.y, 0.0f);
			Rocket *r = new Rocket(center, textures);
			assert(r);
			sprites->push_back(r->sprite);
			break;
		}
		case ENEMY1: {
			Enemy1 *e1 = new Enemy1(textures);
			assert(e1);
			sprites->push_back(e1->sprite);
			break;
		}
	}
}

void SpriteManager::removeSprite(int index) {

	delete sprites->at(index);
	sprites->erase(sprites->begin() + index);
}

void SpriteManager::removeSpriteType(int type) {

	for(int i=0; i<sprites->size(); i++)
		if(sprites->at(i)->type == type)
			removeSprite(i);
}

void SpriteManager::update_crash_model(SpriteManager *effect_sprites, float dt) {

	for(int i=0; i<sprites->size(); i++) {

		switch(sprites->at(i)->type) {

			case PLAYER: {
				bool modified = Player::Get()->calc_model_Player(sprites->at(i), dt);
				if(modified == true) {
					if(thrust == false) {
						effect_sprites->addEffectSprite(JET_PLAYER, sprites->at(i)->model_matrix);
						thrust = !thrust;
					} else
						thrustSprite->model_matrix = sprites->at(i)->model_matrix;
				} else
					if(thrust == true) {
						effect_sprites->removeSpriteType(JET_PLAYER);
						thrust = !thrust;
					}
				break;
			}
			case PROJECTILE: {
				bool exists = Projectile::Get()->calc_model_Projectile(sprites->at(i), dt);
				if(exists == false)
					removeSprite(i);
				break;
			}
			case ROCKET: {
				bool exists = Rocket::Get()->calc_model_Rocket(sprites->at(i), dt);
				jet_rocket->model_matrix = sprites->at(i)->model_matrix;
				if(exists == false) {
					removeSprite(i);
					effect_sprites->removeSpriteType(JET_ROCKET);
				}
				break;
			}
			case ENEMY1: {
				Enemy1::Get()->calc_model_Enemy1(sprites->at(i), dt);
				break;
			}
		}
	}
}

bool SpriteManager::detectCollision(Sprite::aabb AABB_1, Sprite::aabb AABB_2) {

	if(AABB_1.max.x < AABB_2.min.x || AABB_1.min.x > AABB_2.max.x) 
		return false;
	if(AABB_1.max.y < AABB_2.min.y || AABB_1.min.y > AABB_2.max.y)
		return false;

	return true;
}

void SpriteManager::onColide(Sprite *s, int index) {

	switch(s->type) {

		case PLAYER: {
			removeSprite(index);
			break;
		}
		case PROJECTILE: {
			removeSprite(index);
			break;
		}	
		case ENEMY1: {
			removeSprite(index);
			break;
		}
	}
}

void SpriteManager::handleCollisions() {

	for(int i=0; i<sprites->size(); i++) {

		if(sprites->at(i)->type == PLAYER || sprites->at(i)->type == PROJECTILE) {
		
			for(int j=0; j<sprites->size(); j++) {

				if(sprites->at(j)->type != PLAYER && sprites->at(j)->type != PROJECTILE && sprites->at(j)->type != ROCKET) {

					if(detectCollision(sprites->at(i)->get_AABB(sprites->at(i)->model_matrix, true), 
										sprites->at(j)->get_AABB(sprites->at(j)->model_matrix, true)) == true) {

						onColide(sprites->at(i), i);
						onColide(sprites->at(j), j);
					}
				}
			}
		}
	}
}

void SpriteManager::drawSprites(Shader *shader, float dt) {

	glUseProgram (shader->program);

	glUniformMatrix4fv(shader->location_projection_matrix,1,false,glm::value_ptr(projection_matrix));
	glUniformMatrix4fv(shader->location_view_matrix,1,false,glm::value_ptr(view_matrix));

	for(int i=0; i<sprites->size(); i++) {

		glUniformMatrix4fv(shader->location_model_matrix,1,false,glm::value_ptr(sprites->at(i)->model_matrix));
		glUniform1f(shader->location_isAnimated, sprites->at(i)->texture->isAnimated);
		glUniform1f(shader->location_texRatio, sprites->at(i)->texture->texRatio);

		if(sprites->at(i)->texture->isAnimated == 1.0f) {

			glUniform1f(shader->location_frame, sprites->at(i)->currentAnimation.current_frame);
			sprites->at(i)->currentAnimation.current_time += dt;
			float anim_len = sprites->at(i)->currentAnimation.end_frame - sprites->at(i)->currentAnimation.begin_frame;
			float time_len = anim_len / sprites->at(i)->currentAnimation.speed;
			if(sprites->at(i)->currentAnimation.current_time >= time_len)
				sprites->at(i)->currentAnimation.current_time = 0.0f;
			sprites->at(i)->currentAnimation.current_frame = floor(sprites->at(i)->currentAnimation.begin_frame + 
																	sprites->at(i)->currentAnimation.current_time * 
																	sprites->at(i)->currentAnimation.speed);
		}
		else
			glUniform1f(shader->location_frame, 0.0f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sprites->at(i)->texture->id);
		glUniform1i(shader->location_texture, 0);

		glBindVertexArray(sprites->at(i)->vao);
		glDrawElements(GL_TRIANGLES, sprites->at(i)->nr_indices, GL_UNSIGNED_BYTE, NULL);
	}
}