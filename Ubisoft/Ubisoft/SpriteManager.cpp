#include "stdafx.h"
#include "SpriteManager.h"
#include "Player.h"
#include "Projectile.h"
#include "Rocket.h"
#include "Enemy1.h"
#include "Enemy2.h"

Sprite* SpriteManager::player;


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

void SpriteManager::addUiSprite(int type, float offset) {

	Sprite *s;

	switch(type) {
		case SCORE: {
			s = new Sprite(SCORE, glm::vec3(-winRatio*11/12, -winRatio/2.2, 0.0f), 
									glm::vec2(winRatio/13, winRatio/24));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/UI/Score.png", 0.0f, false));
			sprites->push_back(s);
			break;
		}
		case RED_BAR: {
			s = new Sprite(RED_BAR, glm::vec3(-winRatio*5/6, -winRatio/2, 0.0f), 
									glm::vec2(winRatio/7, winRatio/70));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/UI/red_button14.png", 0.0f, false));
			sprites->push_back(s);
			break;
		}
		case GREEN_BAR: {
			s = new Sprite(GREEN_BAR, glm::vec3(-winRatio*5/6, -winRatio/2, 0.0f), 
									glm::vec2(winRatio/7, winRatio/70));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/UI/green_button00.png", 0.0f, false));
			sprites->push_back(s);
			break;
		}
		case NUMBER_0: {
			s = new Sprite(NUMBER_0, glm::vec3(-winRatio*8.5/12 - offset, -winRatio/2.2, 0.0f), 
									glm::vec2(winRatio/70, winRatio/70));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/UI/hud_0.png", 0.0f, false));
			sprites->push_back(s);
			break;
		}
		case NUMBER_1: {
			s = new Sprite(NUMBER_1, glm::vec3(-winRatio*8.5/12 - offset, -winRatio/2.2, 0.0f), 
									glm::vec2(winRatio/70, winRatio/70));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/UI/hud_1.png", 0.0f, false));
			sprites->push_back(s);
			break;
		}
		case NUMBER_2: {
			s = new Sprite(NUMBER_2, glm::vec3(-winRatio*8.5/12 - offset, -winRatio/2.2, 0.0f), 
									glm::vec2(winRatio/70, winRatio/70));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/UI/hud_2.png", 0.0f, false));
			sprites->push_back(s);
			break;
		}
		case NUMBER_3: {
			s = new Sprite(NUMBER_3, glm::vec3(-winRatio*8.5/12 - offset, -winRatio/2.2, 0.0f), 
									glm::vec2(winRatio/70, winRatio/70));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/UI/hud_3.png", 0.0f, false));
			sprites->push_back(s);
			break;
		}
		case NUMBER_4: {
			s = new Sprite(NUMBER_4, glm::vec3(-winRatio*8.5/12 - offset, -winRatio/2.2, 0.0f), 
									glm::vec2(winRatio/70, winRatio/70));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/UI/hud_4.png", 0.0f, false));
			sprites->push_back(s);
			break;
		}
		case NUMBER_5: {
			s = new Sprite(NUMBER_5, glm::vec3(-winRatio*8.5/12 - offset, -winRatio/2.2, 0.0f), 
									glm::vec2(winRatio/70, winRatio/70));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/UI/hud_5.png", 0.0f, false));
			sprites->push_back(s);
			break;
		}
		case NUMBER_6: {
			s = new Sprite(NUMBER_6, glm::vec3(-winRatio*8.5/12 - offset, -winRatio/2.2, 0.0f), 
									glm::vec2(winRatio/70, winRatio/70));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/UI/hud_6.png", 0.0f, false));
			sprites->push_back(s);
			break;
		}
		case NUMBER_7: {
			s = new Sprite(NUMBER_7, glm::vec3(-winRatio*8.5/12 - offset, -winRatio/2.2, 0.0f), 
									glm::vec2(winRatio/70, winRatio/70));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/UI/hud_7.png", 0.0f, false));
			sprites->push_back(s);
			break;
		}
		case NUMBER_8: {
			s = new Sprite(NUMBER_8, glm::vec3(-winRatio*8.5/12 - offset, -winRatio/2.2, 0.0f), 
									glm::vec2(winRatio/70, winRatio/70));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/UI/hud_8.png", 0.0f, false));
			sprites->push_back(s);
			break;
		}
		case NUMBER_9: {
			s = new Sprite(NUMBER_9, glm::vec3(-winRatio*8.5/12 - offset, -winRatio/2.2, 0.0f), 
									glm::vec2(winRatio/70, winRatio/70));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/UI/hud_9.png", 0.0f, false));
			sprites->push_back(s);
			break;
		}
		case RKT_ICON: {
			s = new Sprite(RKT_ICON, glm::vec3(winRatio*20/21 - offset, -winRatio/2.1f, 0.0f), 
									glm::vec2(winRatio/25, winRatio/25));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/UI/rocket_type_A0001.png", 0.0f, false));
			sprites->push_back(s);
			break;
		}
		case READY: {
			s = new Sprite(READY, glm::vec3(0.0f, 0.0f, 0.0f), 
									glm::vec2(winRatio/5, winRatio/25));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/UI/textGetReady.png", 0.0f, false));
			sprites->push_back(s);
			break;
		}
		case OVER: {
			s = new Sprite(OVER, glm::vec3(0.0f, 0.0f, 0.0f), 
									glm::vec2(winRatio/5, winRatio/25));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/UI/textGameOver.png", 0.0f, false));
			sprites->push_back(s);
			break;
		}
	}
}

