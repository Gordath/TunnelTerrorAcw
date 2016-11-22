#pragma once
#include "GameObjectComponent.h"
#include <vector>

// System class 
// This provides the behaviours that act on the components
class System {
public:
	System();
	virtual ~System();

	virtual void Process(std::vector<GameObject*>& list, double deltaTime) = 0;
};
