#pragma once
#include "GameObjectComponent.h"
#include <GL/GLM/detail/type_vec3.hpp>

class PhysicsComponent
		: public GameObjectComponent {
	// Data
protected:
	glm::vec3 _velocity; // Velocity of object
	float _maxSpeed; // Maximum speed


	// Structors
public:
	PhysicsComponent(GameObject* gob);
	virtual ~PhysicsComponent();

	const glm::vec3& GetVelocity() const { return _velocity; }
	void SetVelocity(const glm::vec3& v) { _velocity = v; }

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

	const glm::vec3& GetObjectPosition() const;
	
	void SetObjectPosition(const glm::vec3& v) const;
};
