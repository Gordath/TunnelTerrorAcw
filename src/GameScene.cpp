#include "GameScene.h"
#include "DebugDummy.h"
#include "SceneManager.h"
#include "Game.h"
#include <GL/GLM/GTC/matrix_transform.inl>

void GameScene::Initialise()
{
	PipeDesc pipeDesc{ 7.0f, 1.0f, 20, 20, 0.25f };
	_pipeNetwork = std::make_unique<PipeNetwork>(pipeDesc, 3, 0.0055f, this);
	_pipeNetwork->Initialize(_sceneManager->GetGame()->GetRenderer());

	_player = new Player(_sceneManager->GetGame()->GetMesh("cube"));

	_gameObjects.push_back(_player);

	for (auto gameObject : _gameObjects) {
		gameObject->Start();
	}
}

void GameScene::OnKeyboard(int key, bool down)
{
}

void GameScene::OnMouseMove(int x, int y)
{
}

void GameScene::Update(double deltaTime, long time)
{
	Scene::Update(deltaTime, time);

	_pipeNetwork->Update(deltaTime, time);

	glm::mat4 proj{ glm::perspectiveLH(static_cast<float>(glm::radians(90.0f)), 1024.0f / 768.0f, 0.1f, 1000.0f) };

	P = glm::mat4{ 1.0f };
	P *= proj;

	V = glm::mat4{ 1.0f };
//	V = glm::translate(V, glm::vec3{ 0.0, 0.0, 4.0f });
	
	V = glm::rotate(V, static_cast<float>(glm::radians(-15.0f)), glm::vec3{ 1, 0, 0 });
	V = glm::rotate(V, static_cast<float>(glm::radians(-90.0f)), glm::vec3{ 0, 1, 0 });
	V = glm::translate(V, glm::vec3{ 0.0f, -0.35, 0.0f });

	//	V = glm::rotate(V, static_cast<float>(_sceneManager->GetGame()->GetWindow()->_cursorX / 10.0f), glm::vec3{ 0, 1, 0 });
	//	V = glm::rotate(V, static_cast<float>(_sceneManager->GetGame()->GetWindow()->_cursorY / 10.0f), glm::vec3{ 1, 0, 0 });
}

void GameScene::Render(RenderSystem* renderer)
{
	renderer->SetModelMatrix(glm::mat4{ 1 });
	renderer->SetViewMatrix(V);
	renderer->SetProjectionMatrix(P);
	renderer->Process(_gameObjects, 0);
}
