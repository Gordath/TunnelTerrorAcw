#ifndef PLAYER_MOUSE_CONTROLLER_COMPONENT_H_
#define PLAYER_MOUSE_CONTROLLER_COMPONENT_H_
#include "UserInputComponent.h"
#include <GL/GLM/detail/type_vec3.hpp>
#include <GL/GLM/mat4x2.hpp>

class PlayerMouseControllerComponent : public UserInputComponent {
private:
	float _rotationSpeed{ 0.0f };
	float _rotationAngle{ 0.0f };
	glm::vec3 _playerLocalPos;
	glm::vec3 _playerLocalScale;

	bool _rotateLeft{ false };
	bool _rotateRight{ false };

	void CalculateXformMatrix(glm::mat4& matrix) const noexcept;

public:
	PlayerMouseControllerComponent(GameObject* gameObject, const std::string& type)
	:UserInputComponent(gameObject, type)
	{}

	void Start() noexcept override;

	void Update(double deltaTime) noexcept override;

	void OnMessage(Message* msg) noexcept override;

	void End() noexcept override;

	void SetRotationSpeed(float rotationSpeed) noexcept { _rotationSpeed = rotationSpeed; }

	void SetPlayerLocalPosition(const glm::vec3& localPosition) noexcept { _playerLocalPos = localPosition; }

	void SetPlayerLocalScale(const glm::vec3& localScale) noexcept { _playerLocalScale = localScale; }
};

#endif //PLAYER_MOUSE_CONTROLLER_COMPONENT_H_