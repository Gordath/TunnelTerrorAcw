#ifndef TIME_WARP_EXPIRATION_MESSAGE_H_
#define TIME_WARP_EXPIRATION_MESSAGE_H_
#include "Message.h"

class TimeWarpExpirationMessage : public Message {
private:
	float _warpValue{ 1.0f };

public:
	TimeWarpExpirationMessage(float warpValue)
		: Message("TimeWarpExpiration"), _warpValue(warpValue)
	{
	}

	float GetWarpValue() const noexcept { return _warpValue; }
};

#endif //TIME_WARP_EXPIRATION_MESSAGE_H_
