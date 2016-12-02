#ifndef PLAYER_KEYBOARD_CONTROLLER_COMPONENT_H_
#define PLAYER_KEYBOARD_CONTROLLER_COMPONENT_H_
#include "UserInputComponent.h"
#include <GL/GLM/detail/type_vec3.hpp>
#include <GL/GLM/mat4x2.hpp>

class PlayerKeyboardControllerComponent : public UserInputComponent {
private:
	float _rotationSpeed{ 0.0f };
	float _rotationAngle{ 0.0f };
	glm::vec3 _playerLocalPos;
	glm::vec3 _playerLocalScale{ 0.2f, 0.2f, 0.2f };

	bool _rotateLeft{ false };
	bool _rotateRight{ false };

	void CalculateXformMatrix(glm::mat4& matrix) const noexcept;

public:
	PlayerKeyboardControllerComponent(GameObject* gameObject);

	void Start() override;

	void Update(double deltaTime) override;

	void OnMessage(Message* msg) override;

	void End() override;

	void SetRotationSpeed(float rotationSpeed) noexcept { _rotationSpeed = rotationSpeed; }

	void SetPlayerLocalPosition(const glm::vec3& localPosition) noexcept { _playerLocalPos = localPosition; }

	void SetPlayerLocalScale(const glm::vec3& localScale) noexcept { _playerLocalScale = localScale; }
};

#endif //PLAYER_KEYBOARD_CONTROLLER_COMPONENT_H_
