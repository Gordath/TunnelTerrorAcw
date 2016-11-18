#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_
#include "Scene.h"
#include "PhysicsSystem.h"
#include "CollisionSystem.h"

class GameScene : public Scene {
protected:
	PhysicsSystem _physicsSystem;
	CollisionSystem _collisionSystem;

public:
	void Initialise() override;

	void OnKeyboard(int key, bool down) override;

	void Render(RenderSystem* renderer) override;
};

#endif //GAME_SCENE_H_