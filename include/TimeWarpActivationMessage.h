#ifndef TIME_WARP_ACTIVATION_MESSAGE_H_
#define TIME_WARP_ACTIVATION_MESSAGE_H_
#include "Message.h"

class TimeWarpActivationMessage : public Message {
private:
	float _warpValue{ 1.0f };
	double _activationTime{ 0.0 };

public:
	TimeWarpActivationMessage(float warpValue, double activationTime)
		: Message("TimeWarpActivation"), _warpValue(warpValue), _activationTime(activationTime)
	{
	}

	double GetWarpValue() const noexcept { return _warpValue; }

	double GetActivationTime() const noexcept { return _activationTime; }
};

#endif //TIME_WARP_MESSAGE_H_
