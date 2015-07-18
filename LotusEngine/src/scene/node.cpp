#include "node.hpp"

namespace lotus {

		Node::Node() :
			m_parent(nullptr),
			m_name("") {}

		void Node::update(float delta)
		{
			updateCurrent(delta);

			for (auto it = m_children.begin(); it < m_children.end(); it++)
			{
				(*it)->update(delta);
			}

			for (auto it = m_components.begin(); it < m_components.end(); it++)
			{
				(*it)->update(delta);
			}
		}

		void Node::render() const
		{
			renderCurrent();

			for (auto it = m_children.begin(); it < m_children.end(); it++)
			{
				(*it)->render();
			}

			for (auto it = m_components.begin(); it < m_components.end(); it++)
			{
				(*it)->render();
			}
		}

		Node &Node::addChild(std::unique_ptr<Node> node)
		{
			node->m_parent = this;
			m_children.push_back(std::move(node));

			return *this;
		}

		Node &Node::addComponent(std::unique_ptr<NodeComponent> component)
		{
			component->setParent(this);
			m_components.push_back(std::move(component));

			return *this;
		}

		std::unique_ptr<Node> Node::removeChild(const Node &node)
		{
			auto found = std::find_if(m_children.begin(),
									  m_children.end(),
			[&node] (std::unique_ptr<Node>& child)
			{
				return child.get() == &node;
			});

			if (found != m_children.end())
			{
				std::unique_ptr<Node> result = std::move(*found);
				result->m_parent = nullptr;
				m_children.erase(found);

				return result;
			}

			return nullptr;
		}

		std::unique_ptr<NodeComponent> Node::removeComponent(const NodeComponent &component)
		{
			auto found = std::find_if(m_components.begin(),
									  m_components.end(),
			[&component] (std::unique_ptr<NodeComponent>& c)
			{
				return c.get() == &component;
			});

			if (found != m_components.end())
			{
				std::unique_ptr<NodeComponent> result = std::move(*found);
				result->setParent(nullptr);
				m_components.erase(found);

				return result;
			}

			return nullptr;
		}

		maths::mat4 Node::getGlobalTransformation() const
		{	
			if (m_parent == nullptr)
			{
				return m_transform.getTransformation();
			}

			maths::mat4 result;
			result *= m_parent->getGlobalTransformation();
			
			return result;
		}

		Node *Node::getChild(const std::string &name)
		{
			for (const std::unique_ptr<Node>& child : m_children)
			{
				if (child->m_name == name)
				{
					return child.get();
				}
			}

			return nullptr;
		}

}