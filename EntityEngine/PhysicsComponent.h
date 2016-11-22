#pragma once
#include "GameObjectComponent.h"
#include "Vector4.h"

class PhysicsComponent
		: public GameObjectComponent {
	// Data
protected:
	Vector4 _velocity; // Velocity of object
	float _maxSpeed; // Maximum speed


	// Structors
public:
	PhysicsComponent(GameObject* gob);
	virtual ~PhysicsComponent();

	Vector4 GetVelocity() const { return _velocity; }
	void SetVelocity(Vector4 v) { _velocity = v; }

	float GetMaxSpeed() const { return _maxSpeed; }
	void SetMaxSpeed(float f) { _maxSpeed = f; }

	// Setup function -- called when parent object is initialised (using its own Start method)
	void Start() override;

	// Main update function (called every frame)
	void Update(double deltaTime) override;

	// Message handler (called when message occurs)
	void OnMessage(Message* msg) override;

	// Shutdown function -- called when parent object is destroyed
	void End() override;

	void LimitToMaximumSpeed(float max);

	Vector4 GetObjectPosition() const;
	
	void SetObjectPosition(Vector4 v);
};
