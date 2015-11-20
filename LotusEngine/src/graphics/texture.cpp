#include "texture.hpp"
#include "stb/stb_image.h"

#include <iostream>
#include <cassert>

namespace lotus { namespace graphics {

	TextureResource::TextureResource(const std::string &name, GLenum textureTarget, unsigned int width, unsigned int height,
									unsigned int numTextures, unsigned char **data, GLfloat *filters,
									GLenum *internalFormats, GLenum *formats, bool *clamp, GLenum *attachments) :
		Resource(name),
		m_textureTarget(textureTarget),
		m_width(width),
		m_height(height),
		m_numTextures(numTextures),
		m_frameBuffer(0)
	{
		m_textureID = new GLuint[m_numTextures];
		glGenTextures(m_numTextures, m_textureID);

		initTextures(data, filters, internalFormats, formats, clamp);
		initRenderTargets(attachments);
	}

	TextureResource::TextureResource(const std::string &name) :
		Resource(name) {}

	TextureResource::~TextureResource()
	{
		glDeleteTextures(m_numTextures, m_textureID);
		if (m_frameBuffer) glDeleteFramebuffers(1, &m_frameBuffer);
		delete[] m_textureID;
	}

	void TextureResource::bind(GLuint unit) const
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(m_textureTarget, m_textureID[0]);
	}

	void TextureResource::bindAsRenderTarget() const
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_frameBuffer);
		glViewport(0, 0, m_width, m_height);
	}

	void TextureResource::initTextures(unsigned char **data, GLfloat *filters, GLenum *internalFormats, GLenum *formats, bool *clamp)
	{
		for (unsigned int i = 0; i < m_numTextures; i++)
		{
			glBindTexture(m_textureTarget, m_textureID[i]);

			glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, filters[i]);
			glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, filters[i]);

			if (clamp[i])
			{
				glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			else
			{
				glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
			}

			glTexImage2D(m_textureTarget, 0, internalFormats[i], m_width, m_height, 0, formats[i], GL_UNSIGNED_BYTE, data[i]);
		}
	}

	void TextureResource::initRenderTargets(GLenum *attachments)
	{
		if (!attachments) return;

		GLenum drawBuffers[m_numTextures];

		for (unsigned int i = 0; i < m_numTextures; i++)
		{
			if (attachments[i] == GL_NONE) continue;

			if (attachments[i] == GL_DEPTH_ATTACHMENT || attachments[i] == GL_STENCIL_ATTACHMENT)
			{
				drawBuffers[i] = GL_NONE;
			}
			else
			{
				drawBuffers[i] = attachments[i];
			}

			if (!m_frameBuffer)
			{
				glGenFramebuffers(1, &m_frameBuffer);
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_frameBuffer);
			}
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachments[i], m_textureTarget, m_textureID[i], 0);
		}

		if (!m_frameBuffer) return;

		glDrawBuffers(m_numTextures, drawBuffers);
		if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cerr << "ERROR: Framebuffer completion failed!" << std::endl;
		}
	}

	Texture::Texture(const std::string &name, GLenum textureTarget, GLuint numTextures,
					std::string *fileNames, GLfloat *filters, GLenum *internalFormats, GLenum *formats, bool *clamp, GLenum *attachments)
	{
		if (ResourceManager::exists(name))
		{
			m_textureResource = ResourceManager::get<TextureResource>(name);
			return;
		}

		unsigned char **data = new unsigned char*[numTextures];
		int width;
		int height;
		int numComponents;

		for (unsigned int i = 0; i < numTextures; i++)
		{
			data[i] = stbi_load((TEXTURE_IMAGE_FILE_DIRECTORY  + fileNames[i]).c_str(), &width, &height, &numComponents, 4);
			if (data[i] == nullptr)
			{
				std::cerr << "ERROR: Failed to load image: " + fileNames[i] << std::endl;
			}
		}

		m_textureResource = ResourceManager::create<TextureResource>(name, true, textureTarget, width, height, numTextures, data, filters, internalFormats, formats, clamp, attachments);

		for (unsigned int i = 0; i < numTextures; i++) stbi_image_free(data[i]);
		delete[] data;
	}

	Texture::Texture(const std::string &fileName, GLenum textureTarget, GLfloat filter, GLenum internalFormat, GLenum format, bool clamp, GLenum attachment) :
		Texture(fileName, textureTarget, 1, (std::string[]) {fileName}, (GLfloat[]) {filter},
				(GLenum[]) {internalFormat}, (GLenum[]) {format}, (bool[]) {clamp}, (GLenum[]) {attachment}) {}

	Texture::Texture(const std::string &name, GLenum textureTarget, unsigned int width, unsigned int height,
					unsigned int numTextures, unsigned char **data, GLfloat *filters, GLenum *internalFormats, GLenum *formats, bool *clamp, GLenum *attachments)
	{
		m_textureResource = ResourceManager::create<TextureResource>(name, true, textureTarget, width, height, numTextures, data, filters, internalFormats, formats, clamp, attachments);
	}

	Texture::Texture(const std::string &name, unsigned int width, unsigned int height, unsigned char *data, GLenum textureTarget, GLfloat filter,
					GLenum internalFormat, GLenum format, bool clamp, GLenum attachment) :
		Texture(name, textureTarget, width, height, 1, &data, (GLfloat[]) {filter}, (GLenum[]) {internalFormat}, (GLenum[]) {format}, (bool[]) {clamp}, (GLenum[]) {attachment}) {}

	Texture::~Texture()
	{
		m_textureResource->removeReference();
	}

	void Texture::bind(GLuint unit) const
	{
		assert(unit >= 0 && unit <= 31);
		m_textureResource->bind(unit);
	}

	void Texture::bindAsRenderTarget() const
	{
		m_textureResource->bindAsRenderTarget();
	}

} }
