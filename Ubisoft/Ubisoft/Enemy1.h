#pragma once

#include "Sprite.h"
#include "TextureManager.h"
#include <time.h>


class Enemy1 {

private:
	static Enemy1 me;
	float speed;

public:
	Sprite *sprite;

	Enemy1();
	Enemy1(TextureManager *textures);
	~Enemy1();
	static Enemy1* Get();
	bool calc_model_Enemy1(Sprite* &sprite, double dt);
};