#include "PlayerKeyboardControllerComponent.h"
#include "GameObject.h"
#include "KeyPressMessage.h"
#include <GL/GLM/GTC/matrix_transform.inl>


void PlayerKeyboardControllerComponent::CalculateXformMatrix(glm::mat4& matrix) const noexcept
{

	matrix = glm::rotate(matrix, static_cast<float>(_rotationAngle), glm::vec3{ 1.0f, 0.0f, 0.0f });
	matrix = glm::translate(matrix, _playerLocalPos);
	matrix = glm::rotate(matrix, glm::radians(-90.0f), glm::vec3{ 0.0f, 1.0f, 0.0f });
	matrix = glm::rotate(matrix, glm::radians(-90.0f), glm::vec3{ 1.0f, 0.0f, 0.0f });
}

PlayerKeyboardControllerComponent::PlayerKeyboardControllerComponent(GameObject* gameObject, const std::string& type)
	: UserInputComponent(gameObject, type)
{
}

void PlayerKeyboardControllerComponent::Start() noexcept
{
	_parent->RegisterListener("keypress", this);
}

void PlayerKeyboardControllerComponent::Update(double deltaTime) noexcept
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

void PlayerKeyboardControllerComponent::OnMessage(Message* msg) noexcept
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

void PlayerKeyboardControllerComponent::End() noexcept
{
}
