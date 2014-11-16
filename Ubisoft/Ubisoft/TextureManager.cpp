#include "stdafx.h"
#include "TextureManager.h"
#include <assert.h>


TextureManager::TextureManager() {

	textures = new std::map<std::string, Texture*>;
	assert(textures);
}

TextureManager::~TextureManager() {

	for(std::map<string, Texture*>::iterator i = textures->begin(); i != textures->end(); i++)
		delete i->second;

	delete textures;
}

Texture* TextureManager::addTexture(const char *texture_name, float isAnimated, bool flip) {

	std::map<std::string, Texture*>::iterator fnd = textures->find(texture_name);
	Texture* needed_img = NULL;
	if(fnd == textures->end()) {

		needed_img = new Texture(texture_name, isAnimated, flip);
		assert(needed_img);
			
		std::pair<std::string, Texture*> ins_t(texture_name, needed_img);
		textures->insert(ins_t);
	}
	else
		needed_img = fnd->second;

	return needed_img;
}