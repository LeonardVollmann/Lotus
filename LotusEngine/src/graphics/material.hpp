#ifndef LOTUS_MATERIAL_HPP_INCLUDED
#define LOTUS_MATERIAL_HPP_INCLUDED

#include "texture.hpp"
#include "../core/maths.hpp"

#include <map>
#include <string>

namespace lotus { namespace graphics {

	class Material
	{
	public:
		static const Material *CURRENT;
	private:
		mutable std::map<std::string, void*> m_values;
	public:
		Material() {}
		Material(Texture *diffuse, maths::Vector4f color = maths::Vector4f(), float specularIntensity = 2.0f, float specularPower = 8.0f,
				 Texture *normalMap = new Texture("default_normal.png"), Texture *dispMap = new Texture("default_disp.png"),
				 float dispMapScale = 0.0f, float dispMapOffset = 0.0f);
		virtual ~Material();
		
		void bind() const;
		void bindTexture(const std::string &name, unsigned int unit) const;
		
		void set(const std::string &name, void *value) const;
		
		inline const void *get(const std::string &name)				const { return (const void*) m_values[name]; }
		inline const float *getFloat(const std::string &name)		const { return (const float*) get(name); }
		inline const maths::Vector2f *getVector2f(const std::string &name)	const { return (const maths::Vector2f*) get(name); }
		inline const maths::Vector3f *getVector3f(const std::string &name)	const { return (const maths::Vector3f*) get(name); }
		inline const maths::Vector4f *getVector4f(const std::string &name)	const { return (maths::Vector4f*) get(name); }
		inline const Texture *getTexture(const std::string &name)	const { return (const Texture*) get(name); }
	};

} }

#endif