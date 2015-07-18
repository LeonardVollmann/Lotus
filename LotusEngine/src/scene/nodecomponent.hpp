#ifndef LOTUS_NODE_COMPONENT_HPP_INCLUDED
#define LOTUS_NODE_COMPONENT_HPP_INCLUDED

#include "../core/transform.hpp"

namespace lotus {

	class Node;

	class NodeComponent
	{
	private:
		Node *m_parent;
	public:
		virtual void update(float delta) {}
		virtual void render() const {}

		const Transform &getTransform() const;
		Transform &getTransform();

		inline const Node *getParent() const { return m_parent; }

		inline void setParent(Node *parent) { m_parent = parent; }
	};

}

#endif