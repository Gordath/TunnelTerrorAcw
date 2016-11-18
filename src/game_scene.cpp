#include "game_scene.h"
#include "pipe.h"
#include "debug_dummy.h"
#include "SceneManager.h"
#include "Game.h"

void GameScene::Initialise()
{
	DebugDummy *dd = new DebugDummy(_sceneManager->GetGame()->GetMesh("triangle"));
	dd->Reset();
	_gameObjects.push_back(dd);

	for(auto gameObject : _gameObjects) {
		gameObject->Start();
	}
}

void GameScene::OnKeyboard(int key, bool down)
{
	
}

void GameScene::Update(double deltaTime)
{
	Scene::Update(deltaTime);

	glm::mat4 proj{ glm::perspective(static_cast<float>(toRad(60.0f)), 1024.0f / 768.0f, 0.1f, 1000.0f) };
	MVM = glm::mat4{ 1.0f };
	MVM *= proj;
	MVM = glm::translate(MVM, glm::vec3{ 0.0, 0.0, -10.0f });
	static long foo;
	foo += deltaTime * 500;
	MVM = glm::rotate(MVM, static_cast<float>(toRad(foo)), glm::vec3{ 0, 1 ,0 });
}

void GameScene::Render(RenderSystem* renderer)
{
	renderer->SetMVM(MVM);
	renderer->Process(_gameObjects, 0);
}
