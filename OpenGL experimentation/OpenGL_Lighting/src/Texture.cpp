#include "texture.h"

Texture::Texture(const char* fileName, unsigned int imageFormat)
{
	stbi_set_flip_vertically_on_load(true);
	//Create the texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//Set parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	//Important variables (Width, height, channels)
	int textureWidth, textureHeight, nrChannels;

	//Define the actual texture data
	unsigned char* data = stbi_load(fileName, &textureWidth, &textureHeight, &nrChannels, 0);

	if (data)
	{
			//Bind the data to the texture and generate mipmaps
			glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, textureWidth, textureHeight, 0, imageFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERR::COULDNT_GENERATE_DATA" << std::endl;
	}

	this->textureId = texture;

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

Texture::~Texture()
{

}

void Texture::AssignTextureUnit(unsigned int unit) const
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, this->textureId);
}

void Texture::Use()
{
	glBindTexture(GL_TEXTURE_2D, this->textureId);
}

void Texture::Unuse()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}