#include "game_scene.h"
#include "pipe.h"
#include "debug_dummy.h"
#include "SceneManager.h"
#include "Game.h"

void GameScene::Initialise()
{
	DebugDummy *dd = new DebugDummy(_sceneManager->GetGame()->GetMesh("cube"));
	_gameObjects.push_back(dd);

	for(auto gameObject : _gameObjects) {
		gameObject->Start();
	}
}

void GameScene::OnKeyboard(int key, bool down)
{
	
}

void GameScene::Render(RenderSystem* renderer)
{
	glm::mat4 camera;
	glm::translate(camera, glm::vec3{ 0, 0, -1 });

	glm::mat4 projection{ glm::perspectiveFovLH(60.0f, 1024.0f, 768.0f, 0.1f, 1000.0f) };

	renderer->SetMVM(projection * glm::inverse(camera));
	renderer->Process(_gameObjects, 0);
}
