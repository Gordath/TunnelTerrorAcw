#pragma once
#include "Message.h"
#include <GL/GLM/detail/type_vec3.hpp>

class ThrustMessage : public Message {
protected:
	glm::vec3 _thrust;

public:
	ThrustMessage(const glm::vec3& thrustAmt)
		: Message("thrust"), _thrust(thrustAmt)
	{
	}
	
	virtual ~ThrustMessage() = default;

	const glm::vec3& GetThrust() const noexcept { return _thrust; }
};
