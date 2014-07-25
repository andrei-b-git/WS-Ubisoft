#pragma once

#include "Sprite.h"
#include "TextureManager.h"
#include <vector>

using namespace std;


class SpriteManager {

private:
	std::vector<Sprite*> *sprites;
	TextureManager *textures;

public:
	SpriteManager();
	~SpriteManager();
	void reserveSprites(int nr);
	void addEffectSprite(int type, glm::mat4 model_matrix);
	void addCrashSprite(int type);
	void removeSprite(int index);
	void removeSpriteType(int type);
	void update_crash_model(SpriteManager *effect_sprites, float dt);
	void drawSprites(Shader *shader, float dt);
};