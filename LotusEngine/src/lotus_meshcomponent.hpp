#ifndef LOTUS_MESH_COMPONENT_HPP_INCLUDED
#define LOTUS_MESH_COMPONENT_HPP_INCLUDED

#include "lotus_irenderablecomponent.hpp"
#include "lotus_mesh.hpp"
#include "lotus_material.hpp"

class MeshComponent : public IRenderableComponent
{
protected:
	Mesh		*m_mesh;
	Material	*m_material;
public:
	MeshComponent(Mesh *mesh, Material *material);
	virtual ~MeshComponent();
	
	virtual void bind() const override;
	virtual void render(IRenderer *renderer) const override;
	
	inline const Mesh *getMesh()			const { return m_mesh; }
	inline const Material *getMaterial()	const { return m_material; }
};

#endif