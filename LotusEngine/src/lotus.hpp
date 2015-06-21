#ifndef LOTUS_HPP_INCLUDED
#define LOTUS_HPP_INCLUDED

#include "lotus_igame.hpp"
#include "lotus_engine.hpp"
#include "lotus_input.hpp"
#include "lotus_time.hpp"
#include "lotus_window.hpp"
#include "lotus_maths.hpp"

#include "lotus_shader.hpp"
#include "lotus_simpleshader.hpp"
#include "lotus_phongshader.hpp"
#include "lotus_forwardambient.hpp"
#include "lotus_forwarddirectional.hpp"
#include "lotus_forwardpoint.hpp"
#include "lotus_forwardspot.hpp"

#include "lotus_lighting.hpp"
#include "lotus_camera.hpp"

#include "lotus_simplerenderer3d.hpp"
#include "lotus_phongrenderer3d.hpp"
#include "lotus_forwardrenderer3d.hpp"

#include "lotus_vertex.hpp"
#include "lotus_renderable.hpp"

#include "lotus_texture.hpp"
#include "lotus_material.hpp"

#include "lotus_indexedmodel.hpp"
#include "lotus_objloader.hpp"

#include "lotus_scene.hpp"

#include "lotus_transform.hpp"
#include "lotus_entity.hpp"
#include "lotus_renderablecomponent.hpp"
#include "lotus_freemove.hpp"
#include "lotus_freelook.hpp"

typedef Renderable<Vertex2D> Renderable2D;
typedef Renderable<Vertex3D> Renderable3D;
typedef RenderableComponent<Renderable2D> RenderableComponent2D;
typedef RenderableComponent<Renderable3D> RenderableComponent3D;

#endif