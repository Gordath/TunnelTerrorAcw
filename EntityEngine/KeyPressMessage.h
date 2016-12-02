#pragma once
#include "Message.h"

class KeyPressMessage : public Message
{
protected:
	int _key;
	bool _down;

public:
	KeyPressMessage(int key, bool down)
		: Message("keypress"), _key(key), _down(down)
	{
	}

	virtual ~KeyPressMessage() = default;

	int GetKey() const noexcept { return _key; }

	bool GetDown() const noexcept { return _down; }
};
