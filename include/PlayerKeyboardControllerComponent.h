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
	glm::vec3 _playerLocalScale;
	glm::vec3 _playerLocalRotation;

	bool _rotateLeft{ false };
	bool _rotateRight{ false };

	void CalculateXformMatrix(glm::mat4& matrix) const noexcept;

public:
	PlayerKeyboardControllerComponent(GameObject* gameObject, const std::string& type);

	void Start() noexcept override;

	void Update(double deltaTime) noexcept override;

	void OnMessage(Message* msg) noexcept override;

	void End() noexcept override;

	float GetRotationSpeed() const noexcept { return _rotationSpeed; }
	void SetRotationSpeed(float rotationSpeed) noexcept { _rotationSpeed = rotationSpeed; }

	const glm::vec3& GetPlayerLocalPosition() const noexcept { return _playerLocalPos; }
	void SetPlayerLocalPosition(const glm::vec3& localPosition) noexcept { _playerLocalPos = localPosition; }

	const glm::vec3& GetPlayerLocalScale() const noexcept { return _playerLocalScale; }
	void SetPlayerLocalScale(const glm::vec3& localScale) noexcept { _playerLocalScale = localScale; }
};

#endif //PLAYER_KEYBOARD_CONTROLLER_COMPONENT_H_
