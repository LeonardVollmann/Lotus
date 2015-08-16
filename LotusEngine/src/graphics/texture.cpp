#include "texture.hpp"
#include "../../ext/stb_image.h"

#include <iostream>
#include <cassert>

namespace lotus { namespace graphics {

	TextureResource::TextureResource(const std::string &fileName) :
		Resource(fileName)
	{
		int width, height, numComponents;
		unsigned char *image = stbi_load(("res/textures/" + fileName).c_str(), &width, &height, &numComponents, 4);

		if (image == nullptr)
		{
			std::cerr << "ERROR: Failed to load image: " << fileName << std::endl;
		}

		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

		stbi_image_free(image);

		if (m_textureID == 0)
		{
			std::cerr << "ERROR: Failed to create texture: " << fileName << std::endl;
		}
	}

	TextureResource::~TextureResource()
	{
		glDeleteTextures(1, &m_textureID);
	}

	Texture::Texture(const std::string &fileName)
	{
		m_textureResource = ResourceManager::get<TextureResource>(fileName);
	}

	Texture::~Texture()
	{
		m_textureResource->removeReference();
	}

	void Texture::bind(unsigned int unit) const
	{
		assert(unit >= 0 && unit <= 31);

		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, m_textureResource->getTextureID());
	}

} }
