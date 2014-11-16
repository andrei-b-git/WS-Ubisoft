#pragma once

#include "Sprite.h"
#include "TextureManager.h"


class Projectile {

private:
	static Projectile me; 

public:
	Sprite *sprite;

	Projectile();
	Projectile(Sprite *ref, TextureManager *textures);
	~Projectile();
	static Projectile* Get();
	bool calc_model_Projectile(Sprite* &sprite, double dt);
};