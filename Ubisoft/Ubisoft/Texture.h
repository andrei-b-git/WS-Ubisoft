#pragma once


class Texture {

private:
	int width;
	int height;

public:
	unsigned int id;
	float texRatio;
	float isAnimated;

	Texture(const char *texture_name, float _isAnimated, bool flip);
	~Texture();
};
