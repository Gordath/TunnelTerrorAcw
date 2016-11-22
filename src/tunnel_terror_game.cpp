#include "tunnel_terror_game.h"
#include "Mesh.h"
#include "game_scene.h"

void TunnelTerrorGame::Initialise(Window* window)
{
	Game::Initialise(window);

	_renderer->SetClearColour(Colour{0.3f, 0.3f, 0.3f, 1.0f});

	Mesh* cube = new Mesh();
	//front
	cube->AddVertex({-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f});
	cube->AddVertex({-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f});
	cube->AddVertex({0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f});
	cube->AddVertex({0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f});


	//right
	cube->AddVertex({0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f});
	cube->AddVertex({0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f});
	cube->AddVertex({0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f});
	cube->AddVertex({0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f});

	//left
	cube->AddVertex({-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f});
	cube->AddVertex({-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f});
	cube->AddVertex({-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f});
	cube->AddVertex({-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f});

	//back
	cube->AddVertex({0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f});
	cube->AddVertex({0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f});
	cube->AddVertex({-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f});
	cube->AddVertex({-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f});

	//top
	cube->AddVertex({-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f});
	cube->AddVertex({-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f});
	cube->AddVertex({0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f});
	cube->AddVertex({0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f});

	//bottom
	cube->AddVertex({0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f});
	cube->AddVertex({0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f});
	cube->AddVertex({-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f});
	cube->AddVertex({-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f});

	AddMesh("cube", cube);

	for (auto mesh : _meshes) {
		mesh.second->GenerateIndices();
		mesh.second->CreateBuffers(_renderer);
	}

	_sceneManager.PushScene(new GameScene);
}

void TunnelTerrorGame::OnKeyboard(int key, bool down)
{
	Game::OnKeyboard(key, down);
}

void TunnelTerrorGame::Render()
{
	// Clear screen
	_renderer->ClearScreen();

	_sceneManager.Render(&_renderSystem);

	_renderer->SwapBuffers();
}

void TunnelTerrorGame::Run()
{
	Game::Run();
	_sceneManager.Update(_deltaTime, _currentTime);
	Render();
}

void TunnelTerrorGame::ListenToMessage(Message* msg)
{
}