void SpriteManager::addEffectSprite(int type, Sprite *ref, float offset) {

	Sprite *s;

	switch(type) {
		case BACKGROUND: {
			if(offset < 0.0f) {
				s = new Sprite(BACKGROUND, glm::vec3(0.0f, winRatio, 0.0f), 
											glm::vec2(outer_lim*winRatio, outer_lim*winRatio));
				assert(s);
				s->set_texture(textures->addTexture("../resurse/Backgrounds/Background2.png", 0.0f, false));
				sprites->push_back(s);
			} else {
				s = new Sprite(BACKGROUND, glm::vec3(0.0f, 2*winRatio, 0.0f), 
											glm::vec2(outer_lim*winRatio, outer_lim*winRatio));
				assert(s);
				switch((int)offset) {
					case 1: {
						s->set_texture(textures->addTexture("../resurse/Backgrounds/Background2.png", 0.0f, false));
						break;
					}
					case 2: {
						s->set_texture(textures->addTexture("../resurse/Backgrounds/Background4.png", 0.0f, false));
						break;
					}
					case 3: {
						s->set_texture(textures->addTexture("../resurse/Backgrounds/Background1.png", 0.0f, false));
						break;
					}
					case 4: {
						s->set_texture(textures->addTexture("../resurse/Backgrounds/Background3.png", 0.0f, false));
						break;
					}
				}
				sprites->push_back(s);
				break;
			}
			break;
		}
		case THRUST: {
			switch(ref->type) {
				case PLAYER: {
					s = new Sprite(THRUST, glm::vec3(p_coords_x, p_coords_y - winRatio/8, 0.0f), 
											glm::vec2(winRatio/20, winRatio/20));
					assert(s);
					s->set_texture(textures->addTexture("../resurse/FX/thrust_yellow2.png", 1.0f, false));
					s->set_frames(jp_idle_begin, jp_idle_end);
					s->model_matrix = ref->model_matrix;
					s->ref = ref;
					sprites->push_back(s);
					break;
				}
				case ROCKET: {
					s = new Sprite(THRUST, glm::vec3(p_coords_x + offset * winRatio/19, p_coords_y - winRatio/20, 0.0f), 
											glm::vec2(winRatio/35, winRatio/35));
					assert(s);
					s->set_texture(textures->addTexture("../resurse/FX/thrust_green.png", 1.0f, false));
					s->set_frames(jr_idle_begin, jr_idle_end);
					s->model_matrix = player->model_matrix;
					s->ref = ref;
					sprites->push_back(s);
					break;
				}
				case ENEMY1: {
					s = new Sprite(THRUST, glm::vec3(ref->center.x, ref->center.y + winRatio/11, 0.0f), 
											glm::vec2(winRatio/40, winRatio/20));
					assert(s);
					s->set_texture(textures->addTexture("../resurse/FX/thrust_orange_big.png", 1.0f, true));
					s->texture->texRatio = je1_texRatio;
					s->set_frames(je1_idle_begin, je1_idle_end);
					s->model_matrix = ref->model_matrix;
					s->ref = ref;
					sprites->push_back(s);
					break;
				}
			}
			break;
		}
		case GUN_BLAST: {
			switch(ref->type) {
				case PLAYER: {
					s = new Sprite(GUN_BLAST, glm::vec3(p_coords_x, p_coords_y + winRatio/11, 0.0f), 
												glm::vec2(winRatio/20, winRatio/20));
					assert(s);
					s->set_texture(textures->addTexture("../resurse/FX/gun_blast_blue.png", 1.0f, false));
					s->set_frames(gp_idle_begin, gp_idle_end);
					s->model_matrix = ref->model_matrix;
					s->ref = ref;
					sprites->push_back(s);
					break;
				}
				case ROCKET: {
					s = new Sprite(GUN_BLAST, glm::vec3(p_coords_x + offset * winRatio/19, p_coords_y, 0.0f), 
												glm::vec2(winRatio/30, winRatio/30));
					assert(s);
					s->set_texture(textures->addTexture("../resurse/FX/gun_blast.png", 1.0f, false));
					s->set_frames(gr_idle_begin, gr_idle_end);
					s->model_matrix = player->model_matrix;
					s->ref = player;
					sprites->push_back(s);
					break;
				}
				case ENEMY1: {
					s = new Sprite(GUN_BLAST, glm::vec3(ref->center.x, ref->center.y - winRatio/20, 0.0f), 
												glm::vec2(winRatio/30, winRatio/30));
					assert(s);
					s->set_texture(textures->addTexture("../resurse/FX/gun_blast_red.png", 1.0f, false));
					s->set_frames(ge1_idle_begin, ge1_idle_end);
					s->model_matrix = ref->model_matrix;
					s->ref = ref;
					sprites->push_back(s);
					break;
				}
			}
			break;
		}
		case EXPLOSION1: {
			s = new Sprite(EXPLOSION1, glm::vec3(ref->center.x, ref->center.y, 0.0f), 
										glm::vec2(winRatio/15, winRatio/15));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/Explosions/Exp_type_A.png", 1.0f, false));
			s->set_frames(ex1_idle_begin, ex1_idle_end);
			s->currentAnimation.speed = anim_speed*1.5f;
			s->model_matrix = ref->model_matrix;
			s->ref = ref;
			sprites->push_back(s);			
			break;
		}
		case EXPLOSION2: {
			s = new Sprite(EXPLOSION2, glm::vec3(ref->center.x, ref->center.y, 0.0f), 
										glm::vec2(winRatio/15, winRatio/15));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/Explosions/Turret_blast_strip.png", 1.0f, false));
			s->set_frames(ex2_idle_begin, ex2_idle_end);
			s->currentAnimation.speed = anim_speed*1.5f;
			s->model_matrix = ref->model_matrix;
			s->ref = ref;
			sprites->push_back(s);			
			break;
		}
		case EXPLOSION3: {
			s = new Sprite(EXPLOSION3, glm::vec3(ref->center.x, ref->center.y, 0.0f), 
										glm::vec2(winRatio/6, winRatio/6));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/Explosions/Exp_type_C.png", 1.0f, false));
			s->set_frames(ex3_idle_begin, ex3_idle_end);
			s->model_matrix = ref->model_matrix;
			s->ref = ref;
			sprites->push_back(s);			
			break;
		}
		case EXPLOSION4: {
			s = new Sprite(EXPLOSION4, glm::vec3(ref->center.x, ref->center.y, 0.0f), 
										glm::vec2(winRatio/4, winRatio/4));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/Explosions/Fort_exp_strip.png", 1.0f, false));
			s->set_frames(ex4_idle_begin, ex4_idle_end);
			s->model_matrix = ref->model_matrix;
			s->ref = ref;
			sprites->push_back(s);			
			break;
		}
		case EXPLOSION5: {
			s = new Sprite(EXPLOSION5, glm::vec3(ref->center.x, ref->center.y, 0.0f), 
										glm::vec2(winRatio/4, winRatio/4));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/Explosions/Vehicle_exp_strip.png", 1.0f, false));
			s->set_frames(ex5_idle_begin, ex5_idle_end);
			s->model_matrix = ref->model_matrix;
			s->ref = ref;
			sprites->push_back(s);			
			break;
		}
	}
}

