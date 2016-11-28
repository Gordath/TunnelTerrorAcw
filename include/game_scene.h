#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_
#include "Scene.h"
#include "PhysicsSystem.h"
#include "CollisionSystem.h"
#include <GL/GLM/glm.hpp>
#include "pipe.h"

class GameScene : public Scene {
protected:
	PhysicsSystem _physicsSystem;
	CollisionSystem _collisionSystem;

	GameObject* _pipeSystem;
	//PIPES -------------------------------------
	static const int MAX_PIPES{ 5 };

	Pipe* _pipes[MAX_PIPES];
	Pipe* _currentPipe{ nullptr };
	float _speed{ 0.01f };
	float _distanceTraveled{ 0.0f };
	float _distanceToAngle{ 0.0f };
	float _pipeSystemRotation{ 0.0f };
	//-------------------------------------------

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
