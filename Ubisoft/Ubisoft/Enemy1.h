#pragma once

class Enemy1 {

private:
	float speed;

public:
	Sprite *sprite;

	Enemy1() {

		speed = 0.01f;
	}

	Enemy1(TextureManager *textures) {

		sprite = new Sprite(ENEMY1, glm::vec3(0.0f, winRatio/3, 0.0f), glm::vec2(winRatio/15, winRatio/15));
		sprite->set_texture(textures->addTexture("../resurse/Enemies/strip_saucer.png", 1.0f));
		sprite->set_frames(0,15);
		speed = 0.01f;
	}

	~Enemy1() {}

	void calc_model_Enemy1(Sprite* &sprite) {

		glm::vec3 pos = sprite->pos;
		glm::vec3 dir = glm::vec3();

		pos.x += pos.z * speed;

		glm::mat4 model_matrix = glm::translate(glm::mat4(), pos);
/*		if(sprite->isInside(projection_matrix, view_matrix,  model_matrix)) {
			sprite->translation = translation;
			sprite->model_matrix = model_matrix;
		}
		else {
			sprite->translation.z *= -1.0f;
		}*/
	}
};