void SpriteManager::addCrashSprite(int type, Sprite *ref, SpriteManager *effect_sprites) {

	switch(type) {
		case PLAYER: {
			Player *p = new Player(textures);
			assert(p);
			player = p->sprite;
			sprites->push_back(p->sprite);
			delete p;
			break;
		}
		case PROJECTILE: {
			Projectile *pr = new Projectile(ref, textures);
			assert(pr);
			pr->sprite->original_model_matrix = ref->model_matrix;
			pr->sprite->ref = ref;
			pr->sprite->ref_type = ref->type;
			sprites->push_back(pr->sprite);
			delete pr;
			effect_sprites->addEffectSprite(GUN_BLAST, ref, 0.0f);
			break;
		}
		case ROCKET: {
			Rocket *r1 = new Rocket(glm::vec3(p_coords_x - winRatio/19, p_coords_y, 0.0f), textures);
			assert(r1);
			r1->sprite->original_model_matrix = player->model_matrix;
			sprites->push_back(r1->sprite);
			effect_sprites->addEffectSprite(THRUST, r1->sprite, -1.0f);
			effect_sprites->addEffectSprite(GUN_BLAST, r1->sprite, -1.0f);
			delete r1;

			Rocket *r2 = new Rocket(glm::vec3(p_coords_x + winRatio/19, p_coords_y, 0.0f), textures);
			assert(r2);
			r2->sprite->original_model_matrix = player->model_matrix;
			sprites->push_back(r2->sprite);
			effect_sprites->addEffectSprite(THRUST, r2->sprite, 1.0f);
			effect_sprites->addEffectSprite(GUN_BLAST, r2->sprite, 1.0f);
			delete r2;
			break;
		}
		case BONUS: {
			Sprite *s = new Sprite(BONUS, glm::vec3(0.0f, 0.0f, 0.0f), 
										glm::vec2(winRatio/20, winRatio/20));
			assert(s);
			s->set_texture(textures->addTexture("../resurse/Rockets/strip_rocket_type_A.png", 1.0f, false));
			s->set_frames(b_idle_begin, b_idle_end);
			sprites->push_back(s);			
			break;
		}
		case ENEMY1: {
			Enemy1 *e1 = new Enemy1(textures);
			assert(e1);
			sprites->push_back(e1->sprite);
			effect_sprites->addEffectSprite(THRUST, e1->sprite, 0.0f);
			delete e1;
			break;
		}
		case ENEMY2: {
			Enemy2 *e2 = new Enemy2(textures);
			assert(e2);
			sprites->push_back(e2->sprite);
			delete e2;
			break;
		}
	}
}

