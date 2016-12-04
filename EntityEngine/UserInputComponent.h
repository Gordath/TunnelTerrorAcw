#pragma once
#include "GameObjectComponent.h"

class UserInputComponent
		: public GameObjectComponent {
public:
	UserInputComponent(GameObject* gob);
	virtual ~UserInputComponent();

	// Setup function -- called when parent object is initialised (using its own Start method)
	void Start() noexcept override;

	// Main update function (called every frame)
	void Update(double deltaTime) noexcept override;

	// Message handler (called when message occurs)
	void OnMessage(Message* msg) noexcept override;

	// Shutdown function -- called when parent object is destroyed
	void End() noexcept override;

};
