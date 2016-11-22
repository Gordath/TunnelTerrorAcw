#pragma once
#include <string>
#include "Message.h"
#include "Vector4.h"

class ThrustMessage : public Message {
protected:
	Vector4 _thrust;

public:
	ThrustMessage(Vector4 thrustAmt);
	virtual ~ThrustMessage();

	Vector4 GetThrust() const { return _thrust; }
};
