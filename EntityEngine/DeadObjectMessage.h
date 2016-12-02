#pragma once
#include "Message.h"

class GameObject;

class DeadObjectMessage : public Message
{
protected:
	GameObject* _deadObject;

public:
	DeadObjectMessage(GameObject* deadObject)
		: Message("dead"), _deadObject(deadObject)
	{
	}

	virtual ~DeadObjectMessage() = default;

	GameObject* GetDeadObject() const noexcept { return _deadObject; }
};
