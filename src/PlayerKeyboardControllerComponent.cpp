#include "PlayerKeyboardControllerComponent.h"
#include "GameObject.h"
#include "KeyPressMessage.h"
#include <GL/GLM/GTC/matrix_transform.inl>
#include <iostream>

void PlayerKeyboardControllerComponent::CalculateXformMatrix(glm::mat4& matrix) const noexcept
{
	matrix = glm::rotate(matrix, static_cast<float>(_rotationAngle), glm::vec3{ 1.0f, 0.0f, 0.0f });
	matrix = glm::translate(matrix, _playerLocalPos);
	matrix = glm::scale(matrix, _playerLocalScale);
}

PlayerKeyboardControllerComponent::PlayerKeyboardControllerComponent(GameObject* gameObject)
	: UserInputComponent(gameObject)
{
}

void PlayerKeyboardControllerComponent::Start()
{
	_parent->RegisterListener("keypress", this);
}

void PlayerKeyboardControllerComponent::Update(double deltaTime)
{
	glm::mat4 xform;

	if (_rotateLeft) {
		_rotationAngle -= _rotationSpeed * deltaTime;
	}

	if (_rotateRight) {
		_rotationAngle += _rotationSpeed * deltaTime;
	}

	CalculateXformMatrix(xform);

	_parent->SetExtraXForm(xform);
}

void PlayerKeyboardControllerComponent::OnMessage(Message* msg)
{
	if (msg->GetMessageType() == "keypress") {
		KeyPressMessage* kpm{ dynamic_cast<KeyPressMessage*>(msg) };

		if(kpm) {
			switch (kpm->GetKey()) {
			case 97: //a
			case 65: //A
			case 37: //left arrow
				_rotateLeft = kpm->GetDown();
				break;
			case 100: //d
			case 68: //D
			case 39: //right arrow
				_rotateRight = kpm->GetDown();
				break;
			default:
				break;
			}
		}
	}
}

void PlayerKeyboardControllerComponent::End()
{
}
