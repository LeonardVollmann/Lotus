#ifndef LOTUS_TEXTURE_HPP_INCLUDED
#define LOTUS_TEXTURE_HPP_INCLUDED

#include <GL/glew.h>
#include <string>

class Texture
{	
private:
	GLuint m_texture;
public:
	Texture(const std::string &fileName);
	virtual ~Texture();

	void bind(unsigned int unit) const;

	inline GLuint getTextureLocation() const { return m_texture; }
};

#endif