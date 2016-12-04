#pragma once
#include "GameObjectComponent.h"
#include "GameObject.h"
#include <algorithm>

class CollisionComponent
		: public GameObjectComponent {
	// Data
protected:
	float _radius; // Collision radius of object
	int _collisionMatrix; // Who to collide with (bitfields)
	int _collisionID; // This object's collision type

	// Structors
public:
	CollisionComponent(GameObject* gob);
	virtual ~CollisionComponent();

	float GetCollisionRadius() const
	{
		float m = std::max(std::max(_parent->GetScale().x, _parent->GetScale().y), _parent->GetScale().z);
		return _radius * m;
	}

	void SetCollisionRadius(float r) { _radius = r; }

	// Collision matrix
	void SetCollisionMatrixFlag(int flag) { _collisionMatrix |= flag; }
	void UnsetCollisionMatrixFlag(int flag) { _collisionMatrix &= ~flag; }
	bool CheckCollisionMatrixFlag(int flag) const { return (_collisionMatrix & flag) != 0; }
	int GetCollisionMatrix() const { return _collisionMatrix; }

	// Collision ID
	int GetCollisionID() const { return _collisionID; }
	void SetCollisionID(int id) { _collisionID = id; }

	// Functions
public:

	// Setup function -- called when parent object is initialised (using its own Start method)
	void Start() noexcept override;

	// Main update function (called every frame)
	void Update(double deltaTime) noexcept override;

	// Message handler (called when message occurs)
	void OnMessage(Message* msg) noexcept override;

	// Shutdown function -- called when parent object is destroyed
	void End() noexcept override;


};
