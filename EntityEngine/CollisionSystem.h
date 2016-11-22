#pragma once
#include "System.h"
#include <vector>

class CollisionComponent;

// Moves objects around based on PhysicsComponents
class CollisionSystem : public System {
public:
	CollisionSystem();
	virtual ~CollisionSystem();

	bool CollideWith(const CollisionComponent* collidee, const CollisionComponent* collider);

	void Process(std::vector<GameObject*>& list, double deltaTime) override;
};
