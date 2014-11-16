#pragma once

#include "Sprite.h"
#include "TextureManager.h"


class Rocket {

private:
	static Rocket me; 
	double speed;

public:
	Sprite *sprite;

	Rocket();
	Rocket(glm::vec3 center, TextureManager *textures);
	~Rocket();
	static Rocket* Get();
	bool calc_model_Rocket(Sprite* &sprite, double dt);
};