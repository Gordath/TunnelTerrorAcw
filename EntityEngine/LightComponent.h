#ifndef LIGHT_COMPONENT_H_
#define LIGHT_COMPONENT_H_
#include "GameObjectComponent.h"
#include <GL/GLM/detail/type_vec3.hpp>

class LightComponent : public GameObjectComponent {
private:
	glm::vec3 _position;
	glm::vec3 _direction;

public:

	LightComponent(GameObject* parent)
		: GameObjectComponent("light", parent)
	{
	}

	void OnMessage(Message*) noexcept override;
	
	void Start() noexcept override;
	
	void Update(double deltaTime) noexcept override;
	
	void End() noexcept override;
};

#endif //LIGHT_COMPONENT_H_