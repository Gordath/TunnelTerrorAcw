#pragma once
#include <map>
#include <vector>
#include "ObserverSubject.h"
#include <GL/GLM/detail/type_mat4x4.hpp>

// Forward references
class GameObjectComponent;
class Message;

// Typedefs
using ComponentMap = std::map<std::string, GameObjectComponent*>;

// Now new and improved to use a component-based architecture
class GameObject : public ObserverSubject {
protected:
	GameObject* _parent{ nullptr };

	std::string _type; // Type of the object
	glm::vec3 _position; // Position of object's origin
	glm::vec3 _eulerAngles;
	glm::vec3 _scale{ 1.0f, 1.0f, 1.0f };

	glm::mat4 _Xform;
	glm::mat4 _extraXform;

	bool _alive; // Alive flag; when false, is not updated
	bool _deleteFlag; // Set when you want this game object to be deleted by the game

	// Components
	ComponentMap _components;

public:
	GameObject() = default;
	GameObject(std::string type);
	virtual ~GameObject();

	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

	void SetParent(GameObject* parent) { _parent = parent; }

	const glm::vec3& GetPosition() const { return _position; }
	void SetPosition(const glm::vec3& v) { _position = v; }

	const glm::vec3& GetEulerAngles() const { return  _eulerAngles; }
	void SetEulerAngles(const glm::vec3& angles) { _eulerAngles = angles; }

	const glm::vec3& GetScale() const { return _scale; }
	void SetScale(const glm::vec3& v) { _scale = v; }

	glm::mat4 GetXform() const { return _Xform; }
	void SetXform(const glm::mat4& xform) { _Xform = xform; }
	void CalcXform();

	glm::mat4 GetExtraXform() const { return _extraXform; }
	void SetExtraXForm(const glm::mat4& xform) { _extraXform = xform; }

	bool IsAlive() const { return _alive; }
	void SetAlive(bool v) { _alive = v; }

	bool ShouldBeDeleted() const { return _deleteFlag; }
	void SetDeleteFlag(bool v) { _deleteFlag = v; }

	const std::string& GetType() const { return _type; }

	bool AddComponent(GameObjectComponent* goc);

	bool RemoveComponent(GameObjectComponent* goc);
	
	bool RemoveComponent(std::string componentType);
	
	GameObjectComponent* GetComponent(std::string type);

	// Setup function -- called to initialise object and its components. Should only be called once
	virtual void Start();

	// Main update function (called every frame)
	virtual void Update(double deltaTime);

	// Message handler (called when message occurs)
	virtual void OnMessage(Message* msg) { BroadcastMessage(msg); }

	// Shutdown function -- called when object is destroyed (i.e., from destructor)
	virtual void End();

	// Resets the game object to the start state (similar to Start(), but may be called more than once)
	virtual void Reset();
};
