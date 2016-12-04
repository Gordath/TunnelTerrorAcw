#pragma once
#include "Message.h"

class GameObject;

class CollisionMessage : public Message {
	// Data
protected:
	GameObject* _collider;
	GameObject* _collidee;

	// Structors
public:
	CollisionMessage(GameObject* collider, GameObject* collidee)
		: Message("collision"), _collider(collider), _collidee(collidee)
	{}
	
	virtual ~CollisionMessage() = default;

	GameObject* GetCollider() const noexcept { return _collider; }

	GameObject* GetCollidee() const noexcept { return _collidee; }

	GameObject* GetOtherCollisionObject(GameObject* obj) const noexcept 
	{ 
		return _collider == obj ? _collidee : _collider; 
	}
};
