#include "player.h"
#include <iostream>
#include "RenderComponent.h"
#include "PlayerKeyboardControllerComponent.h"
#include <GL/GLM/gtc/constants.inl>
#include "PlayerMouseControllerComponent.h"
#include "CollisionComponent.h"
#include "CollisionMatrix.h"


Player::Player(Mesh* mesh) : GameObject("Player")
{
	RenderComponent* rc{ new RenderComponent{ this } };
	rc->SetMesh(mesh);
	rc->ShouldDraw(true);
	rc->SetMaterial(Material{ glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f }, glm::vec4{ 1.0f, 1.0f, 1.0f, 80.0f } });

	CollisionComponent* cc{ new CollisionComponent{ this } };
	cc->SetCollisionRadius(mesh->CalculateMaxSize());
	cc->SetCollisionID(PLAYER_ID);
	cc->SetCollisionMatrixFlag(OBSTACLE_ID);

	PlayerKeyboardControllerComponent* kc{ new PlayerKeyboardControllerComponent{ this } };
	kc->SetRotationSpeed(glm::pi<float>());
	kc->SetPlayerLocalPosition(glm::vec3{ 0.85f, -0.75f, 0.0f });
	kc->SetPlayerLocalScale(glm::vec3{ 0.2f, 0.2f, 0.2f });

	_applyDefaultXform = false;

	SetPosition(glm::vec3{ 0.85f, -0.75f, 0.0f });
	SetScale(glm::vec3{ 0.2f, 0.2f, 0.2f });
}

void Player::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}


void Player::OnMessage(Message* msg)
{
	if (msg->GetMessageType() == "collision") {
		std::cout << "DIED!" << std::endl;
	}

	GameObject::OnMessage(msg);
}
