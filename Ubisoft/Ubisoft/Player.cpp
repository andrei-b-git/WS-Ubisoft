#include "stdafx.h"
#include "common.h"
#include "Player.h"

Player Player::me;


Player::Player() {

	speed = p_speed;
}

Player::Player(TextureManager *textures) {

	sprite = new Sprite(PLAYER, glm::vec3(0.0f, -winRatio/3, 0.0f), glm::vec2(winRatio/10, winRatio/10));
	sprite->set_texture(textures->addTexture("../resurse/Player/strip_player.png", 1.0f));
	set_anim(sprite, IDLE);
	speed = p_speed;
}

Player::~Player() {}

Player* Player::Get() {

	return &me;
}

bool Player::verify_anim(Sprite* sprite, int type) {

	switch(type) {
		case LEFT:
			return sprite->verify_frames(p_left_begin, p_left_end);
			break;
		case RIGHT:
			return sprite->verify_frames(p_right_begin, p_right_end);
			break;
		case UP:
			return sprite->verify_frames(p_up_begin, p_up_end);
			break;
		case IDLE:
			return sprite->verify_frames(p_idle_begin, p_idle_end);
			break;
		default:
			return false;
	}	
}

void Player::set_anim(Sprite* sprite, int type) {

	switch(type) {
		case LEFT:
			sprite->set_frames(p_left_begin, p_left_end);
			break;
		case RIGHT:
			sprite->set_frames(p_right_begin, p_right_end);
			break;
		case UP:
			sprite->set_frames(p_up_begin, p_up_end);
			break;
		case IDLE:
			sprite->set_frames(p_idle_begin, p_idle_end);
			break;
	}
}

bool Player::calc_model_Player(Sprite* sprite, float dt) {

	bool modified = false;
	glm::vec3 pos = sprite->pos;
	glm::vec3 dir = glm::vec3();

	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_A)) {
		dir.x = -1.0f;
		if(verify_anim(sprite, LEFT) == false && modified == false)
			set_anim(sprite, LEFT);
		modified = true;
	}
	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_D)) {
		dir.x = 1.0f;
		if(verify_anim(sprite, RIGHT) == false && modified == false)
			set_anim(sprite, RIGHT);
		modified = true;
	}
	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_W)) {
		dir.y = 1.0f;
		if(verify_anim(sprite, UP) == false && modified == false)
			set_anim(sprite, UP);
		modified = true;
	}
	if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_S)) {
		dir.y = -1.0f;
		if(verify_anim(sprite, IDLE) == false && modified == false)
			set_anim(sprite, IDLE);
		modified = true;
	}
	if(modified == true) {
		dir = glm::normalize(dir);
		pos += dir*speed*dt;
		glm::mat4 model_matrix = glm::translate(glm::mat4(), pos);
		if(sprite->isInside(model_matrix)) {
			sprite->pos = pos;
			sprite->model_matrix = model_matrix;
		}
		if(verify_anim(sprite, IDLE) == false)
			return true;
		return false;
	}
	else {
		if(verify_anim(sprite, IDLE) == false)
			set_anim(sprite, IDLE);
		return false;
	}
}
