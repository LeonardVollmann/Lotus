#ifndef LOTUS_TEXTURE_HPP_INCLUDED
#define LOTUS_TEXTURE_HPP_INCLUDED

#include "../core/resourcemanagement.hpp"

#include <GL/glew.h>
#include <string>

namespace lotus { namespace graphics {

	#define TEXTURE_IMAGE_FILE_DIRECTORY "./res/textures/"

	class TextureResource : public Resource
	{
	public:
		TextureResource(const std::string &name, GLenum textureTarget, unsigned int width, unsigned int height,
						unsigned int numTextures, unsigned char **data, GLfloat *filters,
						GLenum *internalFormats, GLenum *formats, bool *clamp, GLenum *attachments);
		TextureResource(const std::string &name);
		virtual ~TextureResource();

		void bind(GLuint unit) const;
		void bindAsRenderTarget() const;

		inline GLuint *getTextureID() const { return m_textureID; }
	private:
		void initTextures(unsigned char **data, GLfloat *filters, GLenum *internalFormats, GLenum *formats, bool *clamp);
		void initRenderTargets(GLenum *attachments);

		GLuint			*m_textureID;
		GLenum			m_textureTarget;
		unsigned int	m_width;
		unsigned int	m_height;
		unsigned int	m_numTextures;
		GLuint			m_frameBuffer;
	};

	class Texture
	{
	public:
		Texture(const std::string &name, GLenum textureTarget,
				GLuint numTextures, std::string *fileNames, GLfloat *filters,
				GLenum *internalFormats, GLenum *formats, bool *clamp, GLenum *attachments);
		Texture(const std::string &fileName, GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_NEAREST,
				GLenum internalFormat = GL_RGBA, GLenum format = GL_RGBA, bool clamp = false, GLenum attachment = GL_NONE);
		Texture(const std::string &name, unsigned int width, unsigned int height, GLenum textureTarget,
				unsigned int numTextures, unsigned char **data, GLfloat *filters, GLenum *internalFormats, GLenum *formats,
				bool *clamp, GLenum *attachments);
		Texture(const std::string &name, unsigned int width, unsigned int height, unsigned char *data = nullptr,
				GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_NEAREST,
				GLenum internalFormat = GL_RGBA, GLenum format = GL_RGBA,
				bool clamp = false, GLenum attachment = GL_NONE);
		virtual ~Texture();

		void bind(GLuint unit) const;
		void bindAsRenderTarget() const;

		inline GLuint *getTextureID() const { return m_textureResource->getTextureID(); }
	private:
		TextureResource *m_textureResource;
	};

} }

#endif
