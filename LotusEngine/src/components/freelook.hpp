#ifndef LOTUS_FREE_LOOK_HPP_INCLUDED
#define LOTUS_FREE_LOOK_HPP_INCLUDED

#include "../scene/nodecomponent.hpp"

namespace lotus {

	class FreeLook : public NodeComponent
	{
	private:
		float m_turnSpeed;
	public:
		FreeLook(float turnSpeed);
		virtual void update(float delta) override;
	};

}

#endif