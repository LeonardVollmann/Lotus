#ifndef LOTUS_TEXTURE_HPP_INCLUDED
#define LOTUS_TEXTURE_HPP_INCLUDED

#include "../core/resourcemanagement.hpp"

#include <GL/glew.h>
#include <string>

namespace lotus { namespace graphics {

	class TextureResource : public Resource
	{
	private:
		GLuint m_textureID;
	public:
		TextureResource(const std::string &fileName);
		virtual ~TextureResource();

		inline GLuint getTextureID() const { return m_textureID; }
	};

	class Texture
	{
	private:
		TextureResource *m_textureResource;
	public:
		Texture(const std::string &fileName);
		virtual ~Texture();

		void bind(unsigned int unit) const;

		inline GLuint getTextureID() const { return m_textureResource->getTextureID(); }
	};

} }

#endif
