#pragma once

#include "Sprite.h"
#include "TextureManager.h"

class Projectile {

private:
	static Projectile me; 
	float speed;

public:
	Sprite *sprite;

	Projectile();
	Projectile(glm::vec3 center, TextureManager *textures);
	~Projectile();
	static Projectile* Get();
	bool calc_model_Projectile(Sprite* &sprite, float dt);
};