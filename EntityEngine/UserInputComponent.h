#pragma once
#include "GameObjectComponent.h"

class UserInputComponent
		: public GameObjectComponent {
public:
	UserInputComponent(GameObject* gob);
	virtual ~UserInputComponent();

	// Setup function -- called when parent object is initialised (using its own Start method)
	void Start() override;

	// Main update function (called every frame)
	void Update(double deltaTime) override;

	// Message handler (called when message occurs)
	void OnMessage(Message* msg) override;

	// Shutdown function -- called when parent object is destroyed
	void End() override;

};
