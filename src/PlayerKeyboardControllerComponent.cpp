#include "PlayerKeyboardControllerComponent.h"
#include "GameObject.h"
#include "KeyPressMessage.h"
#include <GL/GLM/GTC/matrix_transform.inl>

void PlayerKeyboardControllerComponent::CalculateXformMatrix(glm::mat4& matrix) const noexcept
{
	matrix = glm::rotate(matrix, static_cast<float>(glm::radians(_rotationAngle)), glm::vec3{ 1.0f, 0.0f, 0.0f });
	matrix = glm::translate(matrix, _playerLocalPos);
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
				//TODO: turn left.
				break;
			case 100: //d
			case 68: //D
				//TODO: turn right.
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
