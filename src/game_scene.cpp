#include "game_scene.h"
#include "pipe.h"
#include "debug_dummy.h"
#include "SceneManager.h"
#include "Game.h"
#include "Window.h"

void GameScene::Initialise()
{
	Pipe *pipe = new Pipe(4, 1, 20, 10, _sceneManager->GetGame()->GetRenderer());

	_gameObjects.push_back(pipe);

//	float uDelta = (2.0f * PI) / pipe->getCurveSegments();
//	float vDelta = (2.0f * PI) / pipe->getPipeSegments();
//	for (int u = 0; u < pipe->getCurveSegments(); ++u) {
//		for (int v = 0; v < pipe->getPipeSegments(); ++v) {
//			Vector4 p = pipe->getPointOnTorus(u * uDelta, v * vDelta);
//			DebugDummy *dd = new DebugDummy(_sceneManager->GetGame()->GetMesh("cube"));
//			dd->SetScale(0.2f);
//			dd->SetPosition(p);
//			_gameObjects.push_back(dd);
//		}
//	}
	

//	DebugDummy *dd = new DebugDummy(_sceneManager->GetGame()->GetMesh("cube"));
//	dd->Reset();
//	_gameObjects.push_back(dd);

	for(auto gameObject : _gameObjects) {
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

	glm::mat4 proj{ glm::perspectiveLH(static_cast<float>(toRad(60.0f)), 1024.0f / 768.0f, 0.1f, 1000.0f) };
	MVM = glm::mat4{ 1.0f };
	MVM *= proj;
	MVM = glm::translate(MVM, glm::vec3{ 0.0, 0.0, 20.0f });

	MVM = glm::rotate(MVM, static_cast<float>(_sceneManager->GetGame()->GetWindow()->_cursorX / 10.0f), glm::vec3{ 0, 1, 0 });
	MVM = glm::rotate(MVM, static_cast<float>(_sceneManager->GetGame()->GetWindow()->_cursorY / 10.0f), glm::vec3{ 1, 0, 0 });
}

void GameScene::Render(RenderSystem* renderer)
{
	renderer->SetMVM(MVM);
	renderer->Process(_gameObjects, 0);
}
