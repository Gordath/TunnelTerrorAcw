#include "game_scene.h"
#include "pipe.h"
#include "debug_dummy.h"
#include "SceneManager.h"
#include "Game.h"
#include "RenderComponent.h"
#include "Window.h"
#include <random>
#include <GL/GLM/GTC/matrix_transform.inl>
#include <iostream>
#include <algorithm>

void GameScene::Initialise()
{
	srand(time(nullptr));
	_pipeSystem = new GameObject("PipeSystem");
	RenderComponent *rc = new RenderComponent(_pipeSystem);
	_gameObjects.push_back(_pipeSystem);

	for (int i = 0; i < MAX_PIPES; i++) {
		Pipe* pipe = _pipes[i] = new Pipe(7, 1, 20, 20, _sceneManager->GetGame()->GetRenderer());

		if (i == 0) {
			pipe->SetParent(_pipeSystem);
			pipe->SetEulerAngles(glm::vec3{ pipe->GetEulerAngles().xy, 0 });
		}
		else {
			pipe->SetParent(_pipes[i - 1]);

			static float prevRot;
			float relativeRotation = glm::radians((rand() % pipe->GetCurveSegments()) * (360.0f / pipe->GetPipeSegments()));
			
			pipe->SetRelativeRotation(relativeRotation);

			pipe->SetPosition(glm::vec3{});

			glm::mat4 extraXForm = glm::mat4(1);
			extraXForm = glm::translate(extraXForm, glm::vec3{ 0.0f, pipe->GetCurveRadius(), 0.0f });
			extraXForm = glm::rotate(extraXForm, relativeRotation, glm::vec3{ 1.0f, 0.0f, 0.0f });
			extraXForm = glm::translate(extraXForm, glm::vec3{0.0f, -pipe->GetCurveRadius(), 0.0f});

			pipe->SetExtraXForm(extraXForm);
		}

		_gameObjects.push_back(pipe);
	}

	//Align the 1st pipe with the origin.
	_currentPipe = _pipes[0];
	_currentPipe->SetPosition(glm::vec3{ 0.0f, -_currentPipe->GetCurveRadius(), 0.0f });

	_distanceToAngle = 360.0f / 2.0f * glm::pi<float>() * _currentPipe->GetCurveRadius();

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

	float delta{ _speed * static_cast<float>(deltaTime) };
	_distanceTraveled += delta;

	_pipeSystemRotation += delta * _distanceToAngle;
	std::cout << _pipeSystemRotation << std::endl;

	if (_pipeSystemRotation >= 90.0f) {
		delta = (_pipeSystemRotation - 90.0f) / _distanceToAngle;

		//shift the pipes and update the current pipe
		Pipe* temp = _pipes[0];
		for (int i = 1; i < MAX_PIPES; i++) {
			_pipes[i - 1] = _pipes[i];
		}
		_pipes[MAX_PIPES - 1] = temp;
		std::replace(_gameObjects.begin(), _gameObjects.end(), _currentPipe, _pipes[0]);
		_currentPipe = _pipes[0];
		_currentPipe->SetPosition(glm::vec3{0.0f, -_currentPipe->GetCurveRadius(), 0.0f});
		_currentPipe->SetEulerAngles(glm::vec3{});
		_currentPipe->SetExtraXForm(glm::mat4{ 1 });
		_currentPipe->SetParent(_pipeSystem);

		_pipeSystemRotation = delta * _distanceToAngle;

		_worldRotation += glm::degrees(_currentPipe->GetRelativeRotation());
		if(_worldRotation < 0.0f) {
			_worldRotation += 360.0f;
		}
		else if (_worldRotation >= 360.0f) {
			_worldRotation -= 360.0f;
		}
	}

	_currentPipe->SetEulerAngles(glm::vec3{0.0f, 0.0f, glm::radians(_pipeSystemRotation)});
	_pipeSystem->SetEulerAngles(glm::vec3{glm::radians(_worldRotation), 0.0f, 0.0f });

	

	glm::mat4 proj{ glm::perspectiveLH(static_cast<float>(glm::radians(90.0f)), 1024.0f / 768.0f, 0.1f, 1000.0f) };

	P = glm::mat4{ 1.0f };
	P *= proj;


	V = glm::mat4{ 1.0f };
	V = glm::translate(V, glm::vec3{ 0.0, 0.0, 20.0f });
//	V = glm::rotate(V, static_cast<float>(glm::radians(-90.0f)), glm::vec3{ 0, 1, 0 });
//	V = glm::translate(V, glm::vec3{ 5.0, 0.0, 0.0f });

//	V = glm::rotate(V, static_cast<float>(_sceneManager->GetGame()->GetWindow()->_cursorX / 10.0f), glm::vec3{ 0, 1, 0 });
//	V = glm::rotate(V, static_cast<float>(_sceneManager->GetGame()->GetWindow()->_cursorY / 10.0f), glm::vec3{ 1, 0, 0 });
}

void GameScene::Render(RenderSystem* renderer)
{
	renderer->SetModelMatrix(glm::mat4{1});
	renderer->SetViewMatrix(V);
	renderer->SetProjectionMatrix(P);
	renderer->Process(_gameObjects, 0);
}
