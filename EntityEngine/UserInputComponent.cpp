#include "UserInputComponent.h"
#include "GameObject.h"
#include "Message.h"

/******************************************************************************************************************/
// Structors
/******************************************************************************************************************/

UserInputComponent::UserInputComponent(GameObject* gob)
	: GameObjectComponent("input", gob)
{

}

/******************************************************************************************************************/

UserInputComponent::~UserInputComponent()
{

}

/******************************************************************************************************************/
// Functions
/******************************************************************************************************************/

// Setup function -- called when parent object is initialised (using its own Start method)
void UserInputComponent::Start() noexcept
{
	// Register as a listener
	_parent->RegisterListener("keypress", this);
}

/******************************************************************************************************************/

// Main update function (called every frame)
void UserInputComponent::Update(double deltaTime) noexcept
{

}

/******************************************************************************************************************/

// Message handler (called when message occurs)
void UserInputComponent::OnMessage(Message* msg) noexcept
{
	if (msg->GetMessageType() == "keypress")
	{
		// Respond to this keypress somehow
	}
}

/******************************************************************************************************************/

// Shutdown function -- called when parent object is destroyed
void UserInputComponent::End() noexcept
{
	_parent->UnregisterListener("keypress", this);
}

/******************************************************************************************************************/
