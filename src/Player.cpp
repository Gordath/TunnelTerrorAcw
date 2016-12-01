#include "player.h"
#include <iostream>
#include "RenderComponent.h"


Player::Player(Mesh* mesh) : GameObject("Player")
{
	RenderComponent* rc = new RenderComponent(this);
	rc->SetMesh(mesh);
	rc->ShouldDraw(true);
	rc->SetMaterial(Material{ glm::vec4{0.0f, 0.0f, 1.0f, 1.0f}, glm::vec4{1.0f, 1.0f, 1.0f, 80.0f} });
}

void Player::Update(double deltaTime)
{
	std::cout << "Updating the player!" << std::endl;
}


void Player::OnMessage(Message* msg)
{

}
