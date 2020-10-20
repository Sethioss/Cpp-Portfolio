#pragma once
#include "libs.h"

#include "vendor/stb_image.h"

class Texture {

private:
	unsigned int textureId;

public:
	Texture(const char* fileName, unsigned int imageFormat);
	~Texture();
	void Use();
	void Unuse();
	void AssignTextureUnit(unsigned int unit) const;
};