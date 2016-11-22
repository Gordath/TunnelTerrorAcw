#pragma once
#include "System.h"
#include <vector>

class PhysicsComponent;

// Moves objects around based on PhysicsComponents
class PhysicsSystem : public System {
public:
	PhysicsSystem();
	virtual ~PhysicsSystem();

	void Process(std::vector<GameObject*>& list, double deltaTime) override;
};
