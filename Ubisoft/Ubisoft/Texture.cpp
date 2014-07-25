#include "stdafx.h"
#include "common.h"
#include "Texture.h"
#include "stb_image.h"
#include "utils.h"


Texture::Texture(const char *texture_name, float _isAnimated) {

	int x, y, n;
	int force_channels = 4;
	unsigned char* image_data = stbi_load(texture_name, &x, &y, &n, force_channels);
	if (!image_data) {
		fprintf(stderr, "ERROR: could not load %s\n", texture_name);
	}
	width = x;
	height = y;

	FlipTexture(image_data, x, y, n);

	id = 0;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data );

	free(image_data);

	texRatio = (float)height/width;
	isAnimated = _isAnimated;
}

Texture::~Texture() {

	glDeleteTextures(1, &id);
}