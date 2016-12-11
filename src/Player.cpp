#include "player.h"
#include <iostream>
#include "RenderComponent.h"
#include "PlayerKeyboardControllerComponent.h"
#include "PlayerMouseControllerComponent.h"
#include "CollisionComponent.h"
#include "CollisionMatrix.h"
#include "DeadObjectMessage.h"
#include "Game.h"
#include "TimeWarpActivationMessage.h"
#include "TunnelTerrorGame.h"
#include "TimeWarpExpirationMessage.h"

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
	}
		break;
	case PlayerControls::MOUSE: {
		PlayerMouseControllerComponent* mc{ new PlayerMouseControllerComponent{ this, "MousePlayerController" } };
		mc->SetRotationSpeed(glm::pi<float>());
		mc->SetPlayerLocalPosition(localPosition);
	}
		break;
	default: 
		break;
	}

	_applyDefaultXform = false;

	GameObject::SetPosition(glm::vec3{ 0.85f, -0.75f, 0.0f });
	SetScale(glm::vec3{ 0.8f, 0.8f, 0.8f });
}

void Player::Update(double deltaTime)
{
	if (!_timeWarpCharge && Game::TheGame->GetCurrentTime() - _timeWarpActivationTime > 60000.0) {
		_timeWarpCharge = true;
		TunnelTerrorGame::_audioManager.play_sample(TunnelTerrorGame::_timeWarpReady, 1.0, AUDIO_PLAYMODE_ONCE);
		std::cout << "Time warp recharged!" << std::endl;
	}


	if (_timeWarpWarning && Game::TheGame->GetCurrentTime() - _timeWarpActivationTime > 8000.0) {
		TunnelTerrorGame::_audioManager.play_sample(TunnelTerrorGame::_timeWarpWarning, 1.0, AUDIO_PLAYMODE_ONCE);
		_timeWarpWarning = false;
	}

	if (!_timeWarpExpired && Game::TheGame->GetCurrentTime() - _timeWarpActivationTime > 14000.0) {
		TimeWarpExpirationMessage* twem{ new TimeWarpExpirationMessage(_warpValue) };
		_timeWarpExpired = true;
		Game::TheGame->ListenToMessage(twem);
	}

	GameObject::Update(deltaTime);
}


void Player::OnMessage(Message* msg)
{
	if (msg->GetMessageType() == "collision") {
		DeadObjectMessage* dom{ new DeadObjectMessage{this} };
		OnMessage(dom);
		Game::TheGame->ListenToMessage(dom);
	}

	if (msg->GetMessageType() == "TimeWarpActivation" && _timeWarpCharge) {
		TimeWarpActivationMessage* twam{ static_cast<TimeWarpActivationMessage*>(msg) };
		_timeWarpActivationTime = twam->GetActivationTime();
		_warpValue = twam->GetWarpValue();
		_timeWarpCharge = false;
		_timeWarpExpired = false;
		_timeWarpWarning = true;
		TunnelTerrorGame::_audioManager.play_sample(TunnelTerrorGame::_timeWarpActivation, 18.0f, AUDIO_PLAYMODE_ONCE);
		Game::TheGame->ListenToMessage(twam);
	}

	GameObject::OnMessage(msg);
}
