#include "PhysicsComponent.h"
#include "GameObject.h"
#include "Message.h"
#include "ThrustMessage.h"

/******************************************************************************************************************/
// Structors
/******************************************************************************************************************/

PhysicsComponent::PhysicsComponent(GameObject* gob)
	: GameObjectComponent("physics", gob),
	  _velocity(glm::vec3{})
{
}

/******************************************************************************************************************/

PhysicsComponent::~PhysicsComponent()
{
}

/******************************************************************************************************************/
// Functions
/******************************************************************************************************************/

// Setup function -- called when parent object is initialised (using its own Start method)
void PhysicsComponent::Start() noexcept
{
	_parent->RegisterListener("thrust", this);
}

/******************************************************************************************************************/

// Main update function (called every frame)
void PhysicsComponent::Update(double deltaTime) noexcept
{
}

/******************************************************************************************************************/

// Message handler (called when message occurs)
void PhysicsComponent::OnMessage(Message* msg) noexcept
{
	if (msg->GetMessageType() == "thrust") {
		ThrustMessage* tm = static_cast<ThrustMessage*>(msg);
		_velocity += tm->GetThrust();
	}
}

/******************************************************************************************************************/

// Shutdown function -- called when parent object is destroyed
void PhysicsComponent::End() noexcept
{
	_parent->UnregisterListener("thrust", this);
}

/******************************************************************************************************************/

void PhysicsComponent::LimitToMaximumSpeed(float max)
{
	_velocity = glm::clamp(_velocity, 0.0f, max);
}

/******************************************************************************************************************/

const glm::vec3& PhysicsComponent::GetObjectPosition() const
{
	return _parent->GetPosition();
}

/******************************************************************************************************************/

void PhysicsComponent::SetObjectPosition(const glm::vec3& v) const
{
	_parent->SetPosition(v);
}

/******************************************************************************************************************/
