#pragma once
#include "Message.h"

class GameObject;

class DeadObjectMessage : public Message {
protected:
	GameObject* _deadObject;

public:
	DeadObjectMessage(GameObject* deadObject);
	virtual ~DeadObjectMessage();

	GameObject* GetDeadObject() const { return _deadObject; }
};
