#include "stdafx.h"
#include "SpriteManager.h"
#include "Player.h"
#include "Projectile.h"
#include "Enemy1.h"

Sprite *player;
bool thrust;
Sprite *thrustSprite;


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