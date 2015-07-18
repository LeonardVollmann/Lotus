#ifndef LOTUS_NODE_HPP_INCLUDED
#define LOTUS_NODE_HPP_INCLUDED

#include "nodecomponent.hpp"
#include "../core/transform.hpp"
#include "../maths/mat4.hpp"

#include <vector>
#include <memory>
#include <string>

namespace lotus {

	class Node
	{
	protected:
		Transform 									m_transform;
		std::vector<std::unique_ptr<Node>>			m_children;
		std::vector<std::unique_ptr<NodeComponent>>	m_components;
		Node 										*m_parent;
		std::string									m_name;
	public:
		Node();
		virtual ~Node() {}

		void update(float delta);
		void render() const;

		Node &addChild(std::unique_ptr<Node> node);
		Node &addComponent(std::unique_ptr<NodeComponent> component);
		std::unique_ptr<Node> removeChild(const Node &node);
		std::unique_ptr<NodeComponent> removeComponent(const NodeComponent &component);

		maths::mat4 getGlobalTransformation() const;
		Node *getChild(const std::string &name);

		inline const Transform &getTransform() 	const { return m_transform; }
		inline Transform &getTransform()			  { return m_transform; }
		inline const std::string &getName()		const { return m_name; }
		inline const Node *getParent()			const { return m_parent; }

		inline void setName(const std::string &name) 	{ m_name = name; }
		inline void setParent(Node *parent)				{ m_parent = parent; } 
	protected:
		virtual void updateCurrent(float delta) {}
		virtual void renderCurrent() const {}
	};

}

#endif