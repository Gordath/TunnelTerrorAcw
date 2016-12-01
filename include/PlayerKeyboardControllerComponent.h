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

	void CalculateXformMatrix(glm::mat4& matrix) const noexcept;
public:
	PlayerKeyboardControllerComponent(GameObject* gameObject);

	void Start() override;

	void Update(double deltaTime) override;

	void OnMessage(Message* msg) override;

	void End() override;
};

#endif //PLAYER_KEYBOARD_CONTROLLER_COMPONENT_H_
