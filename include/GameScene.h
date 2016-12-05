#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_
#include "Scene.h"
#include "PhysicsSystem.h"
#include "CollisionSystem.h"
#include <GL/GLM/glm.hpp>
#include "PipeNetwork.h"
#include <memory>
#include "player.h"

class GameScene : public Scene {
protected:
	CollisionSystem _collisionSystem;

	std::unique_ptr<PipeNetwork> _pipeNetwork;

	Player* _player;

	unsigned int _score;
	bool _playerDied{ false };

	glm::mat4 M;
	glm::mat4 V;
	glm::mat4 P;

public:
	~GameScene();

	void Initialise() override;

	void OnKeyboard(int key, bool down) override;

	void OnMessage(Message* msg) override;

	void Update(double deltaTime, long time) override;

	void Render(RenderSystem* renderer) override;
};

#endif //GAME_SCENE_H_
