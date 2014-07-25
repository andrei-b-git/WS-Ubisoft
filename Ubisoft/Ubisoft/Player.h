#pragma once

#include "Sprite.h"
#include "TextureManager.h"

enum AnimationTypePlayer
{
	LEFT	= 0,
	RIGHT	= 1,
	UP		= 2,
	IDLE	= 3
};


class Player {

private:
	static Player me; 
	float speed;

public:
	Sprite *sprite;

	Player();
	Player(TextureManager *textures);
	~Player();
	static Player* Get();
	bool verify_anim(Sprite* sprite, int type);
	void set_anim(Sprite* sprite, int type);
	bool calc_model_Player(Sprite* sprite, float dt);
};