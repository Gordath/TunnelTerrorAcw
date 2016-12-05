#include "MainMenuScene.h"
#include "Game.h"
#include "Window.h"
#include <GL/GLM/GTC/matrix_transform.inl>
#include <algorithm>
#include <iostream>
#include "GameScene.h"

void MainMenuScene::Initialise()
{
	PipeItem* smallObstacleTemplate{ new PipeItem{ _sceneManager->GetGame()->GetMesh("cube") } };
	smallObstacleTemplate->SetScale(glm::vec3{ 0.3f, 0.2f, 0.3f });

	PipeDesc pipeDesc{ 7.0f, 1.0f, 20, 20, 0.25f };
	_pipeNetwork = std::make_unique<PipeNetwork>(pipeDesc, 3, 0.0055f, this);
	_pipeNetwork->AddPipeItemTemplate(smallObstacleTemplate);
	_pipeNetwork->Initialize(_sceneManager->GetGame()->GetRenderer());
}

void MainMenuScene::OnKeyboard(int key, bool down)
{
	switch(down) {
	case true:
		switch (key) {
		case '1':
			_sceneManager->PushScene(new GameScene);
			break;
		default:
			break;
		}
	case false:
		switch (key) {
		default:
			break;
		}
	default:
		break;
	}
}

void MainMenuScene::Update(double deltaTime, long time)
{
	Scene::Update(deltaTime, time);

	_pipeNetwork->Update(deltaTime, 0);

	P = glm::mat4{ 1.0f };
	P *= glm::perspectiveLH(static_cast<float>(glm::radians(90.0f)), 1024.0f / 768.0f, 0.1f, 1000.0f);

	V = glm::mat4{ 1.0f };
	V = glm::rotate(V, static_cast<float>(glm::radians(-15.0f)), glm::vec3{ 1, 0, 0 });
	V = glm::rotate(V, static_cast<float>(glm::radians(-90.0f)), glm::vec3{ 0, 1, 0 });
	V = glm::translate(V, glm::vec3{ 0.0f, 0.0f, sin(time / 1000.0f) * 0.25f });
	V = glm::rotate(V, glm::radians(time / 60.0f), glm::vec3{ 1.0f, 0.0f, 0.0f });
	V = glm::rotate(V, cos(time / 1000.0f) * glm::pi<float>() / 7.5f, glm::vec3{ 0.0f, 1.0f, 0.0f });
	V = glm::translate(V, glm::vec3{ 0.0f, -0.35, 0.0f });
}

void MainMenuScene::Render(RenderSystem* renderer)
{
	renderer->SetModelMatrix(glm::mat4{ 1 });
	renderer->SetViewMatrix(V);
	renderer->SetProjectionMatrix(P);
	renderer->Process(_gameObjects, 0);

	int winWidth{ _sceneManager->GetGame()->GetWindow()->_width };
	int winHeight{ _sceneManager->GetGame()->GetWindow()->_height };

	int verticalOffset = winHeight / 8;
	int verticalPos = verticalOffset;

	renderer->GetRenderer()->DrawString(L"TUNNEL TERROR", 100, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);

	verticalPos = winHeight / 2;
	renderer->GetRenderer()->DrawString(L"1. SINGLE PLAYER", 50, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);

	verticalPos += verticalOffset;
	renderer->GetRenderer()->DrawString(L"2. TWO PLAYER", 50, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);

	verticalPos += verticalOffset;
	renderer->GetRenderer()->DrawString(L"3. OPTIONS", 50, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);

	verticalPos += verticalOffset + 20;
	renderer->GetRenderer()->DrawString(L"DEVELOPED BY ANGELOS GKOUNTIS FOR THE UNIVERSITY OF HULL", 25, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);
}
