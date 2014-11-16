#pragma once

#include "Sprite.h"
#include "TextureManager.h"
#include <time.h>


class Enemy2 {

private:
	static Enemy2 me;
	float speed;

public:
	Sprite *sprite;

	Enemy2();
	Enemy2(TextureManager *textures);
	~Enemy2();
	static Enemy2* Get();
	bool calc_model_Enemy2(Sprite* &sprite, double dt);
};