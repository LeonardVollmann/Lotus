#include "lotus_animation2d.hpp"

Animation2D::Animation2D(Sprite *sprite, Material *material, const std::vector<Texture*> &frames, float interval, bool looped) :
	RenderableComponent(sprite, material),
	m_interval(interval),
	m_looped(looped),
	m_done(false),
	m_current(0),
	m_numFrames((unsigned int) frames.size())
{
	for (unsigned int i = 0; i < frames.size(); i++)
	{
		m_material->addTexture(std::to_string(i), frames[i]);
	}
}

Animation2D::~Animation2D()
{
	delete m_renderable;
	delete m_material;
}

void Animation2D::bind() const
{
	m_renderable->bind();
	m_material->bind();
	m_material->bindTexture(std::to_string(m_current), 0);
}

void Animation2D::update(float delta)
{
	if (m_done) return;
	
	m_passedTime += delta;
	if (m_passedTime >= m_interval)
	{
		m_passedTime = 0;
		m_current++;
		if (m_current == m_numFrames)
		{
			if (m_looped) m_current = 0;
			else m_done = true;
		}
		
		m_material->setTexture("diffuse", m_material->getTexture(std::to_string(m_current)));
	}
}