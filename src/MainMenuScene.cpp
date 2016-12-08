#include "MainMenuScene.h"
#include "Game.h"
#include "Window.h"
#include <GL/GLM/GTC/matrix_transform.inl>
#include <iostream>
#include "GameScene.h"
#include "Texture_DX.h"


// Private methods ----------------------------------------------------------------------------------
void MainMenuScene::DrawGameTitle(Renderer* renderer) const noexcept
{
	int winWidth{ _sceneManager->GetGame()->GetWindow()->_width };
	int winHeight{ _sceneManager->GetGame()->GetWindow()->_height };

	int verticalOffset = winHeight / 8;
	int verticalPos = verticalOffset;

	renderer->DrawString(L"TUNNEL TERROR", 100, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);
}

void MainMenuScene::DrawInitialMenuText(Renderer* renderer) const noexcept
{
	int winWidth{ _sceneManager->GetGame()->GetWindow()->_width };
	int winHeight{ _sceneManager->GetGame()->GetWindow()->_height };

	int verticalOffset = winHeight / 8;

	int verticalPos = winHeight / 2;
	renderer->DrawString(L"1. SINGLE PLAYER", 50, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);

	verticalPos += verticalOffset;
	renderer->DrawString(L"2. TWO PLAYER", 50, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);

	verticalPos += verticalOffset;
	renderer->DrawString(L"3. EXIT GAME", 50, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);

	verticalPos += verticalOffset + 20;
	renderer->DrawString(L"DEVELOPED BY ANGELOS GKOUNTIS FOR THE UNIVERSITY OF HULL", 25, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);
}

void MainMenuScene::DrawSPControlsSelectionText(Renderer* renderer) const noexcept
{
	int winWidth{ _sceneManager->GetGame()->GetWindow()->_width };
	int winHeight{ _sceneManager->GetGame()->GetWindow()->_height };

	int verticalOffset = winHeight / 8;

	int verticalPos = winHeight / 2;
	renderer->DrawString(L"1. KEYBOARD", 50, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);

	verticalPos += verticalOffset;
	renderer->DrawString(L"2. MOUSE", 50, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);

	verticalPos += verticalOffset;
	renderer->DrawString(L"3. BACK", 50, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);
}

void MainMenuScene::DrawTPControlsSelectionText(Renderer* renderer) const noexcept
{
	int winWidth{ _sceneManager->GetGame()->GetWindow()->_width };
	int winHeight{ _sceneManager->GetGame()->GetWindow()->_height };

	int verticalOffset = winHeight / 8;

	int verticalPos = winHeight / 2;
	renderer->DrawString(L"1. PLAYER1 KEYBOARD    PLAYER2 MOUSE", 50, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);

	verticalPos += verticalOffset;
	renderer->DrawString(L"2. PLAYER1 MOUSE    PLAYER2 KEYBOARD", 50, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);

	verticalPos += verticalOffset;
	renderer->DrawString(L"3. BACK", 50, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);
}

// --------------------------------------------------------------------------------------------------

void MainMenuScene::Initialise()
{
	PipeItem* smallObstacleTemplate{ new PipeItem{ _sceneManager->GetGame()->GetMesh("cube") } };
	smallObstacleTemplate->SetScale(glm::vec3{ 0.3f, 0.3f, 0.3f });

	PipeDesc pipeDesc{ 7.0f, 1.0f, 20, 20, 0.25f };
	_pipeNetwork = std::make_unique<PipeNetwork>(pipeDesc, 3, 0.0055f, this);
	_pipeNetwork->AddPipeItemTemplate(smallObstacleTemplate);
	_pipeNetwork->Initialize(_sceneManager->GetGame()->GetRenderer());
}


