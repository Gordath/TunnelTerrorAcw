#include "GameObject.h"
#include "GameObjectComponent.h"
#include "Message.h"
#include <GL/GLM/GTC/matrix_transform.inl>

/******************************************************************************************************************/
// Structors
/******************************************************************************************************************/

GameObject::GameObject(std::string type)
	: _angleX(0),
	  _angleY(0),
	  _angleZ(0),
	  _scale(1),
	  _position(0, 0),
	  _alive(true),
	  _deleteFlag(false),
	  _type(type)
{
}

/******************************************************************************************************************/

GameObject::~GameObject()
{
	End();
}

void GameObject::CalcXform()
{
	_Xform = glm::mat4(1.0f);
	_Xform = glm::translate(_Xform, glm::vec3(_position.x(), _position.y(), _position.z()));
	_Xform = glm::rotate(_Xform, _angleX, glm::vec3{ 1.0f, 0.0f, 0.0f });
	_Xform = glm::rotate(_Xform, _angleY, glm::vec3{ 0.0f, 1.0f, 0.0f });
	_Xform = glm::rotate(_Xform, _angleZ, glm::vec3{ 0.0f, 0.0f, 1.0f });
	_Xform = glm::scale(_Xform, glm::vec3{ _scale, _scale, _scale });

	if (_parent) {
		_Xform = _parent->GetXform() * _Xform * _extraXform;
	}
}

/******************************************************************************************************************/
// Component Functions
/******************************************************************************************************************/

bool GameObject::AddComponent(GameObjectComponent* goc)
{
	if (_components.find(goc->GetComponentType()) != _components.end()) {
		// Error - already have this component!
		return false;
	}
	_components[goc->GetComponentType()] = goc;

	return true;
}

/******************************************************************************************************************/

bool GameObject::RemoveComponent(GameObjectComponent* goc)
{
	return RemoveComponent(goc->GetComponentType());
}

/******************************************************************************************************************/

bool GameObject::RemoveComponent(std::string type)
{
	ComponentMapIterator i = _components.find(type);
	if (i != _components.end()) {
		// Remove it
		_components.erase(i);

		// Delete it
		i->second->End();
		delete i->second;

		return true;
	}

	// Couldn't find it
	return false;
}

/******************************************************************************************************************/

GameObjectComponent* GameObject::GetComponent(std::string type)
{
	ComponentMapIterator i = _components.find(type);
	if (i != _components.end()) {
		// Return it
		return i->second;
	}

	// Couldn't find it
	return nullptr;
}

/******************************************************************************************************************/
// General Functions
/******************************************************************************************************************/

// Setup function -- called to initialise object and its components
void GameObject::Start()
{
	// Initialise all objects
	for (ComponentMapIterator i = _components.begin();
	     i != _components.end();
	     ++i) {
		i->second->Start();
	}
}

/******************************************************************************************************************/

// Main update function (called every frame)
void GameObject::Update(double deltaTime)
{
	// Update all objects
	for (ComponentMapIterator i = _components.begin();
	     i != _components.end();
	     ++i) {
		i->second->Update(deltaTime);
	}
}

/******************************************************************************************************************/

// Shutdown function -- called when object is destroyed (i.e., from destructor)
void GameObject::End()
{
	// End all objects
	for (ComponentMapIterator i = _components.begin();
	     i != _components.end();
	     ++i) {
		GameObjectComponent* component = i->second;
		component->End();
		delete component;
	}

	// Clear list
	_components.clear();
}

/******************************************************************************************************************/

// Resets the game object to the start state (similar to Start(), but may be called more than once)
void GameObject::Reset()
{
}

/******************************************************************************************************************/
