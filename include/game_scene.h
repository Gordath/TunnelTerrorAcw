#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_
#include "Scene.h"
#include "PhysicsSystem.h"
#include "CollisionSystem.h"
#include <GL/GLM/glm.hpp>
#include "pipe_network.h"

class GameScene : public Scene {
protected:
	PhysicsSystem _physicsSystem;
	CollisionSystem _collisionSystem;

	PipeNetwork* _pipeNetwork;

	glm::mat4 M;
	glm::mat4 V;
	glm::mat4 P;

public:
	void Initialise() override;

	void OnKeyboard(int key, bool down) override;

	void OnMouseMove(int x, int y) override;

	void Update(double deltaTime, long time) override;

	void Render(RenderSystem* renderer) override;
};

#endif //GAME_SCENE_H_