void MainMenuScene::OnKeyboard(int key, bool down)
{
	switch (down) {
	case true:
		switch (key) {
		default:
			break;
		}
		break;
	case false:
		switch (key) {
		case '1':
			if (_menuState == MainMenuState::SP_CONTROLS_SELECTION) {
				Material m;
				m.diffuse = glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f };
				m.specular = glm::vec4{ 1.0f, 1.0f, 1.0f, 60.0f };
				m.textures[TEX_DIFFUSE] = Game::_resourceManager.Get<Texture_DX>(L"test.png");
				m.textures[TEX_SPECULAR] = Game::_resourceManager.Get<Texture_DX>(L"testSpec.png");
				m.textures[TEX_NORMAL] = Game::_resourceManager.Get<Texture_DX>(L"testNorm.png");

				Player* player{ new Player{ _sceneManager->GetGame()->GetMesh("cube"), m, PlayerControls::KEYBOARD, glm::vec3{ 0.85f, -0.75f, 0.0f } } };
				_sceneManager->PushScene(new GameScene(std::vector<Player*>{ player }));
				_menuState = MainMenuState::INITIAL_MENU;
				_sceneManager->GetGame()->SetGameMode(GameMode::SINGLE_PLAYER);
				break;
			}

			if (_menuState == MainMenuState::TP_CONTROLS_SELECTION) {
				Material m1;
				m1.diffuse = glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f };
				m1.specular = glm::vec4{ 1.0f, 1.0f, 1.0f, 60.0f };
				m1.textures[TEX_DIFFUSE] = Game::_resourceManager.Get<Texture_DX>(L"test.png");
				m1.textures[TEX_SPECULAR] = Game::_resourceManager.Get<Texture_DX>(L"testSpec.png");
				m1.textures[TEX_NORMAL] = Game::_resourceManager.Get<Texture_DX>(L"testNorm.png");

				Material m2;
				m2.diffuse = glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f };
				m2.specular = glm::vec4{ 1.0f, 1.0f, 1.0f, 60.0f };
				m2.textures[TEX_DIFFUSE] = Game::_resourceManager.Get<Texture_DX>(L"test.png");
				m2.textures[TEX_SPECULAR] = Game::_resourceManager.Get<Texture_DX>(L"testSpec.png");
				m2.textures[TEX_NORMAL] = Game::_resourceManager.Get<Texture_DX>(L"testNorm.png");
				
				Player* player1{ new Player{ _sceneManager->GetGame()->GetMesh("cube"), m1, PlayerControls::KEYBOARD, glm::vec3{ 0.85f, -0.75f, 0.0f } } };
				Player* player2{ new Player{ _sceneManager->GetGame()->GetMesh("cube"), m2, PlayerControls::MOUSE, glm::vec3{ 1.1f, -0.75f, 0.0f } } };
				_sceneManager->PushScene(new GameScene(std::vector<Player*>{ player1, player2 }));
				_menuState = MainMenuState::INITIAL_MENU;
				_sceneManager->GetGame()->SetGameMode(GameMode::MULTI_PLAYER);
				break;
			}

			if (_menuState == MainMenuState::INITIAL_MENU) {
				_menuState = MainMenuState::SP_CONTROLS_SELECTION;
			}
			break;

		case '2':
			if (_menuState == MainMenuState::SP_CONTROLS_SELECTION) {
				Material m;
				m.diffuse = glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f };
				m.specular = glm::vec4{ 1.0f, 1.0f, 1.0f, 60.0f };
				m.textures[TEX_DIFFUSE] = Game::_resourceManager.Get<Texture_DX>(L"test.png");
				m.textures[TEX_SPECULAR] = Game::_resourceManager.Get<Texture_DX>(L"testSpec.png");
				m.textures[TEX_NORMAL] = Game::_resourceManager.Get<Texture_DX>(L"testNorm.png");

				Player* player{ new Player{ _sceneManager->GetGame()->GetMesh("cube"), m, PlayerControls::MOUSE, glm::vec3{ 0.85f, -0.75f, 0.0f } } };
				_sceneManager->PushScene(new GameScene(std::vector<Player*>{ player }));
				_menuState = MainMenuState::INITIAL_MENU;
				_sceneManager->GetGame()->SetGameMode(GameMode::SINGLE_PLAYER);
				break;
			}

			if (_menuState == MainMenuState::TP_CONTROLS_SELECTION) {
				Material m1;
				m1.diffuse = glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f };
				m1.specular = glm::vec4{ 1.0f, 1.0f, 1.0f, 60.0f };
				m1.textures[TEX_DIFFUSE] = Game::_resourceManager.Get<Texture_DX>(L"test.png");
				m1.textures[TEX_SPECULAR] = Game::_resourceManager.Get<Texture_DX>(L"testSpec.png");
				m1.textures[TEX_NORMAL] = Game::_resourceManager.Get<Texture_DX>(L"testNorm.png");

				Material m2;
				m2.diffuse = glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f };
				m2.specular = glm::vec4{ 1.0f, 1.0f, 1.0f, 60.0f };
				m2.textures[TEX_DIFFUSE] = Game::_resourceManager.Get<Texture_DX>(L"test.png");
				m2.textures[TEX_SPECULAR] = Game::_resourceManager.Get<Texture_DX>(L"testSpec.png");
				m2.textures[TEX_NORMAL] = Game::_resourceManager.Get<Texture_DX>(L"testNorm.png");
				Player* player1{ new Player{ _sceneManager->GetGame()->GetMesh("cube"), m1, PlayerControls::MOUSE, glm::vec3{ 0.85f, -0.75f, 0.0f } } };
				Player* player2{ new Player{ _sceneManager->GetGame()->GetMesh("cube"), m2, PlayerControls::KEYBOARD, glm::vec3{ 1.1f, -0.75f, 0.0f } } };
				_sceneManager->PushScene(new GameScene(std::vector<Player*>{ player1, player2 }));
				_menuState = MainMenuState::INITIAL_MENU;
				_sceneManager->GetGame()->SetGameMode(GameMode::MULTI_PLAYER);
				break;
			}

			if (_menuState == MainMenuState::INITIAL_MENU) {
				_menuState = MainMenuState::TP_CONTROLS_SELECTION;
			}
			break;
		case '3':
			if (_menuState == MainMenuState::INITIAL_MENU) {
				_sceneManager->GetGame()->SetQuitFlag(true);
			}
			else if (_menuState == MainMenuState::SP_CONTROLS_SELECTION) {
				_menuState = MainMenuState::INITIAL_MENU;
			}
			else {
				_menuState = MainMenuState::INITIAL_MENU;
			}
			
			break;
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

	_pipeNetwork->Update(deltaTime, time, false);

	P = glm::mat4{ 1.0f };
	float winWidth{ static_cast<float>(_sceneManager->GetGame()->GetWindow()->_width) };
	float winHeight{ static_cast<float>(_sceneManager->GetGame()->GetWindow()->_height) };
	P *= glm::perspectiveLH(static_cast<float>(glm::radians(90.0f)), winWidth / winHeight, 0.1f, 1000.0f);

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

	DrawGameTitle(renderer->GetRenderer());

	if (_menuState == MainMenuState::INITIAL_MENU) {
		DrawInitialMenuText(renderer->GetRenderer());
	}
	else if (_menuState == MainMenuState::SP_CONTROLS_SELECTION) {
		DrawSPControlsSelectionText(renderer->GetRenderer());
	}
	else {
		DrawTPControlsSelectionText(renderer->GetRenderer());
	}
}