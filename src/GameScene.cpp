#include "GameScene.h"
#include "DebugDummy.h"
#include "SceneManager.h"
#include "Game.h"
#include <GL/GLM/GTC/matrix_transform.inl>
#include "Window.h"
#include "../../../../../../../Program Files (x86)/Microsoft DirectX SDK (June 2010)/include/d3dx10.h"

void GameScene::Initialise()
{
	PipeItem* smallObstacleTemplate{ new PipeItem{ _sceneManager->GetGame()->GetMesh("cube") } };
	smallObstacleTemplate->SetScale(glm::vec3{ 0.3f, 0.2f, 0.3f });

	PipeItem* largeObstacleTemplate{ new PipeItem{_sceneManager->GetGame()->GetMesh("cube")} };
	largeObstacleTemplate->SetScale(glm::vec3{ 0.3f, 2.0f, 0.3f });


	PipeDesc pipeDesc{ 7.0f, 1.0f, 20, 20, 0.25f };
	_pipeNetwork = std::make_unique<PipeNetwork>(pipeDesc, 3, 0.0055f, this);
	_pipeNetwork->AddPipeItemTemplate(smallObstacleTemplate);
//	_pipeNetwork->AddPipeItemTemplate(largeObstacleTemplate);
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

void GameScene::Update(double deltaTime, long time)
{
	Scene::Update(deltaTime, time);

	//Check for collisions.
	_collisionSystem.Process(_gameObjects, deltaTime);

	_pipeNetwork->Update(deltaTime * 0.3f, time);

	glm::mat4 proj{ glm::perspectiveLH(static_cast<float>(glm::radians(90.0f)), 1024.0f / 768.0f, 0.1f, 1000.0f) };

	P = glm::mat4{ 1.0f };
	P *= proj;

	V = glm::mat4{ 1.0f };
//	V = glm::translate(V, glm::vec3{ 0.0, 0.0, 4.0f });
	
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

	renderer->GetRenderer()->DrawString(L"Score:" + std::to_wstring(_score), 50.0f, 0.0f, 0.0f, 0xffffffff);
}
