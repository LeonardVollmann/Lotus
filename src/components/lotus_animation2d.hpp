#ifndef	LOTUS_ANIMATION_2D_HPP_INCLUDED
#define LOTUS_ANIMATION_2D_HPP_INCLUDED

#include "lotus_renderablecomponent.hpp"
#include "../graphics/lotus_renderables.hpp"
#include "../graphics/lotus_texture.hpp"
#include "../graphics/lotus_material.hpp"

#include <vector>

class Animation2D : public RenderableComponent
{
protected:
	float			m_interval;
	float			m_passedTime;
	unsigned int	m_current;
	unsigned int	m_numFrames;
	bool			m_looped;
	bool			m_done;
public:
	Animation2D(Sprite *sprite, Material *material, const std::vector<Texture*> &frames, float interval, bool looped);
	virtual ~Animation2D();
	
	virtual void bind() const override;
	virtual void update(float delta) override;
	
	inline float getInterval()				const { return m_interval; }
	inline bool isLooped()					const { return m_looped; }
	inline bool isDone()					const { return m_done; }
};

#endif