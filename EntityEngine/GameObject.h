#pragma once
#include <map>
#include <vector>
#include "Vector4.h"
#include "MathsHelper.h"
#include "ObserverSubject.h"
#include <GL/GLM/detail/type_mat4x4.hpp>

// Forward references
class GameObjectComponent;
class Message;


// Typedefs
typedef std::map<std::string, GameObjectComponent*> ComponentMap;
typedef std::map<std::string, GameObjectComponent*>::iterator ComponentMapIterator;
typedef std::vector<GameObjectComponent*>::iterator ComponentListIterator;


// Now new and improved to use a component-based architecture
class GameObject : public ObserverSubject {
protected:
	GameObject* _parent{ nullptr };

	std::string _type; // Type of the object
	Vector4 _position; // Position of object's origin
	float _angleX; // Angle of object in degrees
	float _angleY;
	float _angleZ;
	float _scale; // Scale of the object (1 = normal)

	Vector4 _localPosition;
	float _localAngleX;
	float _localAngleY;
	float _localAngleZ;
	float _localScale;

	glm::mat4 _Xform;
	glm::mat4 _extraXform;

	bool _alive; // Alive flag; when false, is not updated
	bool _deleteFlag; // Set when you want this game object to be deleted by the game

	// Components
	ComponentMap _components;


	// Constructors
public:
	GameObject() = default;
	GameObject(std::string type);
	virtual ~GameObject();

	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

	void SetParent(GameObject* parent) { _parent = parent; }

	Vector4 GetPosition() const { return _position; }
	void SetPosition(const Vector4& v) { _position = v; }

	float GetAngleX() const { return _angleX; }
	void SetAngleX(float v) { _angleX = v; }

	float GetAngleY() const { return _angleY; }
	void SetAngleY(float v) { _angleY = v; }

	float GetAngleZ() const { return _angleZ; }
	void SetAngleZ(float v) { _angleZ = v; }

	float GetScale() const { return _scale; }
	void SetScale(float v) { _scale = v; }

	Vector4 GetLocalPosition() const { return _localPosition; }
	void SetLocalPosition(const Vector4& v) { _localPosition = v; }

	float GetLocalAngleX() const { return _localAngleX; }
	void SetLocalAngleX(float v) { _localAngleX = v; }

	float GetLocalAngleY() const { return _localAngleY; }
	void SetLocalAngleY(float v) { _localAngleY = v; }

	float GetLocalAngleZ() const { return _localAngleZ; }
	void SetLocalAngleZ(float v) { _localAngleZ = v; }

	float GetLocalScale() const { return _localScale; }
	void SetLocalScale(float v) { _localScale = v; }

	glm::mat4 GetXform() const { return _Xform; }
	void SetXform(const glm::mat4& xform) { _Xform = xform; }
	void CalcXform();

	glm::mat4 GetExtraXform() const { return _extraXform; }
	void SetExtraXForm(const glm::mat4& xform) { _extraXform = xform; }

	bool IsAlive() const { return _alive; }
	void SetAlive(bool v) { _alive = v; }

	bool ShouldBeDeleted() const { return _deleteFlag; }
	void SetDeleteFlag(bool v) { _deleteFlag = v; }

	std::string GetType() const { return _type; }

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
