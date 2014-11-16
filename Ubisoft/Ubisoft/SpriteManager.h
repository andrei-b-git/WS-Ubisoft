#pragma once

#include "Sprite.h"
#include "TextureManager.h"
#include <vector>

using namespace std;


class SpriteManager {

public:
	std::vector<Sprite*> *sprites;
	TextureManager *textures;
	static Sprite* player;

public:
	SpriteManager();
	~SpriteManager();
	void reserveSprites(int nr);
	void addUiSprite(int type, float offset);
	void addEffectSprite(int type, Sprite *ref, float offset);
	void addCrashSprite(int type, Sprite *ref, SpriteManager *effect_sprites);
	void removeSprite(int index);
	void clearScore();
	void clearRockets();
	void update_background(double dt);
	void update_crash_model(SpriteManager *effect_sprites, double t, double dt);
	bool detectCollision(Sprite::aabb AABB_1, Sprite::aabb AABB_2);
	bool passColideCond(Sprite *a, Sprite *b);
	void onColide(Sprite *s, int index, SpriteManager *effect_sprites, SpriteManager *UI_sprites);
	void handleCollisions(SpriteManager *effect_sprites, SpriteManager *UI_sprites);
	void update_animation(double dt);
	void drawSprites(Shader *shader, bool clamp);
};