void SpriteManager::removeSprite(int index) {

	delete sprites->at(index);
	sprites->erase(sprites->begin() + index);
}

void SpriteManager::clearScore() {

	for(int i=0; i<sprites->size(); i++)
		if(sprites->at(i)->type / 10 == 2) {
			removeSprite(i);
			i--;
		}
}

void SpriteManager::clearRockets() {

	for(int i=0; i<sprites->size(); i++)
		if(sprites->at(i)->type == RKT_ICON) {
			removeSprite(i);
			i--;
		}
}

void SpriteManager::update_background(double dt) {

	static float offset = 2.0f;
	static float fact = 1.9f;

	if(sprites->size() == 1 && sprites->at(0)->pos.y <= -fact*winRatio) {
		if(offset > 4.0f)
			offset = 1.0f;
		addEffectSprite(BACKGROUND, NULL, offset);
		offset ++;
		fact = 3.0f;
	}
	if(sprites->at(0)->pos.y <= -(fact+1.0f)*winRatio)
		removeSprite(0);

	for(int i=0; i<sprites->size(); i++) {
		sprites->at(i)->pos.y -= (float)(b_speed*dt);
		sprites->at(i)->model_matrix = glm::translate(sprites->at(i)->pos);
	}
}

void SpriteManager::update_crash_model(SpriteManager *effect_sprites, double t, double dt) {

	static bool p_thrust = false;
	static float jp_scale = 0.0f;

	for(int i=0; i<sprites->size(); i++) {

		switch(sprites->at(i)->type) {

			case PLAYER: {
				bool modified = Player::Get()->calc_model_Player(sprites->at(i), dt);
				if(modified == true) {
					if(p_thrust == false) {
						effect_sprites->addEffectSprite(THRUST, player, 0.0f);
						p_thrust = !p_thrust;
					}
					for(int j=0; j<effect_sprites->sprites->size(); j++) {
						if(effect_sprites->sprites->at(j)->ref == sprites->at(i)) {
							effect_sprites->sprites->at(j)->model_matrix = sprites->at(i)->model_matrix;
							if(effect_sprites->sprites->at(j)->type == THRUST)
								if(jp_scale < 1.0f) {
									effect_sprites->sprites->at(j)->model_matrix *= 
										glm::translate(glm::vec3(p_coords_x, p_coords_y - winRatio/8 + winRatio/20, 0.0f));
									effect_sprites->sprites->at(j)->model_matrix *= 
										glm::scale(glm::vec3(jp_scale, jp_scale, 0.0f));
									effect_sprites->sprites->at(j)->model_matrix *= 
										glm::translate(glm::vec3(-p_coords_x, -p_coords_y + winRatio/8 - winRatio/20, 0.0f));
									jp_scale += (float)(jp_speed * dt);
								}
						}
					}
				} else
					if(p_thrust == true) {
						for(int j=0; j<effect_sprites->sprites->size(); j++)
							if(effect_sprites->sprites->at(j)->ref == sprites->at(i) && 
							   effect_sprites->sprites->at(j)->type == THRUST) {
								if(jp_scale > 0.0f) {
									effect_sprites->sprites->at(j)->model_matrix *= 
										glm::translate(glm::vec3(p_coords_x, p_coords_y - winRatio/8 + winRatio/20, 0.0f));
									effect_sprites->sprites->at(j)->model_matrix *= 
										glm::scale(glm::vec3(jp_scale, jp_scale, 0.0f));
									effect_sprites->sprites->at(j)->model_matrix *= 
										glm::translate(glm::vec3(-p_coords_x, -p_coords_y + winRatio/8 - winRatio/20, 0.0f));
									jp_scale -= (float)(jp_speed * dt);
								}
								else {
									effect_sprites->removeSprite(j);
									p_thrust = !p_thrust;
								}
							}
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
				if(exists == true) {
					for(int j=0; j<effect_sprites->sprites->size(); j++)
						if(effect_sprites->sprites->at(j)->ref == sprites->at(i))
							effect_sprites->sprites->at(j)->model_matrix = sprites->at(i)->model_matrix;
				} else {
					for(int j=0; j<effect_sprites->sprites->size(); j++)
						if(effect_sprites->sprites->at(j)->ref == sprites->at(i))
							effect_sprites->removeSprite(j);
					removeSprite(i);
				}
				break;
			}
			case BONUS: {
				sprites->at(i)->pos.y -= (float)(b_speed*dt);
				sprites->at(i)->model_matrix = glm::translate(sprites->at(i)->pos);
				break;
			}
			case ENEMY1: {
				if(t - sprites->at(i)->previousTime > e1pr_delay) {
					sprites->at(i)->previousTime = t;
					addCrashSprite(PROJECTILE, sprites->at(i), effect_sprites);
				}
				bool exists = Enemy1::Get()->calc_model_Enemy1(sprites->at(i), dt);
				if(exists == true) {
					for(int j=0; j<effect_sprites->sprites->size(); j++)
						if(effect_sprites->sprites->at(j)->ref == sprites->at(i))
							effect_sprites->sprites->at(j)->model_matrix = sprites->at(i)->model_matrix;
				} else {
					for(int j=0; j<effect_sprites->sprites->size(); j++)
						if(effect_sprites->sprites->at(j)->ref == sprites->at(i))
							effect_sprites->removeSprite(j);
					removeSprite(i);
				}
				break;
			}
			case ENEMY2: {
				bool exists = Enemy2::Get()->calc_model_Enemy2(sprites->at(i), dt);
				if(exists == false)
					removeSprite(i);
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

bool SpriteManager::passColideCond(Sprite *a, Sprite *b) {

	return !((a->type == b->type) ||
			(a->type == PLAYER && b->type == PROJECTILE && b->ref->type == PLAYER) ||
			(b->type == PLAYER && a->type == PROJECTILE && a->ref->type == PLAYER) ||
			(a->type == PLAYER && b->type == ROCKET) ||
			(b->type == PLAYER && a->type == ROCKET) ||
			(a->type == ROCKET && b->type == PROJECTILE) ||
			(b->type == ROCKET && a->type == PROJECTILE) ||
			(a->type == ENEMY1 && b->type == PROJECTILE && b->ref->type == ENEMY1) ||
			(b->type == ENEMY1 && a->type == PROJECTILE && a->ref->type == ENEMY1) ||
			(a->type == BONUS && b->type != PLAYER) ||
			(b->type == BONUS && a->type != PLAYER) ||
			(a->type == ENEMY1 && b->type == ENEMY2) ||
			(b->type == ENEMY1 && a->type == ENEMY2) ||
			(a->type == ENEMY2 && b->type == PROJECTILE && b->ref->type == ENEMY1) ||
			(b->type == ENEMY2 && a->type == PROJECTILE && a->ref->type == ENEMY1));
}

void SpriteManager::onColide(Sprite *s, int index, SpriteManager *effect_sprites, SpriteManager *UI_sprites) {

	switch(s->type) {

		case PLAYER: {
			if(s->crasher->type != BONUS) {
				s->own.hp -= s->crasher->own.dmg;

				effect_sprites->addEffectSprite(EXPLOSION1, s, 0.0f);

				for(int j=0; j<UI_sprites->sprites->size(); j++)
					if(UI_sprites->sprites->at(j)->type == GREEN_BAR) {
						Sprite *hp = UI_sprites->sprites->at(j);
						hp->model_matrix = glm::translate(glm::vec3(-winRatio*5/6 - winRatio/7, -winRatio/2, 0.0f));
						if(s->own.hp < 0.0f)
							s->own.hp = 0.0f;
						hp->model_matrix *= glm::scale(glm::vec3(s->own.hp/100.0f, 1.0f, 0.0f));
						hp->model_matrix *= glm::translate(glm::vec3( winRatio*5/6 + winRatio/7, winRatio/2, 0.0f));
					}
				if(s->own.hp == 0.0f) {
					for(int j=0; j<effect_sprites->sprites->size(); j++)
						if(effect_sprites->sprites->at(j)->ref == s)
							effect_sprites->removeSprite(j);
					effect_sprites->addEffectSprite(EXPLOSION4, s, 0.0f);
					removeSprite(index);
					GAME_OVER = true;
				}
			}
			break;
		}
		case PROJECTILE: {
			removeSprite(index);
			break;
		}
		case ROCKET: {
			for(int i=0; i<effect_sprites->sprites->size(); i++)
				if(effect_sprites->sprites->at(i)->ref == sprites->at(index))
					effect_sprites->removeSprite(i);
			removeSprite(index);
			break;
		}
		case BONUS: {
			nr_rockets ++;
			removeSprite(index);
			break;
		}
		case ENEMY1: {
			if(s->crasher->type != PLAYER && s->crasher->type != PROJECTILE && s->crasher->type != ROCKET)
				s->own.hp -= ppr_dmg;
			else
				s->own.hp -= s->crasher->own.dmg;
			s->own.red += e1_red_rate;

			effect_sprites->addEffectSprite(EXPLOSION2, s, 0.0f);

			score += s->own.hit_score;

			if(s->own.hp <= 0.0f) {
				for(int i=0; i<effect_sprites->sprites->size(); i++)
					if(effect_sprites->sprites->at(i)->ref == s)
						effect_sprites->removeSprite(i);
				score += s->own.kill_score;
				effect_sprites->addEffectSprite(EXPLOSION3, s, 0.0f);
				nr_e1_killed ++;
				nr_e2_killed = 0;
				removeSprite(index);
			}
			break;
		}
		case ENEMY2: {
			if(s->crasher->type != PLAYER && s->crasher->type != PROJECTILE && s->crasher->type != ROCKET)
				s->own.hp -= ppr_dmg;
			else
				s->own.hp -= s->crasher->own.dmg;
			s->own.red += e2_red_rate;

			effect_sprites->addEffectSprite(EXPLOSION2, s, 0.0f);

			score += s->own.hit_score;

			if(s->own.hp <= 0.0f) {
				score += s->own.kill_score;
				effect_sprites->addEffectSprite(EXPLOSION5, s, 0.0f);
				nr_e2_killed ++;
				nr_e1_killed = 0;
				removeSprite(index);
			}
			break;
		}
	}
}

void SpriteManager::handleCollisions(SpriteManager *effect_sprites, SpriteManager *UI_sprites) {

	for(int i=0; i<sprites->size(); i++) {

		if(sprites->at(i)->hasColided == false) {
		
			for(int j=0; j<sprites->size(); j++) {

				if(sprites->at(j)->hasColided == false) {

					if(passColideCond(sprites->at(i), sprites->at(j)) == true) {

						if(detectCollision(sprites->at(i)->get_AABB(sprites->at(i)->model_matrix, true), 
											sprites->at(j)->get_AABB(sprites->at(j)->model_matrix, true)) == true) {

							sprites->at(i)->hasColided = true;
							sprites->at(i)->crasher = sprites->at(j);
							sprites->at(j)->hasColided = true;
							sprites->at(j)->crasher = sprites->at(i);
						}
					}
				}
			}
		}
	}
	for(int i=0; i<sprites->size(); i++)
		if(sprites->at(i)->hasColided == true) {
			sprites->at(i)->hasColided = false;
			onColide(sprites->at(i), i, effect_sprites, UI_sprites);
		}
}

void SpriteManager::update_animation(double dt) {

	for(int i=0; i<sprites->size(); i++) {
		sprites->at(i)->currentAnimation.current_time += dt;
		double anim_len = sprites->at(i)->currentAnimation.end_frame - sprites->at(i)->currentAnimation.begin_frame;
		double time_len = anim_len / sprites->at(i)->currentAnimation.speed;
		if(sprites->at(i)->currentAnimation.current_time >= time_len)
			sprites->at(i)->currentAnimation.current_time = 0.0f;
		sprites->at(i)->currentAnimation.current_frame = (float)floor(sprites->at(i)->currentAnimation.begin_frame + 
																sprites->at(i)->currentAnimation.current_time * 
																sprites->at(i)->currentAnimation.speed);
	}
}

void SpriteManager::drawSprites(Shader *shader, bool clamp) {

	glUseProgram (shader->program);

	glUniformMatrix4fv(shader->location_projection_matrix,1,false,glm::value_ptr(projection_matrix));

	if(GAME_OVER == false) {
		glm::vec3 alt_pos = player->pos;
		alt_pos.y = 0.0f;
		glm::mat4 alt_model = glm::translate(alt_pos);
		if(player->isInside(player->model_matrix, inner_lim, true))
			view_matrix = glm::inverse(alt_model);
	}
	for(int i=0; i<sprites->size(); i++) {

		if(clamp == true)
			glUniformMatrix4fv(shader->location_view_matrix,1,false,glm::value_ptr(glm::mat4()));
		else
			glUniformMatrix4fv(shader->location_view_matrix,1,false,glm::value_ptr(view_matrix));

		glUniformMatrix4fv(shader->location_model_matrix,1,false,glm::value_ptr(sprites->at(i)->model_matrix));
		glUniform1f(shader->location_isAnimated, sprites->at(i)->texture->isAnimated);
		glUniform1f(shader->location_texRatio, sprites->at(i)->texture->texRatio);
		glUniform1f(shader->location_red, sprites->at(i)->own.red);

		if(sprites->at(i)->texture->isAnimated == 1.0f)
			glUniform1f(shader->location_frame, sprites->at(i)->currentAnimation.current_frame);
		else
			glUniform1f(shader->location_frame, 0.0f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sprites->at(i)->texture->id);
		glUniform1i(shader->location_texture, 0);

		glBindVertexArray(sprites->at(i)->vao);
		glDrawElements(GL_TRIANGLES, sprites->at(i)->nr_indices, GL_UNSIGNED_BYTE, NULL);

		float current_frame = sprites->at(i)->currentAnimation.current_frame;
		switch(sprites->at(i)->type) {
			case GUN_BLAST: {
				switch(sprites->at(i)->ref->type) {
					case PLAYER: {
						if(sprites->at(i)->center.y != p_coords_y) {
							if(current_frame == gp_idle_end-1)
								removeSprite(i);
						} else {
							if(current_frame == gr_idle_end-1)
								removeSprite(i);
						}
						break;
					}
					case ENEMY1: {
						if(current_frame == ge1_idle_end-1)
							removeSprite(i);					
						break;
					}
				}
				break;
			}
			case EXPLOSION1: {
				if(current_frame == ex1_idle_end-1)
					removeSprite(i);
				break;
			}
			case EXPLOSION2: {
				if(current_frame == ex2_idle_end-1)
					removeSprite(i);
				break;
			}
			case EXPLOSION3: {
				if(current_frame == ex3_idle_end-1)
					removeSprite(i);
				break;
			}
			case EXPLOSION4: {
				if(current_frame == ex4_idle_end-1)
					removeSprite(i);
				break;
			}
			case EXPLOSION5: {
				if(current_frame == ex5_idle_end-1)
					removeSprite(i);
				break;
			}
			default: { break; }
		}
	}
}