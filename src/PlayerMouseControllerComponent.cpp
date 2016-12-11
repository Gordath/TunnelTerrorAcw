#include "PlayerMouseControllerComponent.h"
#include <GL/GLM/GTC/matrix_transform.inl>
#include "GameObject.h"
#include "MouseClickMessage.h"
#include "Game.h"
#include "TimeWarpActivationMessage.h"

void PlayerMouseControllerComponent::CalculateXformMatrix(glm::mat4& matrix) const noexcept
{
	matrix = glm::rotate(matrix, static_cast<float>(_rotationAngle), glm::vec3{ 1.0f, 0.0f, 0.0f });
	matrix = glm::translate(matrix, _playerLocalPos);
	matrix = glm::rotate(matrix, glm::radians(-90.0f), glm::vec3{ 0.0f, 1.0f, 0.0f });
	matrix = glm::rotate(matrix, glm::radians(-90.0f), glm::vec3{ 1.0f, 0.0f, 0.0f });
}

void PlayerMouseControllerComponent::Start() noexcept
{
	_parent->RegisterListener("mouseclick", this);
}

void PlayerMouseControllerComponent::Update(double deltaTime) noexcept
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

void PlayerMouseControllerComponent::OnMessage(Message* msg) noexcept
{
	static glm::vec2 prevCursorPos;
	if (msg->GetMessageType() == "mouseclick") {
		MouseClickMessage* mcm{ dynamic_cast<MouseClickMessage*>(msg) };

		if (mcm) {
			switch (mcm->GetMouseButton()) {
			case MouseButtonType::L_BUTTON:
				_rotateLeft = mcm->GetState();
				break;
			case MouseButtonType::R_BUTTON:
				_rotateRight = mcm->GetState();
				break;
			default:
				break;
			}

			if (!mcm->GetState()) {
				switch (mcm->GetMouseButton()) {
				case MouseButtonType::M_BUTTON: {
					if (Game::TheGame->GetGameMode() == GameMode::SINGLE_PLAYER) {
						TimeWarpActivationMessage* twam{ new TimeWarpActivationMessage{ 0.9f, Game::TheGame->GetCurrentTime() } };
						_parent->OnMessage(twam);
					}
					else {
						TimeWarpActivationMessage* twam{ new TimeWarpActivationMessage{ 0.45f, Game::TheGame->GetCurrentTime() } };
						_parent->OnMessage(twam);
					}
				}
					break;
				default:
					break;
				}
			}
		}
	}
}

void PlayerMouseControllerComponent::End() noexcept
{
}
