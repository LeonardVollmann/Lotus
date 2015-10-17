#ifndef LOTUS_TEXTURE_HPP_INCLUDED
#define LOTUS_TEXTURE_HPP_INCLUDED

#include "../core/resourcemanagement.hpp"

#include <GL/glew.h>
#include <string>

namespace lotus { namespace graphics {

	class TextureResource : public Resource
	{
	public:
		TextureResource(const std::string &fileName);
		virtual ~TextureResource();

		inline GLuint getTextureID() const { return m_textureID; }
	private:
		GLuint m_textureID;
	};

	class Texture
	{
	public:
		Texture(const std::string &fileName);
		virtual ~Texture();

		void bind(unsigned int unit) const;

		inline GLuint getTextureID() const { return m_textureResource->getTextureID(); }
	private:
		TextureResource *m_textureResource;
	};

} }

#endif
