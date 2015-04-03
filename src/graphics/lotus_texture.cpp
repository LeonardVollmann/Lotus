#include "lotus_texture.hpp"
#include "../staticlibs/stb_image.h"

#include <iostream>
#include <cassert>

namespace lotus { namespace graphics {

	Texture::Texture(const std::string &fileName)
	{
		int width, height, numComponents;
		unsigned char *image = stbi_load(("res/textures/" + fileName).c_str(), &width, &height, &numComponents, 4);

		if (image == nullptr)
		{
			std::cerr << "ERROR: Failed to load image: " << fileName << std::endl;
		}

		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

		stbi_image_free(image);

		if (m_texture == 0)
		{
			std::cerr << "ERROR: Failed to create texture: " << fileName << std::endl;
		}
	}

	Texture::~Texture()
	{
		glDeleteTextures(0, &m_texture);
	}

	void Texture::bind(unsigned int unit) const
	{
	    assert(unit >= 0 && unit <= 31);
	    
	    glActiveTexture(GL_TEXTURE0 + unit);
	    glBindTexture(GL_TEXTURE_2D, m_texture);
	}

	void Texture::unbind() const
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

} }