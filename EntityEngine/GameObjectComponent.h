#pragma once
#include <string>
#include "Observer.h"

// Forward references
class GameObject;
class Message;


class GameObjectComponent
		: public Observer // Implement observer pattern
{
	// Data
protected:
	GameObject* _parent;
	std::string _componentType;

	// Structors
public:
	GameObjectComponent(std::string type, GameObject* parent);
	virtual ~GameObjectComponent();

	GameObjectComponent(const GameObjectComponent&) = delete;
	GameObjectComponent& operator=(const GameObjectComponent&) = delete;

	GameObject* GetGameObject() const { return _parent; }
	std::string GetComponentType() const { return _componentType; }

	// Setup function -- called when parent object is initialised (using its own Start method)
	virtual void Start() noexcept = 0;

	// Main update function (called every frame)
	virtual void Update(double deltaTime) noexcept = 0;

	// Shutdown function -- called when parent object is destroyed
	virtual void End() noexcept = 0;

	// Broadcast a message to all objects
	static void BroadcastMessage(Message* msg) noexcept;
};
