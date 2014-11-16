#pragma once

#include "Texture.h"
#include <map>
#include <string>

using namespace std;


class TextureManager {

private:
	std::map<std::string, Texture*> *textures;

public:
	TextureManager();
	~TextureManager();
	Texture* addTexture(const char *texture_name, float isAnimated, bool flip);
};
