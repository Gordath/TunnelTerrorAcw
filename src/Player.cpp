#include "player.h"
#include <iostream>
#include "RenderComponent.h"
#include "PlayerKeyboardControllerComponent.h"
#include "PlayerMouseControllerComponent.h"
#include "CollisionComponent.h"
#include "CollisionMatrix.h"
#include "DeadObjectMessage.h"
#include "Game.h"


Player::Player(Mesh* mesh, const Material& material, PlayerControls controls, const glm::vec3& localPosition) : GameObject("Player")
{
	RenderComponent* rc{ new RenderComponent{ this } };
	rc->SetMesh(mesh);
	rc->ShouldDraw(true);
	rc->SetMaterial(material);

	CollisionComponent* cc{ new CollisionComponent{ this } };
	cc->SetCollisionRadius(mesh->CalculateMaxSize());
	cc->SetCollisionID(PLAYER_ID);
	cc->SetCollisionMatrixFlag(OBSTACLE_ID);

	switch(controls) {
	case PlayerControls::KEYBOARD: {
		PlayerKeyboardControllerComponent* kc{ new PlayerKeyboardControllerComponent{ this, "KeyboardPlayerController" } };
		kc->SetRotationSpeed(glm::pi<float>());
		kc->SetPlayerLocalPosition(localPosition);
		kc->SetPlayerLocalScale(glm::vec3{ 0.2f, 0.2f, 0.2f });
	}
		break;
	case PlayerControls::MOUSE: {
		PlayerMouseControllerComponent* mc{ new PlayerMouseControllerComponent{ this, "MousePlayerController" } };
		mc->SetRotationSpeed(glm::pi<float>());
		mc->SetPlayerLocalPosition(localPosition);
		mc->SetPlayerLocalScale(glm::vec3{ 0.2f, 0.2f, 0.2f });
	}
		break;
	default: 
		break;
	}

	_applyDefaultXform = false;

	GameObject::SetPosition(glm::vec3{ 0.85f, -0.75f, 0.0f });
	SetScale(glm::vec3{ 0.2f, 0.2f, 0.2f });
}

void Player::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}


void Player::OnMessage(Message* msg)
{
	if (msg->GetMessageType() == "collision") {
		DeadObjectMessage* dom{ new DeadObjectMessage{this} };
		OnMessage(dom);
		Game::TheGame->ListenToMessage(dom);
	}

	GameObject::OnMessage(msg);
}
