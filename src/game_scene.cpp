#include "game_scene.h"
#include "pipe.h"
#include "debug_dummy.h"
#include "SceneManager.h"
#include "Game.h"
#include "Window.h"
#include <random>

void GameScene::Initialise()
{
	for (int i = 0, j = 1; i < MAX_PIPES; i++, j++) {
		Pipe* pipe = pipes[i] = new Pipe(4, 1, 20, 10, _sceneManager->GetGame()->GetRenderer());

		if (i == 0) {
			pipe->SetAngleZ(0);
		}
		else {
			pipe->SetParent(pipes[i - 1]);

			float relativeRotation = toRad((rand() % pipe->GetCurveSegments()) * (360.0f / pipe->GetPipeSegments()));

			pipe->SetPosition(Vector4{});

			glm::mat4 extraXForm = glm::mat4(1);
			extraXForm = glm::translate(extraXForm, glm::vec3{ 0.0f, 4, 0.0f });
			extraXForm = glm::rotate(extraXForm, relativeRotation, glm::vec3{ 1.0f, 0.0f, 0.0f });
			extraXForm = glm::translate(extraXForm, glm::vec3{0.0f, -4, 0.0f});

			pipe->SetExtraXForm(extraXForm);
		}
		_gameObjects.push_back(pipe);
	}

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

	glm::mat4 proj{ glm::perspectiveLH(static_cast<float>(toRad(60.0f)), 1024.0f / 768.0f, 0.1f, 1000.0f) };
	MVM = glm::mat4{ 1.0f };
	MVM *= proj;
	MVM = glm::translate(MVM, glm::vec3{ 0.0, 0.0, 300.0f });

	MVM = glm::rotate(MVM, static_cast<float>(_sceneManager->GetGame()->GetWindow()->_cursorX / 10.0f), glm::vec3{ 0, 1, 0 });
//	MVM = glm::rotate(MVM, static_cast<float>(_sceneManager->GetGame()->GetWindow()->_cursorY / 10.0f), glm::vec3{ 1, 0, 0 });
}

void GameScene::Render(RenderSystem* renderer)
{
	renderer->SetMVM(MVM);
	renderer->Process(_gameObjects, 0);
}
