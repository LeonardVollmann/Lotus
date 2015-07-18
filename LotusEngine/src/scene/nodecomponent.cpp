#include "nodecomponent.hpp"
#include "node.hpp"

namespace lotus {

	const Transform &NodeComponent::getTransform() const
	{
		return m_parent->getTransform();
	}

	Transform &NodeComponent::getTransform()
	{
		return m_parent->getTransform();
	}

}