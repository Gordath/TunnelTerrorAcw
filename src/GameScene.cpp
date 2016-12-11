#include "Game.h"
#include "GameScene.h"
#include "DebugDummy.h"
#include "SceneManager.h"
#include <GL/GLM/GTC/matrix_transform.inl>
#include <iostream>
#include "DeadObjectMessage.h"
#include "ScoreScene.h"
#include "Window.h"

GameScene::~GameScene()
{
}

void GameScene::Initialise()
{
	PipeItem* smallObstacleTemplate{ new PipeItem{ Game::_resourceManager.Get<Mesh>(MODELS_PATH + L"obstacle.fbx") } };

	PipeDesc pipeDesc{ 7.0f, 1.0f, 20, 20, 0.25f };
	_pipeNetwork = std::make_unique<PipeNetwork>(pipeDesc, 3, 0.0055f, this);
	_pipeNetwork->AddPipeItemTemplate(smallObstacleTemplate);
	_pipeNetwork->Initialize(_sceneManager->GetGame()->GetRenderer());

	for (auto player : _players) {
		_gameObjects.push_back(player);
	}

	for (auto gameObject : _gameObjects) {
		gameObject->Start();
	}

	Game::_audioManager.play_stream("breach.ogg", 1.0f, AUDIO_PLAYMODE_LOOP);
}

void GameScene::OnKeyboard(int key, bool down)
{
}

void GameScene::OnMessage(Message* msg)
{
	if (msg->GetMessageType() == "dead") {
		DeadObjectMessage* dom{ static_cast<DeadObjectMessage*>(msg) };

		if (dom->GetDeadObject()->GetType() == "Player") {
			_playerDied = true;
		}
	}

	Scene::OnMessage(msg);
}

void GameScene::Update(double deltaTime, long time)
{
	if(_playerDied) {
		Game::_audioManager.stop_streams();
		_sceneManager->PushScene(new ScoreScene(_score));
	}

	Scene::Update(deltaTime, time);

	//Check for collisions.
	_collisionSystem.Process(_gameObjects, deltaTime);

	_pipeNetwork->Update(deltaTime, time);

	P = glm::mat4{ 1.0f };

	float winWidth{ static_cast<float>(_sceneManager->GetGame()->GetWindow()->_width) };
	float winHeight{ static_cast<float>(_sceneManager->GetGame()->GetWindow()->_height) };
	P *= glm::perspectiveLH(static_cast<float>(glm::radians(90.0f)), winWidth / winHeight, 0.1f, 1000.0f);

	V = glm::mat4{ 1.0f };
//	V = glm::translate(V, glm::vec3{ 0.0, 0.0, 8.0f });
//
	V = glm::rotate(V, static_cast<float>(glm::radians(-15.0f)), glm::vec3{ 1, 0, 0 });
	V = glm::rotate(V, static_cast<float>(glm::radians(-90.0f)), glm::vec3{ 0, 1, 0 });
	V = glm::translate(V, glm::vec3{ 0.0f, -0.35, 0.0f });

	_score = static_cast<int>(_pipeNetwork->GetDistanceTraveled() * 2000.0f);
//	V = glm::rotate(V, static_cast<float>(_sceneManager->GetGame()->GetWindow()->_cursorX / 10.0f), glm::vec3{ 0, 1, 0 });
//	V = glm::rotate(V, static_cast<float>(_sceneManager->GetGame()->GetWindow()->_cursorY / 10.0f), glm::vec3{ 1, 0, 0 });
}

void GameScene::Render(RenderSystem* renderer)
{
	renderer->SetModelMatrix(glm::mat4{ 1 });
	renderer->SetViewMatrix(V);
	renderer->SetProjectionMatrix(P);
	renderer->Process(_gameObjects, 0);

	renderer->GetRenderer()->DrawString(L"Score:" + std::to_wstring(_score), 50.0f, 0.0f, 0.0f, 0xff0000ff);
}
