#pragma once

#include "../core/entitycomponent.hpp"
#include "../graphics/renderable.hpp"
#include "../graphics/material.hpp"
#include "../graphics/renderers/irenderer.hpp"
#include "../maths/types.hpp"

namespace lotus
{
namespace graphics
{

class WaterComponent : public EntityComponent
{
private:
	Renderable *m_renderable;
	Material *m_material;
public:
	WaterComponent(const maths::vec3f &pos, const maths::vec2f &size);
	virtual ~WaterComponent();

	virtual void update(float delta) override;
	virtual void render(IRenderer *renderer) const override;

	void bind() const;

	inline Renderable *getRenderable() const { return m_renderable; }
	inline Material *getMaterial() const { return m_material; }
};

} // namespace graphics
} // namespace lotus