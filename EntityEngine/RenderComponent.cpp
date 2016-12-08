#include "RenderComponent.h"
#include "GameObject.h"
#include "Message.h"

/******************************************************************************************************************/
// Structors
/******************************************************************************************************************/

RenderComponent::RenderComponent(GameObject* gob)
	: GameObjectComponent("render", gob),
	  _material(Material{glm::vec4{1.0f, 1.0f, 1.0f, 1.0f}, glm::vec4{1.0f, 1.0f, 1.0f, 60.0f}, nullptr}),
	  _mesh(nullptr)
{
}

/******************************************************************************************************************/

RenderComponent::~RenderComponent()
{
}

/******************************************************************************************************************/
// Functions
/******************************************************************************************************************/

// Setup function -- called when parent object is initialised (using its own Start method)
void RenderComponent::Start() noexcept
{
}

/******************************************************************************************************************/

// Main update function (called every frame)
void RenderComponent::Update(double deltaTime) noexcept
{
}

/******************************************************************************************************************/

// Message handler (called when message occurs)
void RenderComponent::OnMessage(Message* msg) noexcept
{
}

/******************************************************************************************************************/

// Shutdown function -- called when parent object is destroyed
void RenderComponent::End() noexcept
{
}

/******************************************************************************************************************/
